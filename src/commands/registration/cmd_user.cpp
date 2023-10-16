/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:44:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 10:33:48 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

//USER guest 0 * :Ronnie Reagan

int cmd_user(IRCServer& server, User& user, Message& message){
	if (message.getParams()[2].empty() || message.getTrailing().empty()){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	if (server.getUserMode(user, static_cast<IRCServer::e_uperm>(0x0080))){
		user.getSendBuffer().addToBuffer(ERR_ALREADYREGISTRED(server.getName()).c_str());
		return 1;
	}
	user.setUserName(message.getParams()[0]);
	user.setRealName(message.getParams()[1]);
	if (message.getParams()[2] == "2")
		user.setMode(static_cast<IRCServer::e_uperm>(0x0002));
	if (message.getParams()[2] == "8")
		user.setMode(static_cast<IRCServer::e_uperm>(0x0004));
	user.setMode(static_cast<IRCServer::e_uperm>(0x0080));
	user.getSendBuffer().addToBuffer(RPL_WELCOME(server.getName(), user.getNick(), user.getUserName(), "127.0.0.1").c_str());
	return 0;
}
