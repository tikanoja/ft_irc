/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 10:23:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

//    Command: KILL
//    Parameters: <nickname> <comment>

int cmd_kill(IRCServer& server, User& user, Message& message){

	User *toBeKilled = server.getUsers().findUserByNick(user.getNick());

	if (user.getMode() & 0x0080){
		user.getSendBuffer().addToBuffer(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	if ((user.getMode() & 0x0010) || (user.getMode() & 0x0020)){
		user.getSendBuffer().addToBuffer(ERR_NOPRIVILEGES(server.getName()).c_str());
		return 1;
	}
	if (!toBeKilled){
		user.getSendBuffer().addToBuffer(ERR_NOSUCHNICK(server.getName(),
			user.getNick(), "user").c_str());
		return 1;
	}
	if (message.getParams()[0].empty() || message.getParams()[1].empty()){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	close(user.getSocket()); //might need refinement, my hope is that
	/// when we close, we continue into the polling loop, and catch the closed fd
	// with POLLERR or POLLNVAL. Alternatively, we can call a version of dropConnection
	// and do the clean up right here.
	return 0;
}
