/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_join.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/04 15:22:34 by djagusch         ###   ########.fr       */
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

static void removeUserFromAllChannels(IRCServer& server, User& user, Message& message);
static int checkChannelName(std::string name);
static bool checkPermissions(IRCServer& server, User& user,
	std::vector<std::string> const &params, Channel * toJoin, std::string const & key);

int chan_cmd_join(IRCServer& server, User& user, Message& message){
	
	std::vector<std::string> const & params = message.getParams();
	
	if (!(user.getMode() & IRCServer::registered)) {
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	if (params.size() < 1) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), "JOIN"));
		return 1;
	}
	if (params.front() == "0"){
		removeUserFromAllChannels(server, user, message);
		return 0;
	}
	if (params.size() > 1){
		ssize_t n_chan = std::count(params[0].begin(), params[0].end(), ',');
		ssize_t n_key = std::count(params[1].begin(), params[1].end(), ',');
		if (n_chan != n_key){
			user.send(ERR_NEEDMOREPARAMS(server.getName(), "JOIN"));
			return 1;
		}
	}

	std::stringstream ss(params.front());
	std::string chan;
	std::stringstream key_ss;
	std::string key = "";
	if (params.size() > 1){
		key_ss << params.at(1);
	}
	while (std::getline(ss, chan, ',') || (params.size() > 1 && std::getline(key_ss, key, ','))) {
		Channel* toJoin = server.getChannels().findChannel(chan);
		
		if (toJoin != NULL) {
			if (!checkPermissions(server, user, params, toJoin, key))
				continue ;
				
			toJoin->getMembers()->push_back(&user);
			toJoin->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),\
				user.getIP()) + " JOIN :" + toJoin->getName() + "\r\n", NULL);
			if (toJoin->getTopic() != "")
				user.send(RPL_TOPIC(server.getName(), user.getNick(), \
				toJoin->getName(), toJoin->getTopic()));
			else
				user.send(RPL_NOTOPIC(server.getName(), toJoin->getName()));
			std::string userList = toJoin->getNicks();
			user.send(RPL_NAMREPLY(server.getName(), user.getNick(), toJoin->getName(), userList));
			user.send(RPL_ENDOFNAMES(server.getName(), user.getNick(), toJoin->getName()));
		} else {
			if (checkChannelName(chan) == 1) {
				user.send(ERR_NOSUCHCHANNEL(server.getName(), user.getNick(), chan));
				continue ;
			}
			toJoin = server.getChannels().createChannel(chan);
			toJoin->getMembers()->push_back(&user);
			toJoin->getChops()->push_back(&user);
			if (params.size() > 1){
				toJoin->setKey(key);
				toJoin->setMode(Channel::key);
				toJoin->broadcastToChannel(RPL_CHANNELMODEIS(server.getName(), user.getNick(),
					toJoin->getName(), "+k", key), NULL);
			}
			toJoin->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),\
				user.getIP()) + " JOIN :" + toJoin->getName() + "\r\n", NULL);
		}
	}
	return 0;
}

static void removeUserFromAllChannels(IRCServer& server, User& user, Message& message){

	Cvector channels = server.getChannels().findChannelsByUser(user.getNick());

	for (Cvector::iterator it = channels.begin(); it != channels.end(); it++){
		if (user.getNick() == user.getNick()) {
			(*it)->broadcastToChannel(":" + USER_ID(user.getNick(),
			user.getUserName(), user.getIP()) + " PART " + (*it)->getName(), NULL);
		}
		if (!message.getTrailing().empty())
			(*it)->broadcastToChannel(" :" + message.getTrailing() + "\r\n", NULL);
		else
			(*it)->broadcastToChannel("\r\n", NULL);

		(*it)->getMembers()->removeUserByNick(user.getNick());
		(*it)->removeFromChops(user);
		(*it)->reopChannel(server.getName());
		if ((*it)->getMembers()->size() == 0) {
			server.getChannels().deleteChannel((*it));
		}
	}
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

static bool checkPermissions(IRCServer& server, User& user,
	std::vector<std::string> const & params, Channel * toJoin, std::string const & key){

	if (toJoin->getMode() & Channel::key) {
		if (params.size() < 2 || \
			key != toJoin->getKey()) {
			user.send(ERR_BADCHANNELKEY(server.getName(), user.getNick(),\
				toJoin->getName()));
			return false;
		}
	}
	if (toJoin->getMode() & Channel::limit && \
		(toJoin->getMembers()->size() >= toJoin->getMaxusers() || toJoin->getMaxusers() == 0)) {
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
