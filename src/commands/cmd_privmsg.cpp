/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/25 09:36:42 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

int cmd_privmsg(IRCServer& server, User& user, Message& message){
	
	std::string targetNick = message.getParams().front();
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
		message.getCommand()));
		return 1;
	}
	if (targetNick == "") {
			user.send(ERR_NORECIPIENT(server.getName(),
			message.getCommand()));
		return 1;
	}
	
	std::vector<std::string> recipients = split(message.getParams()[0], ',');
	size_t num_recipients = recipients.size();

	for (size_t i = 0; i < num_recipients; i++){
		User* recipient;
		recipient = server.getUsers().findUserByNick(targetNick);
		if (recipient == NULL) {
			user.send(ERR_NOSUCHNICK(server.getName(),
				message.getParams()[0], "user"));
			return 1;
		}
		if (recipient->getMode() & IRCServer::away)
			user.send(RPL_AWAY(server.getName(),
				recipient->getNick(), recipient->getAwayMsg()));
		if (message.getTrailing().empty()) {
			user.send(ERR_NOTEXTTOSEND(server.getName()));
			return 1;
		}
		
		//tee stringgi
		std::string msg;
		msg = ":" + message.getPrefix() + " PRIVMSG " + targetNick + " :" + message.getTrailing() + "\r\n";

		//tunge se stringi tanne
		recipient->send(msg);
		(void)user;
	}
	return 0;
}
