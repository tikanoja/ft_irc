/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:33:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 16:52:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*         ERR_NONICKNAMEGIVEN             ERR_ERRONEUSNICKNAME
           ERR_NICKNAMEINUSE               ERR_NICKCOLLISION
           ERR_UNAVAILRESOURCE             ERR_RESTRICTED */




/*   { => [
	} => ] 
	| => \
	^ =>  ~ */


bool	isNickvalid(std::string & nick){
	
}

int cmd_nick(IRCServer& server, User &user, Message &message){
	
	std::string new_nick = message.getParams()[0];
	
	if (new_nick.empty())
		user.getSendBuffer().addToBuffer(ERR_NONICKNAMEGIVEN(server.getName()).c_str());
	if (!isNickvalid(new_nick))
		user.getSendBuffer().addToBuffer(ERR_ERRONEUSNICKNAME(server.getName(), new_nick).c_str());
	if (server.getUsers().findUserByNick(new_nick) != NULL)
		user.getSendBuffer().addToBuffer(ERR_NICKNAMEINUSE(server.getName(),
			new_nick).c_str());
}