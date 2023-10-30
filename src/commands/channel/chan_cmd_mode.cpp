/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_mode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/30 16:59:35 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	ERRORS
		ERR_NEEDMOREPARAMS
		ERR_KEYSET
		ERR_NOCHANMODES
		ERR_CHANOPRIVSNEEDED
		ERR_USERNOTINCHANNEL
		ERR_UNKNOWNMODE
		
	REPLIES
		RPL_CHANNELMODEIS
		RPL_BANLIST
		RPL_ENDOFBANLIST
		RPL_EXCEPTLIST
		RPL_ENDOFEXCEPTLIST
		RPL_INVITELIST
		RPL_ENDOFINVITELIST
		RPL_UNIQOPIS

	MODES
		i	set/remove invite only channel
		t	set/remove topic setting for chop/reg
		k	set/remove channel key
		o	set/remove chop priviledge
		l	set/remove user limit on channel
	
	USAGE
		/mode #channel +mode modeparam
*/


void execChanMode(IRCServer& server, User& user, Channel* chan, \
				std::string mode, std::string modeparam) { //this needs to return something in case the command fails
	bool status;
	if (mode[0] == '+')
		status = true;
	else
		status = false;
	switch (mode[1]){
		case ('i'):
			chan->toggleInviteonly(status);
			break;
		case ('t'):
			chan->toggleTopicrestricted(status);
			break;
		case ('k'):
			chan->toggleKeyneeded(status, modeparam);
			break;
		case ('o'):
			chan->toggleChoprights(status, modeparam, chan);
			break;
		case ('l'):
			chan->toggleUserlimit(status, modeparam);
			break;
		default:
			return;
	}
	(void)server;
	(void)user;
	(void)modeparam;
}

std::string getChanModes(Channel* chan) {
	std::string modes = "+";
	if (chan->getTopicrestricted() == true)
		modes += "t";
	if (chan->getInviteonly() == true)
		modes += "i";
	if (chan->getUserlimit() == true)
		modes += "l";
	if (chan->getKeyneeded() == true)
		modes += "k";
	return modes;
}

std::string getChanModeParams(Channel* chan) {
	std::string modeparams = "";
	if (chan->getUserlimit() == true || chan->getKeyneeded() == true)
		modeparams += " ";
	if (chan->getUserlimit() == true) {
		std::ostringstream oss;
		oss << chan->getMaxusers();
		modeparams += oss.str();
		if (chan->getKeyneeded() == true)
			modeparams += " ";
	}
	if (chan->getKeyneeded() == true)
		modeparams += chan->getKey();
	return modeparams;
}

int chan_cmd_mode(IRCServer& server, User& user, Message& message){
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return 1;
	}
	Channel* chan = server.getChannels().findChannel(message.getParams().front());
	if (chan == NULL) { //does the channel exist ?
		user.send(ERR_NOSUCHCHANNEL(server.getName(), message.getParams().front()));
		return 1;
	}
	if (message.getParams().size() == 1) {
		std::string modes = getChanModes(chan);
		modes += getChanModeParams(chan);
		user.send(RPL_CHANNELMODEIS(server.getName(), user.getNick(), chan->getName(), modes)); //mode & modeparams?
		return 0;
	}
	if (chan->getChops()->findUserByNick(user.getNick()) == NULL) { //are we channel op?
		user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
		return 1;
	}
	std::string mode = message.getParams()[1];
	std::string modeparam = "";
	std::string allmodes = "itkol";
	if (message.getParams().size() > 2)
		modeparam = message.getParams()[2];

	if (mode.length() != 2 || (mode[0] != '+' && mode[0] != '-')) { //check that we have correct format '+?'
		user.send(ERR_UNKNOWNMODE(server.getName(), mode, chan->getName()));
		return 1;
	}
	if (allmodes.find(mode[1]) == std::string::npos) { //check that we support the mode
		user.send(ERR_UNKNOWNMODE(server.getName(), mode[1], chan->getName()));
		return 1;
	}

	execChanMode(server, user, chan, mode, modeparam);

	//make reply and send to user
	return 0;
}
