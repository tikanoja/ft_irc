/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_invite.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:21 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/04 13:17:50 by djagusch         ###   ########.fr       */
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

static bool checkPermission(IRCServer & server, User & user, Message const & message,
	Channel ** chan, User ** invited);

int chan_cmd_invite(IRCServer& server, User& user, Message& message){
	
	Channel* chan = NULL;
	User* invited = NULL;

	if (!checkPermission(server, user, message, &chan, &invited))
		return 1;
	chan->getInvitelist()->push_back(invited);
	user.send(RPL_INVITING(server.getName(), user.getNick(), invited->getNick(), chan->getName()));
	invited->send(":" + USER_ID(user.getNick(), user.getUserName(), user.getIP())+ " INVITE " \
		+ invited->getNick() + " :" + chan->getName() + "\r\n");
	return 0;
}

//confirmation to the inviter and notice to the invited!

static bool checkPermission(IRCServer & server, User & user, Message const & message,
	Channel ** chan, User ** invited){
		
	if (!(user.getMode() & IRCServer::registered)) {
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return false;
	}
	if (message.getParams().size() < 2) {
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return false;
	}
	(*chan) = server.getChannels().findChannel(message.getParams()[1]);
	if ((*chan) == NULL) {
		user.send(ERR_NOSUCHNICK(server.getName(), message.getParams()[1], "channel"));
		return false;
	}
	if ((*chan)->getMembers()->findUserByNick(user.getNick()) == NULL) {
		user.send(ERR_NOTONCHANNEL(server.getName(), (*chan)->getName()));
		return false;
	}
	if ((*chan)->getMode() & Channel::invite && (*chan)->isChop(user) == false) {
		user.send(ERR_CHANOPRIVSNEEDED(server.getName(), (*chan)->getName()));
		return false;
	}
	*invited = server.getUsers().findUserByNick(message.getParams().front());
	if ((*invited) == NULL) {
		user.send(ERR_NOSUCHNICK(server.getName(), message.getParams().front(), "nick"));
		return false;
	}
	if ((*invited)->getMode() & IRCServer::away) {
		user.send(RPL_AWAY(server.getName(), user.getNick(), (*invited)->getNick(), (*invited)->getAwayMsg()));
		return false;
	}
	if ((*chan)->getMembers()->findUserByNick((*invited)->getNick()) != NULL) {
		user.send(ERR_USERONCHANNEL(server.getName(), (*invited)->getNick(), (*chan)->getName()));
		return false;
	}
	if ((*chan)->getInvitelist()->findUserByNick((*invited)->getNick()) != NULL) {
		return false;
	}
	return true;
}
