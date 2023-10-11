/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mode.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:06:43 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/11 11:41:05 by djagusch         ###   ########.fr       */
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


# define SETTABLE_MODES "iwroO"

// int cmd_mode(IRCServer& server, User& user, Message& message){
	
// 	if (message.getParams().size() < 1){
// 		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
// 			message.getCommand()).c_str());
// 		return 1;
// 	}
// 	if (message.getSender()->getNick() != message.getParams()[0]){
// 		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
// 		return 1;
// 	}

// 	std::string additions;
// 	std::string removals;
// 	for (size_t i = 1; i < message.getParams().size(); i++){
// 		if (message.getParams()[i][0] != '+' || message.getParams()[i][0]  != '-'){
// 			continue;
// 		}
// 		size_t forbidden;
// 		if (message.getParams()[i][0] != '+' && message.getParams()[i][0] != '-')
// 			forbidden = message.getParams()[i].substr(1).find_first_not_of(SETTABLE_MODES);
// 		if (forbidden != std::string::npos){
// 			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName()).c_str());
// 			continue;
// 		}
// 		additions += server.setBatchMode(user, message.getParams()[i]);
// 		removals += server.unsetBatchMode(user, message.getParams()[i]);
// 	}
// 	user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
// 		server.printModeStr(user)).c_str());
// 	return 0;
// }

// int cmd_mode(IRCServer& server, User& user, Message& message){
	
// 	if (message.getParams().size() < 1){
// 		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
// 			message.getCommand()).c_str());
// 		return 1;
// 	}
// 	if (message.getSender()->getNick() != message.getParams()[0]){
// 		user.getSendBuffer().addToBuffer(ERR_USERSDONTMATCH(server.getName()).c_str());
// 		return 1;
// 	}

// 	std::string additions;
// 	std::string removals;
// 	for (size_t i = 1; i < message.getParams().size(); i++){
// 		if (message.getParams()[i][0] != '+' || message.getParams()[i][0]  != '-'){
// 			continue;
// 		}
// 		size_t forbidden;
// 		if (message.getParams()[i][0] != '+' && message.getParams()[i][0] != '-')
// 			forbidden = message.getParams()[i].substr(1).find_first_not_of(SETTABLE_MODES);
// 		if (forbidden != std::string::npos){
// 			user.getSendBuffer().addToBuffer(ERR_UMODEUNKNOWNFLAG(server.getName()).c_str());
// 			continue;
// 		}
// 		additions += server.setBatchMode(user, message.getParams()[i]);
// 		removals += server.unsetBatchMode(user, message.getParams()[i]);
// 	}
// 	user.getSendBuffer().addToBuffer(RPL_UMODEIS(server.getName(),
// 		server.printModeStr(user)).c_str());
// 	return 0;
// }