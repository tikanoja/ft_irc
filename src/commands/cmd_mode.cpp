/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:06:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/23 17:06:24 by djagusch         ###   ########.fr       */
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

# define ALL_MODES "+-awiroOs"

static bool hasPermissions(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return false;
	}
	if (message.getParams()[0].size() < 1){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return false;
	}
	if (user.getNick() != message.getParams()[0]){
		user.send(ERR_USERSDONTMATCH(server.getName()));
		return false;
	}
	if (message.getParams()[0].size() == 2){
		user.send(RPL_UMODEIS(server.getName(),
			server.getModeStr(user)));
		return false;
	}
	return true;
}

int cmd_mode(IRCServer& server, User& user, Message& message){

	
	if (!hasPermissions(server, user, message))
		return 1;
	std::vector<std::string>const & params = message.getParams();
	if (params.size() == 1){
		std::string mode = server.getModeStr(user);
		std::string reply = server.getName();
		std::cout << reply << std::endl;
		user.send(RPL_UMODEIS(server.getName(), mode));
		return 0;
	}
	size_t forbidden;
	for (size_t i = 1; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALL_MODES);
		if (forbidden != std::string::npos)
			user.send(ERR_UMODEUNKNOWNFLAG(server.getName()));
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
	user.send(reply + "\r\n");

	return 0;
}
