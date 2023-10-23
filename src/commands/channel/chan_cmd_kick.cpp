/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_kick.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 09:35:41 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/10/23 09:55:44 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	ERRORS
		ERR_NOSUCHCHANNEL		403 !
		ERR_NOTONCHANNEL		442
		ERR_NEEDMOREPARAMS		461 !
		ERR_BADCHANMASK			476
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
	if (message.getParams().size() < 2) { //we need at least a chan & an user!
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}
	Channel* chan = server.getChannels().findChannel(message.getParams().front());
	if (chan == NULL) {
		user.send(ERR_NOSUCHCHANNEL(server.getName(), message.getParams().front()));
		return 1;
	}
	if (chan->getMembers()->findUserByNick(message.getParams()[1]) == NULL) {
		//????
	}
	return 0;
}
