/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_join.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/03 09:17:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../../inc/Commands.hpp"
/*
	ERRORS
		ERR_NEEDMOREPARAMS		//if missing params
		ERR_BANNEDFROMCHAN		//trying to join a chan you are banned from
		ERR_INVITEONLYCHAN		//trying to join a chan that is set to invite only without inv
		ERR_BADCHANNELKEY		//wrong key (pw)
		ERR_CHANNELISFULL		//channel is full...
		ERR_BADCHANMASK			//not in use!!!!!?
		ERR_NOSUCHCHANNEL		//given channel name is invalid
		ERR_TOOMANYCHANNELS		//when the user has joined max amount of channels and tries to join another
		ERR_TOOMANYTARGETS		//Returned to a client which is attempting to send a PRIVMSG/NOTICE using the user@host destination format and for a user@host which has several occurrences
		ERR_UNAVAILRESOURCE		// Returned by a server to a user trying to join a channel currently blocked by the channel delay mechanism.

	REPLIES
		RPL_TOPIC				//sent upon successful JOIN
*/

static int checkChannelName(std::string name);
static bool checkPermissions(IRCServer& server, User& user, Message& message, Channel * toJoin);

int chan_cmd_join(IRCServer& server, User& user, Message& message){
	if (!(user.getMode() & IRCServer::registered)) {
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	if (message.getParams().size() < 1) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), "JOIN"));
		return 1;
	}
	
	std::stringstream ss(message.getParams().front());
	std::string chan;
	while (std::getline(ss, chan, ',')) {
		Channel* toJoin = server.getChannels().findChannel(chan);
		
		if (toJoin != NULL) { //JOINING AN EXISTING CHANNEL
			if (!checkPermissions(server, user, message, toJoin))
				continue ;
				
			toJoin->getMembers()->push_back(&user);
			toJoin->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),\
				user.getIP()) + " JOIN :" + toJoin->getName() + "\r\n", NULL);
			if (toJoin->getTopic() != "")
				user.send(RPL_TOPIC(server.getName(), user.getNick(), \
				toJoin->getName(), toJoin->getTopic()));
			else
				user.send(RPL_NOTOPIC(server.getName(), toJoin->getName()));
		} else {
			if (checkChannelName(chan) == 1) {
				user.send(ERR_NOSUCHCHANNEL(server.getName(), user.getNick(), chan));
				continue ;
			}
			toJoin = server.getChannels().createChannel(chan);
			toJoin->getMembers()->push_back(&user);
			toJoin->getChops()->push_back(&user);
			toJoin->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),\
				user.getIP()) + " JOIN :" + toJoin->getName() + "\r\n", NULL);
		}
	}
	return 0;
}

static int checkChannelName(std::string name) {
	if (name.length() > 50)
		return 1;
	if (name.empty() || (name[0] != '#' && name[0] != '&'))
		return 1;
	size_t limit = name.length();
	for (size_t i = 0; i < limit; i++) {
		if (name[i] == 7 || name[i] == ',' || std::isspace(name[i]))
			return 1;
	}	
	return 0;
}


static bool checkPermissions(IRCServer& server, User& user, Message& message, Channel * toJoin){

	if (toJoin->getMode() & Channel::key) {
		if (message.getParams().size() < 2 || \
			message.getParams()[1] != toJoin->getKey()) {
			user.send(ERR_BADCHANNELKEY(server.getName(), user.getNick(),\
				toJoin->getName()));
			return false;
		}
	}
	if (toJoin->getMode() & Channel::limit && \
		toJoin->getMembers()->size() == toJoin->getMaxusers()) {
		user.send(ERR_CHANNELISFULL(server.getName(), user.getNick(),\
			toJoin->getName()));
	return false;
	}
	if (toJoin->getMode() & Channel::invite) {
		if (toJoin->getInvitelist()->findUserByNick(user.getNick()) == NULL) {
			user.send(ERR_INVITEONLYCHAN(server.getName(), user.getNick(),\
				toJoin->getName()));
			return false;
		}
		toJoin->removeFromInvlist(user);
	}
	if (toJoin->getMembers()->findUserByNick(user.getNick()) != NULL) {
		user.send(ERR_USERONCHANNEL(server.getName(), user.getNick(),\
			toJoin->getName()));
		return false;
	}
	return true;
}
