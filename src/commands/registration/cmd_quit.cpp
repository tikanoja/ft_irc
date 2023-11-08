/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:05:15 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/08 10:16:28 by ttikanoj         ###   ########.fr       */
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
			}
			(*it)->removeFromMembers(user);
			(*it)->reopChannel(server.getName());
			(*it)->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(), user.getIP()) \
				+ " QUIT", &user);
			if (message.getTrailing().empty())
				(*it)->broadcastToChannel("\r\n", &user);
			else
				(*it)->broadcastToChannel(" :" + message.getTrailing() + "\r\n", &user);
		}
		if ((*it)->getMembers()->size() == 0) {
			std::cout << COLOR_YELLOW << "Deleting channel " << (*it)->getName();
			delete (*it);
			std::vector<Channel*>::iterator itBackup = server.getChannels().erase(it);
			it = itBackup;
			std::cout << ". Active channels on server: " << server.getChannels().size() << COLOR_END << std::endl;
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
