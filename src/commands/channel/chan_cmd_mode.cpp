/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_mode.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:51 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/27 17:29:33 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

#include "../../inc/Commands.hpp"

/*
	MODES
		i	set/remove invite only channel
		t	set/remove topic setting for chop/reg
		k	set/remove channel key
		o	set/remove chop priviledge
		l	set/remove user limit on channel
*/

//MODE #channel +modeshere

# define ALL_CHAN_MODES "itkol"

static bool hasPermissions(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return false;
	}
	if (message.getParams()[0].size() < 1){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return false;
	}
	if (user.getNick() != message.getParams()[0]){
		user.send(ERR_USERSDONTMATCH(server.getName(), user.getNick()));
		return false;
	}
	return true;
}

int chan_cmd_mode(IRCServer& server, User& user, Message& message){
	//check that the user is listed on p_chops
	//get a string of the modes they askes for
	//check that they are legit, send ERR_UMODEUNKNOWNFLAG for those that are not
	//make additions and removals strings
	//remove common chars
	//make reply and send to user

	
	return 0;
}
