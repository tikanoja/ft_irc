/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_topic.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:04 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 13:36:06 by ttikanoj         ###   ########.fr       */
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
		user.send(ERR_NOSUCHCHANNEL(server.getName(), user.getNick(), message.getParams().front()));
		return 1;
	}
	if (message.getTrailing().empty()) {
		if (chan->getTopic().empty()) {
			user.send(RPL_NOTOPIC(server.getName(), \
			message.getParams().front()));
			return 0;
		}
		user.send(RPL_TOPIC(server.getName(), user.getNick(), chan->getName(),
			chan->getTopic()));
		return 0;
	} else {
		if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) {
			user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
			return 1;
		}
		
		if ((chan->getMode() & Channel::topic_rest) && chan->isChop(user) == false) {
			user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
			return 1;
		}
		if (message.getTrailing() == "\"\"")
			chan->setTopic("");
		else
			chan->setTopic(message.getTrailing());
		chan->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),
		 user.getIP()) + " TOPIC " + chan->getName() + \
			" :" + chan->getTopic() + "\r\n", NULL);
		user.send(RPL_TOPIC(server.getName(), user.getNick(), \
		chan->getName(), chan->getTopic()));
	}
	return 0;
}
