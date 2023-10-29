/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:05:15 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/10/29 11:29:44 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_quit(IRCServer& server, User& user, Message& message){
	//close fd
	close(user.getSocket());

	//search channels
	for (std::vector<Channel*>::iterator it = server.getChannels().begin(); \
		it != server.getChannels().end(); it++){ //iterate thru chans
		if ((*it)->getInvitelist()->findUserByNick(user.getNick())) {//remove from invitelist
			(*it)->removeFromInvlist(user);
			std::cout << "Quitting user removed from invite list!" << std::endl;
		}
		if ((*it)->getMembers()->findUserByNick(user.getNick())) { //found user on chan
			if ((*it)->getChops()->findUserByNick(user.getNick())) { //remove from chops
				(*it)->removeFromChops(user);
				std::cout << "Quitting user removed from chops!" << std::endl;
			}
			(*it)->removeFromMembers(user);
			std::cout << "Quitting user removed from channel members!" << std::endl;
		}
	}

	//del user from p_pfds
	server.delFd(user);
	
	//del user from p_users
	server.delUser(user);

	//del user
	delete &user;

	//add confirmation to other users on channel! TODO!!
	(void)message;
	return 0;
}
