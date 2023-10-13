/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:33:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/12 14:11:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

bool	isNickvalid(std::string & nick){

	if (nick[0] == '$' || nick[0] == ':' || nick[0] == '#')
		return false;

	if (nick.find_first_of(",*?! @.", 0) != std::string::npos)
		return false;

	return true;
}

int cmd_nick(IRCServer& server, User& user, Message& message){

	std::string new_nick = message.getParams()[0];

	if (new_nick.empty()){
		user.getSendBuffer().addToBuffer(ERR_NONICKNAMEGIVEN(server.getName()).c_str());
		return 1;
	}
	if (!isNickvalid(new_nick)){
		user.getSendBuffer().addToBuffer(ERR_ERRONEUSNICKNAME(server.getName(),
			new_nick).c_str());
		return 1;
	}
	if (server.getUsers().findUserByNick(new_nick) != NULL){
		user.getSendBuffer().addToBuffer(ERR_NICKNAMEINUSE(server.getName(),
			new_nick).c_str());
		return 1;
	}
	if (server.isBlocked(new_nick)){
		user.getSendBuffer().addToBuffer(ERR_UNAVAILRESOURCE(server.getName(),
			new_nick, "nick").c_str());
		return 1;
	}
	user.setNick(new_nick);
	return 0;
}
