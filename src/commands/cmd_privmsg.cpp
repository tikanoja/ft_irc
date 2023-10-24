/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/24 13:01:31 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

int cmd_privmsg(IRCServer& server, User& user, Message& message){
	
	std::string targetNick = message.getParams().front();
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
		message.getCommand()).c_str());
		return 1;
	}
	if (targetNick == "") {
			user.send(ERR_NORECIPIENT(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	
	std::vector<std::string> recipients = split(message.getParams()[0], ',');
	size_t num_recipients = recipients.size();

	for (size_t i = 0; i < num_recipients; i++){
		User* recipient;
		recipient = server.getUsers().findUserByNick(targetNick);
		if (recipient == NULL) {
			user.send(ERR_NOSUCHNICK(server.getName(),
				recipient->getNick(), "user").c_str());
			return 1;
		}
		if ((recipient->getMode() >> IRCServer::away) & 1)
			user.send(RPL_AWAY(server.getName(),
				recipient->getNick(), recipient->getAwayMsg()).c_str());
		if (message.getTrailing().empty()) {
			user.send(ERR_NOTEXTTOSEND(server.getName()).c_str());
			return 1;
		}
		
		//tee stringgi
		std::string msg;
		msg = ":" + message.getPrefix() + " PRIVMSG " + targetNick + " :" + message.getTrailing();

		//tunge se stringi tanne
		recipient->send(msg.c_str());
		(void)user;
	}
	return 0;
}
