/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:44:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/30 16:35:42 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

//USER guest 0 * :Ronnie Reagan

int cmd_user(IRCServer& server, User& user, Message& message){
	if (user.getPassFlag() == false) {
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return 1;
	}
	// if (user.getNick().empty()){
	// 	// user.send(ERR_NONICKNAMEGIVEN(server.getName()));
	// 	return 1;
	// }
	if (message.getParams()[2].empty() || message.getTrailing().empty()){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (server.getUserMode(user, IRCServer::registered)){
		user.send(ERR_ALREADYREGISTRED(server.getName()));
		return 1;
	}
	user.setUserName(message.getParams()[0]);
	user.setRealName(message.getParams()[1]);
	if (message.getParams()[2] == "2")
		user.setMode(IRCServer::wallops);
	if (message.getParams()[2] == "8")
		user.setMode(IRCServer::invisible);
	// user.setMode(IRCServer::registered);
	// user.send(RPL_WELCOME(server.getName(), user.getNick(), user.getUserName(), "127.0.0.1"));

	user.setRegistrationFlag(2, user, server);

	return 0;
}
