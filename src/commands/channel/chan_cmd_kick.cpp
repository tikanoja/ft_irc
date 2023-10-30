/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_kick.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:35:41 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/10/30 13:47:34 by ttikanoj         ###   ########.fr       */
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
	if (message.getParams().size() < 2) { //we need at least a chan & an user!
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}

	std::vector<std::string> channels = split(message.getParams().front(), ',');
	std::vector<std::string> users = split(message.getParams()[1], ',');
	size_t limit;
	if (channels.size() < users.size())
		limit = channels.size();
	else
		limit = users.size();
	for (size_t i = 0; i < limit; i++) {
		Channel* chan = server.getChannels().findChannel(channels[i]);
		if (chan == NULL) { //does the channel they asked for exist ?
			user.send(ERR_NOSUCHCHANNEL(server.getName(), channels[i]));
			continue ;
		}
		if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) { //are we a part of that channel?
			user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
			continue ;
		}
		if (chan->isChop(user) == false) {
			user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
			continue ;
		}

		User* toKick = chan->getMembers()->findUserByNick(users[i]);
		if (toKick == NULL) { //could we find the kickee on the channel ?
			user.send(ERR_NOSUCHNICK(server.getName(), users[i], "nick"));
			continue ;
		}
		chan->broadcastToChannel(":" + user.getNick() + "!add_user_host_here KICK " + chan->getName() + " " + toKick->getNick(), NULL);
		if (message.getTrailing() == "")
			chan->broadcastToChannel("\r\n", NULL);
		else
			chan->broadcastToChannel(" " + message.getTrailing() + "\r\n", NULL);
		for (std::vector<User*>::iterator it = chan->getMembers()->begin();\
			it != chan->getMembers()->end(); it++) {
			if ((*it)->getNick() == users[i]) {
				chan->getMembers()->erase(it);
				break ;
			}
		}
		chan->removeFromChops(*toKick);
	}
	return 0;
}

