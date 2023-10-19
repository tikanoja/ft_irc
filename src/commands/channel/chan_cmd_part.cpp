/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_part.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:01 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/19 12:11:11 by ttikanoj         ###   ########.fr       */
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
	if (message.getParams().front() == "") {
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
		//check if user is present in the channel
		for (std::vector<User*>::iterator it = partFrom->getMembers()->begin();\
		it != partFrom->getMembers()->end(); it++) {
			if ((*it)->getNick() == user.getNick()) {
				partFrom->getMembers()->erase(it);
				user.send(":" + user.getNick() + "!add_user_host_here" + " PART " + partFrom->getName());
				if (message.getTrailing() != "")
					user.send(" :" + message.getTrailing() + "\r\n"); //add userhost? add trailing message? check out log from dalnet
				else
					user.send("\r\n");
				user_found = 1;
				break ;
			}
		}
		if (user_found == 0)
			user.send(ERR_NOTONCHANNEL(server.getName(), partFrom->getName()));
		user_found = 0;
	}
	//if yes then get rid of them
	return 1;
}

//make this work with a list of channels to part from!!!!!!!!!!
