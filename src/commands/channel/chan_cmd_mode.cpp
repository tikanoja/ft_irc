/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_mode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/31 08:00:57 by djagusch         ###   ########.fr       */
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


#define ALLCHANMODES "+- itkIol"

int chan_cmd_mode(IRCServer& server, User& user, Message& message){
	std::cout << "Handling chan modes..." << std::endl;
	message.printContent();
	
	if (!(user.getMode() & IRCServer::registered)){ //are we registered?
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return 1;
	}
	std::vector<std::string> params = message.getParams();
	Channel* chan = server.getChannels().findChannel(params.front());
	if (params.size() == 1) {
		std::cout << "REQUESTED CHANMOD LIST" << std::endl;
		user.send(RPL_CHANNELMODEIS(server.getName(), chan->getName(), chan->getChanModes(), chan->getChanStr()));
		return 0;
	}
	if (chan == NULL) { //does the channel exist ?
		user.send(ERR_NOSUCHCHANNEL(server.getName(), params.front()));
		return 1;
	}
	if (!chan->isChop(user)) { //are we channel op?
		user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
		return 1;
	}
	size_t forbidden;
	for (size_t i = 1; i < params.size(); i++){
		forbidden = params[i].find_first_not_of(ALLCHANMODES);
		if (forbidden != std::string::npos)
			user.send(ERR_UMODEUNKNOWNFLAG(server.getName()));
	}

	std::string additions;
	std::string removals;
	
	for (size_t i = 1; i < params.size(); i++){
		size_t pos = 0;
		while (pos < params[i].size())
		{
			if (params[i][pos] == '+')
				additions += chan->setBatchMode(params[i], &pos);
			else if (params[i][pos] == '-')
				removals += chan->unsetBatchMode(params[i], &pos);
			else
				pos++;
		}
	}

	removeCommonCharacters(additions, removals);

	std::string reply = ":" + user.getNick() + " MODE " +  chan->getName() + " :";
	reply += !additions.empty() ? ("+" + additions) : "";
	reply += !removals.empty() ?  ("-" + removals) : "";
	user.send(reply + "\r\n");

	//make reply and send to user
	return 0;
}
