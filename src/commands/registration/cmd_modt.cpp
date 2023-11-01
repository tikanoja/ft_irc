/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_modt.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:16:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 13:41:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_modt(IRCServer& server, User& user, Message& message){

	if (user.getMode() & IRCServer::registered)
	{
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}

	std::ifstream stream;
	char 		line[256];

	stream.open("config/motd.config", std::ifstream::in);
	std::string servername = server.getName();
	user.send(RPL_MOTDSTART(servername));
	
	while (stream.getline(line)){
		RPL_MOTD(servername, text)
	}
	
	user.send(RPL_ENDOFMOTD(server.getName()));
	return 0;
}