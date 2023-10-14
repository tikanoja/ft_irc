/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:06:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/14 10:52:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"


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
# define SETTABLE_MODES "iwroO"


int cmd_mode(IRCServer& server, User& user, Message& message){

	std::vector<std::string>const & params = message.getParams();

	if (params.size() < 1){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	std::cout << "param check passed" << std::endl;
	std::cout << user.getNick() << "\n" << params[0] << std::endl;
	if (user.getNick() != params[0]){
		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
		std::cout << "Users don't match" << std::endl;
		return 1;
	}
	std::cout << "nick check passed" << std::endl;

	if (params.size() == 2){
		user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
			server.getModeStr(user)).c_str());
		std::cout << "mode is " << server.getModeStr(user) << std::endl;
	}
	std::cout << "modes given" << std::endl;

	size_t forbidden;
	for (size_t i = 0; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALL_MODES);
		if (forbidden != std::string::npos)
			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName()).c_str());
		std::cout << "Unknown MODE flag" << std::endl;
	}
	std::cout << "Unknown mode flags checked" << std::endl;

	std::string additions;
	std::string removals;
	for (size_t i = 1; i < params.size(); i++){
		size_t pos = 0;
		while (pos < params[i].size())
		{
			additions += server.setBatchMode(user, params[i], &pos);
			removals += server.unsetBatchMode(user, params[i], &pos);
			pos++;
		}
	}
	std::cout << "YAAAAAAS" << std::endl;

	std::string reply = ":" + user.getNick() + " MODE " +  user.getNick() + " :+" + additions + "-" + removals;
	user.getSendBuffer().addToBuffer(reply.c_str());
	std::cout << "BYYYYYYEEEEE GUUUUURRRRLL" << std::endl;

	return 0;
}
