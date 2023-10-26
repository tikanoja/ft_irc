/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:33:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/26 14:23:05 by ttikanoj         ###   ########.fr       */
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
		user.send(ERR_NONICKNAMEGIVEN(server.getName()));
		return 1;
	}
	if (!isNickvalid(new_nick)){
		user.send(ERR_ERRONEUSNICKNAME(server.getName(),
			new_nick));
		return 1;
	}
	if (server.getUsers().findUserByNick(new_nick) != NULL){
		user.send(ERR_NICKNAMEINUSE(server.getName(),
			new_nick));
		return 1;
	}
	if (server.isBlocked(new_nick)){
		user.send(ERR_UNAVAILRESOURCE(server.getName(),
			new_nick, "nick"));
		return 1;
	}
	user.setNick(new_nick);
	//if not registered
	user.setRegistrationFlag(1, user, server);
		//welcome
	return 0;
}
