/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:41 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 16:12:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

bool IRCServer::getUserMode(User & user, e_uperm mode) const{
	try {
		if (!user.getNick().empty())
			return users.findUserByNick(user.getNick())->getMode() & mode;
		return users.findUserBySocket(user.getSocket())->getMode() & mode;
	} catch (std::exception & e){
		/* send error reply, no such user (techically we'd check first the local users, then all user list (combined from all servers)
		and only then give the error)*/
	}
}

void IRCServer::setUserMode(User & user, e_uperm mode){
	try {
		if (user.getNick() == "")
				users.findUserByNick(user.getNick())->setMode(mode);
			users.findUserBySocket(user.getSocket())->setMode(mode);
	} catch (std::exception & e){
		/* send error reply, no such user (techically we'd check first the local users, then all user list (combined from all servers)
		and only then give the error)*/
	}
}
