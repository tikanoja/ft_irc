/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_mode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 13:10:24 by djagusch         ###   ########.fr       */
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


#define ALLCHANMODES "+-itkol"

static bool checkChanmodePerms(IRCServer const & server, User & user, Message const & message,
	Channel * chan, std::vector<std::string> const & params);
	
static void setModes(Channel * chan, std::vector<std::string> const & params, std::string& additions,
	std::string& removals, std::vector<size_t> & indeces);

int chan_cmd_mode(IRCServer& server, User& user, Message& message){
	
	std::vector<std::string> params = message.getParams();
	Channel* chan = server.getChannels().findChannel(params.front());

	if (!checkChanmodePerms(server, user, message, chan, params))
		return 1;

	size_t forbidden;
	for (size_t i = 1; i < params.size(); i++){
		if (params[i][0] == '+' || params[i][0] == '-')
		{
			forbidden = params[i].find_first_not_of(ALLCHANMODES);
			if (forbidden != std::string::npos)
				user.send(ERR_UMODEUNKNOWNFLAG(server.getName()));
		}
	}

	std::string				additions;
	std::string				removals;
	std::vector<size_t>		indeces;
	
	setModes(chan, params, additions, removals, indeces);

	std::cout << removals << std::endl;
	std::cout << additions << std::endl;
	std::cout << additions << std::endl;
	std::string reply = ":" + user.getNick() + " MODE " +  chan->getName() + " :";
	reply += !additions.empty() ? ("+" + additions) : "";
	reply += !removals.empty() ? ("-" + removals) : "";
	reply += getSetValues(params, indeces);
	user.send(reply + "\r\n");
	if (0 < indeces.size())
		chan->broadcastToChannel(reply, &user);

	return 0;
}

static bool checkChanmodePerms(IRCServer const & server, User & user, Message const & message,
	Channel * chan, std::vector<std::string> const & params){
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return false;
	}
	if (params.size() == 1) {
		user.send(RPL_CHANNELMODEIS(server.getName(), user.getNick(), chan->getName(),\
			chan->getChanModes(), chan->getChanStr()));
		return false;
	}
	if (chan == NULL) {
		user.send(ERR_NOSUCHCHANNEL(server.getName(), message.getParams().front()));
		return false;
	}
	if (!chan->isChop(user)) {
		user.send(ERR_CHANOPRIVSNEEDED(server.getName(), chan->getName()));
		return false;
	}
	return true;
}

static void setModes(Channel * chan, std::vector<std::string> const & params, std::string& additions,
	std::string& removals, std::vector<size_t> & indeces){
	
		for (size_t i = 1; i < params.size(); i++){
		size_t pos = 0;
		while (i < params.size() && pos < params[i].size())
		{
			if (params[i][pos] == '+')
				additions += chan->setBatchMode(params, i, pos, indeces);
			else if (params[i][pos] == '-')
				removals += chan->unsetBatchMode(params, i, pos, indeces);
			else
				pos++;
		}
	}
	removeCommonCharacters(additions, removals);
}
