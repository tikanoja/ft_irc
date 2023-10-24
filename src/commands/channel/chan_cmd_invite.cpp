/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_invite.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:21 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/24 10:00:56 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	ERROR
		ERR_NEEDMOREPARAMS		!
		ERR_NOSUCHNICK			!
		ERR_NOTONCHANNEL		!
		ERR_USERONCHANNEL		!
		ERR_CHANOPRIVNEEDED
		
	REPLIES
		RPL_INVITING
		RPL_AWAY

	EXAMPLES
		:Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel #Dust
		INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to #Twilight_zone
*/

int chan_cmd_invite(IRCServer& server, User& user, Message& message){
	if (message.getParams().size() < 2) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}
	Channel* chan = server.getChannels().findChannel(message.getParams()[1]);
	if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) { //is the inviter on the channel they are inviting to
		user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
		return 1;
	}

	//check if the inviter is chanop!

	if (chan == NULL) { //does channel exist
		user.send(ERR_NOSUCHNICK(server.getName(), message.getParams()[1], "channel"));
		return 1;
	}
	User* invited = chan->getMembers()->findUserByNick(message.getParams().front());
	if (invited == NULL) { //does nick exist
		user.send(ERR_NOSUCHNICK(server.getName(), message.getParams().front(), "nick"));
		return 1;
	}
	if (chan->getMembers()->findUserByNick(message.getParams().front()) != NULL) { //is the user already on the channel
		user.send(ERR_USERONCHANNEL(server.getName(), message.getParams().front(), chan->getName()));
		return 1;
	}
	
	//perform the invite!
	//check if user is already on the guestlist
	if (chan->getGuestlist()->findUserByNick(message.getParams().front()) != NULL) {
		return 1;
	}
	chan->getGuestlist()->push_back(invited); //add user to guestlist
	return 0;
}
