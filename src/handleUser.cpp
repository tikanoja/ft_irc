/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleUser.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:41 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/05 17:13:38 by djagusch         ###   ########.fr       */
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

void	IRCServer::unsetUserMode(User & user, e_uperm mode){
	try {
		if (user.getNick() == "")
				p_users.findUserByNick(user.getNick())->unsetMode(mode);
			p_users.findUserBySocket(user.getSocket())->unsetMode(mode);
	} catch (std::exception & e){
		/* send error reply, no such user (techically we'd check first the local p_users, then all user list (combined from all servers)
		and only then give the error)*/
	}
	
}

void	IRCServer::setBatchMode(User & user, std::string modes){
	
	if (modes[0] != '+')
	{
		for ( size_t i = 1; i < modes.size(); i++ ){
			switch (modes[i]){
				case ('a'):
					user.setMode(away);
				case ('i'):
					user.setMode(invisible);
				case ('w'):
					user.setMode(wallops);
				case ('r'):
					user.setMode(restricted);
				case ('s'):
					user.setMode(server_notice);
			}
		}
	}

}