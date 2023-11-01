/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_modt.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:16:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 16:19:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_motd(IRCServer& server, User& user, Message& message){

	if (user.getMode() & IRCServer::registered)
	{
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}

	std::ifstream	stream;
	std::string		line;

	stream.open("config/motd.config", std::ifstream::in);
	std::string servername = server.getName();
	user.send(RPL_MOTDSTART(servername));
	
	while (std::getline(stream, line)){
		RPL_MOTD(servername, line);
	}
	
	user.send(RPL_ENDOFMOTD(server.getName()));
	return 0;
}

int cmd_motd(IRCServer& server, User& user){

	if (user.getMode() & IRCServer::registered)
	{
		user.send(ERR_NOTREGISTERED(server.getName(), "MOTD"));
		return 1;
	}

	std::ifstream	stream;
	std::string		line;

	stream.open("config/motd.config", std::ifstream::in);
	std::string servername = server.getName();
	user.send(RPL_MOTDSTART(servername));
	
	while (std::getline(stream, line)){
		user.send(RPL_MOTD(servername, line));
	}
	
	user.send(RPL_ENDOFMOTD(server.getName()));
	return 0;
}