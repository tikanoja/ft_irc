/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_kick.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:35:41 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/10/23 13:59:37 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

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
	
	//check user permissions and send 482 & return 1 if necessary!

	if (message.getParams().size() < 2) { //we need at least a chan & an user!
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}
	Channel* chan = server.getChannels().findChannel(message.getParams().front());
	if (chan == NULL) { //does the channel they asked for exist ?
		user.send(ERR_NOSUCHCHANNEL(server.getName(), message.getParams().front()));
		return 1;
	}
	if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) { //are we a part of that channel?
		user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
		return 1;
	}
	//do we have oper????????
	User* toKick = chan->getMembers()->findUserByNick(message.getParams()[1]);
	if (toKick == NULL) { //could we find the kickee on the channel ?
		user.send(ERR_NOSUCHNICK(server.getName(), message.getParams()[1], "nick"));
		return 1;
	}

	//perform the kick!
		//let the channel know about the kick
	chan->broadcastToChannel(":" + user.getNick() + "!add_user_host_here KICK " + chan->getName() + " " + toKick->getNick());
	if (message.getTrailing() == "")
		chan->broadcastToChannel("\r\n");
	else
		chan->broadcastToChannel(" " + message.getTrailing() + "\r\n");
	
		//remove user from the channel vector
		//make a channel function to remove user by name...! can be reused in part
	for (std::vector<User*>::iterator it = chan->getMembers()->begin();\
		it != chan->getMembers()->end(); it++) {
		if ((*it)->getNick() == message.getParams()[1]) {
			chan->getMembers()->erase(it);
			break ;
		}
	}

	//make this work in a loop!!!!!!!!!!!!!
	return 0;
}
