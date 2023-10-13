/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/12 10:44:54 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"

int cmd_privmsg(IRCServer& server, User& user, Message& message){
	std::string targetNick = message.getParams().front();
	if (targetNick == "") {
		std::cout << "could not find target for privmsg..." << std::endl;
		return 1;
	}
	User* recipient = NULL;
	recipient = server.getUsers().findUserByNick(targetNick);
	if (recipient == NULL) {
		std::cout << "could not find target for privmsg..." << std::endl;
		return 1;
	}
	//tee stringgi
	std::string msg;
	msg = ":" + message.getPrefix() + " PRIVMSG " + targetNick + " :" + message.getTrailing();

	//tunge se stringi tanne
	recipient->getRecvBuffer().addToBuffer(msg.c_str());
	(void)user;
	return 0;
}
