/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_topic.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:04 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/24 12:18:27 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	ERRORS
		ERR_NEEDMOREPARAMS		//if missing params
		ERR_NOTONCHANNEL		//the user is not a part of the channel
		ERR_CHANOPRIVSNEEDED	//need op to set topic

	REPLIES
		RPL_NOTOPIC				//topic has not been set
		RPL_TOPIC				//the topic
*/

int chan_cmd_topic(IRCServer& server, User& user, Message& message){
	Channel* chan = server.getChannels().findChannel(message.getParams().front());
	if (chan == NULL) {
		std::cout << "Channel not found! (in chan_cmd_topic())" << std::endl;
		return 1;
	}
	if (message.getTrailing() == "") { //no trailing: they want current topic
		if (chan->getTopic() == "") { //topic has not been set
			user.send(RPL_NOTOPIC(server.getName(), \
			message.getParams().front()));
			return 0;
		}
		user.send(RPL_NOTOPIC(server.getName(), chan->getName())); //sending topic info
		return 0;
	} else { //we have trailing: they want to change topic to a new one
		//check if the new topic complies w protocol
		if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) { //check if they are a part of the channel
			user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
			return 1;
		}
		//check OP mode & send and return if no good :punch.wa.us.dal.net 482 tuukka #test :You're not channel operator
		chan->setTopic(message.getTrailing());
		chan->broadcastToChannel(":" + user.getNick() + \
		"!add_user_host_here TOPIC " + chan->getName() + \
		" :" + message.getTrailing() + "\r\n");
		user.send(RPL_TOPIC(server.getName(), user.getNick(), \
		chan->getName(), chan->getTopic()));
	}
	return 0;
}
