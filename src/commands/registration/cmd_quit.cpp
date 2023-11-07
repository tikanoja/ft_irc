/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:05:15 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/07 08:21:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_quit(IRCServer& server, User& user, Message& message){
	
	close(user.getSocket());

	for (std::vector<Channel*>::iterator it = server.getChannels().begin(); \
		it != server.getChannels().end();){ 
		if ((*it)->getInvitelist()->findUserByNick(user.getNick())) {
			(*it)->removeFromInvlist(user);
		}
		if ((*it)->getMembers()->findUserByNick(user.getNick())) { 
			if ((*it)->getChops()->findUserByNick(user.getNick())) {
				(*it)->removeFromChops(user);
				(*it)->reopChannel(server.getName());
			}
			(*it)->removeFromMembers(user);
			(*it)->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(), user.getIP()) \
				+ " QUIT", &user);
			if (message.getTrailing().empty())
				(*it)->broadcastToChannel("\r\n", &user);
			else
				(*it)->broadcastToChannel(" :" + message.getTrailing() + "\r\n", &user);
		}
		if ((*it)->getMembers()->size() == 0) {
			delete (*it);
			std::vector<Channel*>::iterator itBackup = server.getChannels().erase(it);
			it = itBackup;
		}
		else {
			it++;
		}
	}
	server.log("Removed " + user.getNick(), __FILE__, __LINE__);
	server.delFd(user);
	server.delUser(user);
	(void)message;
	return 0;
}
