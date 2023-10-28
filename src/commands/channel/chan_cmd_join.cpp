/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_join.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/28 18:58:38 by tuukka           ###   ########.fr       */
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
int checkChannelName(std::string name) {
	if (name.length() > 50)
		return 1;
	if (name.empty() || (name[0] != '#' && name[0] != '&' && name[0] != '!' \
		&& name[0] != '+'))
		return 1;
	size_t limit = name.length();
	for (size_t i = 0; i < limit; i++) {
		if (name[i] == 7 || name[i] == ',' || std::isspace(name[i]))
			return 1;
	}	
	return 0;
}

int chan_cmd_join(IRCServer& server, User& user, Message& message){
	if (!(user.getMode() & IRCServer::registered)) {
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	
	if (message.getParams().size() < 1) { //maybe when missing key as well?
		user.send(ERR_NEEDMOREPARAMS(server.getName(), "JOIN"));
		return 1;
	}
	
	//if user has already joined max limit of channels: ERR_TOOMANYCHANNELS
	std::stringstream ss(message.getParams().front());
	std::string chan;
	while (std::getline(ss, chan, ',')) {
		Channel* toJoin = server.getChannels().findChannel(chan);
		if (toJoin != NULL) { //JOINING AN EXISTING CHANNEL
			//if chan full: ERR_CHANNELISFULL
			//if invite only
				//check channel invitelist for user
					//if no match tell them off
					//if yes match erase name from the list
			if (toJoin->getKeyneeded() == true) {
				if (message.getParams().size() < 2 || \
					message.getParams()[1] != toJoin->getKey()) {
					user.send(ERR_BADCHANNELKEY(server.getName(), user.getNick(), toJoin->getName()));
					return 1;
				}
			}
			toJoin->getMembers()->push_back(&user);
			toJoin->broadcastToChannel(":" + user.getNick() + \
			"!add_user_host_here " + "JOIN :" + toJoin->getName() + "\r\n", NULL);
			if (toJoin->getTopic() != "")
				user.send(RPL_TOPIC(server.getName(), user.getNick(), \
				toJoin->getName(), toJoin->getTopic()));
			else
				user.send(RPL_NOTOPIC(server.getName(), toJoin->getName()));
		} else { //CREATING NEW CHANNEL
			//check if the channel name is valid! If not, send err_nosuchchannel(???)
			if (checkChannelName(chan) == 1) {
				user.send(ERR_NOSUCHCHANNEL(server.getName(), chan));
				return 1;
			}
			toJoin = server.getChannels().createChannel(chan);
			toJoin->getMembers()->push_back(&user);
			toJoin->getChops()->push_back(&user); //add channel creator to channel operators (add OG chanop flag ?)
			//add chop to user?
			toJoin->broadcastToChannel(":" + user.getNick() + \
			"!add_user_host_here " + "JOIN :" + toJoin->getName() + "\r\n", NULL);
		}
	}
	return 0;
}
