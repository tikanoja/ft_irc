/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:05:15 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/01 13:13:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_quit(IRCServer& server, User& user, Message& message){
	
	close(user.getSocket());

	for (std::vector<Channel*>::iterator it = server.getChannels().begin(); \
		it != server.getChannels().end();){ 
		if ((*it)->getInvitelist()->findUserByNick(user.getNick())) {
			(*it)->removeFromInvlist(user);
			std::cout << "Quitting user removed from invite list!" << std::endl;
		}
		if ((*it)->getMembers()->findUserByNick(user.getNick())) { 
			if ((*it)->getChops()->findUserByNick(user.getNick())) { 
				(*it)->removeFromChops(user);
				std::cout << "Quitting user removed from chops!" << std::endl;
			}
			(*it)->removeFromMembers(user);
			(*it)->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(), user.getIP()) \
				+ " QUIT", &user);
			if (message.getTrailing().empty())
				(*it)->broadcastToChannel("\r\n", &user);
			else
				(*it)->broadcastToChannel(" :" + message.getTrailing() + "\r\n", &user);
			std::cout << "Quitting user removed from channel members!" << std::endl;
		}
		if ((*it)->getMembers()->size() == 0) {
			delete (*it);
			std::vector<Channel*>::iterator itBackup = server.getChannels().erase(it);
			it = itBackup;
			std::cout << "Quit: channel empty, deleted channel!" << std::endl;
		}
		else {
			it++;
		}
	}

	server.delFd(user);
	server.delUser(user);
	delete &user;
	(void)message;
	return 0;
}
