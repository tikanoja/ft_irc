/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_motd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:16:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 14:09:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_motd(IRCServer& server, User& user, Message& message){

	if (!(user.getMode() & IRCServer::registered))
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
	stream.close();
	return 0;
}

int motd(IRCServer& server, User& user){

	if (!(user.getMode() & IRCServer::registered))
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
	stream.close();
	return 0;
}
