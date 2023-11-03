/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_kick.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:35:41 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/03 13:07:49 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"
#include "../../../inc/Utils.hpp"

/*
	ERRORS
		ERR_NOSUCHCHANNEL		403 !
		ERR_NOTONCHANNEL		442 !
		ERR_NEEDMOREPARAMS		461 !
		ERR_BADCHANMASK			476 ??? "non-generic feature"
		ERR_CHANOPRIVSNEEDED	482

	EXAMPLES
		KICK &Melbourne Matthew					; Kick Matthew from &Melbourne
		KICK #Finnish John :Speaking English	; Kick John from #Finnish using
                                				"Speaking English" as the reason
                                				(comment).
		:WiZ KICK #Finnish John					; KICK message from WiZ to remove John
                                				from channel #Finnish
*/

int chan_cmd_kick(IRCServer& server, User& user, Message& message){
	if (!(user.getMode() & IRCServer::registered)) {
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	if (message.getParams().size() < 2) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}
	
	std::vector<std::string> channels = split(message.getParams().front(), ',');
	std::vector<std::string> users = split(message.getParams().at(1), ',');
	size_t limit = users.size();
	Channel* chan = NULL;
	for (size_t i = 0; i < limit; i++) {
		if (i == 0 || channels.size() > 1)
			chan = server.getChannels().findChannel(channels[i]);
		if (chan == NULL) {
			user.send(ERR_NOSUCHCHANNEL(server.getName(), user.getNick(),
				channels[i]));
			continue ;
		}
		if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) {
			user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
			continue ;
		}
		if (chan->isChop(user) == false) {
			user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
			continue ;
		}

		User* toKick = chan->getMembers()->findUserByNick(users[i]);
		if (toKick == NULL) {
			user.send(ERR_NOSUCHNICK(server.getName(), users[i], "nick"));
			continue ;
		}
		chan->broadcastToChannel(":" + USER_ID(user.getNick(), user.getUserName(),
			user.getIP()) + " KICK " + chan->getName() + " " +
			toKick->getNick() + " :" + user.getNick(), NULL);
		if (message.getTrailing() == "")
			chan->broadcastToChannel("\r\n", NULL);
		else
			chan->broadcastToChannel(" " + (message.getTrailing().empty()? message.getTrailing() : "") + "\r\n", NULL);
		for (std::vector<User*>::iterator it = chan->getMembers()->begin();\
			it != chan->getMembers()->end(); it++) {
			if ((*it)->getNick() == toKick->getNick()) {
				chan->getMembers()->erase(it);
				break ;
			}
		}
		chan->removeFromChops(*toKick);
		if (chan->getMembers()->size() == 0) {
				server.log("Deleted " + chan->getName(), __FILE__, __LINE__);
				server.getChannels().deleteChannel(chan);
		}
	}
	return 0;
}

