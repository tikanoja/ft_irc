/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 09:37:44 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"

Uvector & split( const std::string& str ) {

	Avector				tokens;
	std::istringstream	stream(str);
	std::string			token;
	size_t				i = 0;

	while (!stream.eof())
	{
		std::getline(stream, token, ',');
		tokens[i] = token;
	}
	return (tokens);
}

int cmd_privmsg(IRCServer& server, User& user, Message& message){
	std::string targetNick = message.getParams().front();
	if (targetNick == "") {
			user.getSendBuffer().addToBuffer(ERR_NORECIPIENT(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	Uvector recipients;

	size_t num_recipient = ;

	recipient = server.getUsers().findUserByNick(targetNick);
	if (recipient == NULL) {
		user.getSendBuffer().addToBuffer(ERR_NOSUCHNICK(server.getName(),
			recipient->getNick(), "user").c_str());
		return 1;
	}
	if ((recipient->getMode() >> 0x0001) & 1)
		user.getSendBuffer().addToBuffer(RPL_AWAY(server.getName(),
			recipient->getNick(), recipient->getAwayMsg()).c_str());
	if (message.getTrailing().empty()) {
		user.getSendBuffer().addToBuffer(ERR_NOTEXTTOSEND(server.getName()).c_str());
		return 1;
	}
	
	//tee stringgi
	std::string msg;
	msg = ":" + message.getPrefix() + " PRIVMSG " + targetNick + " :" + message.getTrailing();

	//tunge se stringi tanne
	recipient->getSendBuffer().addToBuffer(msg.c_str());
	(void)user;
	return 0;
}
