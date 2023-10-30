/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_part.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/30 17:08:51 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	ERRORS
		ERR_NEEDMOREPARAMS		//if missing params
		ERR_NOSUCHCHANNEL		//chan not found
		ERR_NOTONCHANNEL		//the user is not a part of the channel

	EXAMPLES
		PART #twilight_zone
		PART #twilight_zone,&group1
*/

int chan_cmd_part(IRCServer& server, User& user, Message& message){
	if (message.getParams().size() < 1) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), "PART"));
		return 1;
	}
	
	std::stringstream ss(message.getParams().front());
	std::string chan;
	int user_found = 0;
	while (std::getline(ss, chan, ',')) {
		Channel* partFrom = server.getChannels().findChannel(chan);
		if (partFrom == NULL) {
			user.send(ERR_NOSUCHCHANNEL(server.getName(), chan));
			continue ;
		}
		for (std::vector<User*>::iterator it = partFrom->getMembers()->begin();\
		it != partFrom->getMembers()->end(); it++) {
			if ((*it)->getNick() == user.getNick()) {
				partFrom->broadcastToChannel(":" + user.getNick() + "!add_user_host_here" + " PART " + partFrom->getName(), NULL);
				if (message.getTrailing() != "")
					partFrom->broadcastToChannel(" :" + message.getTrailing() + "\r\n", NULL);
				else
					partFrom->broadcastToChannel("\r\n", NULL);
				partFrom->getMembers()->erase(it);
				partFrom->removeFromChops(user);
				if (partFrom->getMembers()->size() == 0) {
					std::cout << "Channel is empty, deleting..." << std::endl;
					server.getChannels().deleteChannel(partFrom);
				}
				user_found = 1;
				break ;
			}
		}
		if (user_found == 0)
			user.send(ERR_NOTONCHANNEL(server.getName(), partFrom->getName()));
		user_found = 0;
	}
	return 1;
}
