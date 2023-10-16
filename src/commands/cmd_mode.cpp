/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:06:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 07:44:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"


//    ERR_NEEDMOREPARAMS              ERR_USERSDONTMATCH
//    ERR_UMODEUNKNOWNFLAG            RPL_UMODEIS

//    a - user is flagged as away;
//    i - marks a users as invisible;
//    w - user receives wallops;
//    r - restricted user connection;					NOT SELF -
//    o - operator flag; 								NOT SELF +
//    O - local operator flag; 							NOT SELF +
//    s - marks a user for receipt of server notices.
//		registered = 0x0080,	// user is registered	NOT SELF
//		online = 0x0100			// user is online		NOT SELF

# define ALL_MODES "awiroOs"

static bool hasPermissions(IRCServer& server, User& user, Message& message){
	
	if (!user.getMode() >> 0x0080 & 1)
		user.getSendBuffer().addToBuffer(ERR_NOTREGISTERED(server.getName(), message.getCommand()).c_str());
	if (message.getParams()[0].size() < 1){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	if (user.getNick() != message.getParams()[0]){
		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
		return 1;
	}
	if (message.getParams()[0].size() == 2){
		user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
			server.getModeStr(user)).c_str());
	}
}

int cmd_mode(IRCServer& server, User& user, Message& message){

	
	if (!hasPermissions(server, user, message));
		return 1;
		
	std::vector<std::string>const & params = message.getParams();
	size_t forbidden;
	for (size_t i = 1; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALL_MODES);
		std::cout << std::boolalpha << (forbidden == std::string::npos) << std::endl;
		if (forbidden != std::string::npos)
			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName()).c_str());
	}

	std::string additions;
	std::string removals;
	for (size_t i = 1; i < params.size(); i++){
		size_t pos = 0;
		while (pos < params[i].size())
		{
			if (params[i][pos] == '+')
				additions += server.setBatchMode(user, params[i], &pos);
			else if (params[i][pos] == '-')
				removals += server.unsetBatchMode(user, params[i], &pos);
			else
				pos++;
		}
	}

	removeCommonCharacters(additions, removals);

	std::string reply = ":" + user.getNick() + " MODE " +  user.getNick() + " :";
	reply += !additions.empty() ? ("+" + additions) : "";
	reply += !removals.empty() ?  ("-" + removals) : "";
	user.getSendBuffer().addToBuffer(reply.c_str());

	return 0;
}