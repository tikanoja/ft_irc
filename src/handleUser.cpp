/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:41 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/05 09:11:37 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

bool IRCServer::getUserMode(User & user, e_uperm mode) const{
	try {
		if (!user.getNick().empty())
			return p_users.findUserByNick(user.getNick())->getMode() & mode;
		return p_users.findUserBySocket(user.getSocket())->getMode() & mode;
	} catch (std::exception & e){
		
		return false;
		/* send error reply, no such user (techically we'd check first the local p_users, then all user list (combined from all servers)
		and only then give the error)*/
	}
}

void IRCServer::setUserMode(User & user, e_uperm mode){
	try {
		if (user.getNick() == "")
				p_users.findUserByNick(user.getNick())->setMode(mode);
			p_users.findUserBySocket(user.getSocket())->setMode(mode);
	} catch (std::exception & e){
		/* send error reply, no such user (techically we'd check first the local p_users, then all user list (combined from all servers)
		and only then give the error)*/
	}
}
