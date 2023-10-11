/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_join.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/11 11:24:02 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int chan_cmd_join(IRCServer& server, User& user, Message& message){
	//check p_channels for the chan requested
	Channel* toJoin = server.getChannels().findChannel(*message.getParams().begin());
	//if yes join
	if (toJoin != NULL) {
		toJoin->getMembers()->push_back(&user);
		//notify other channel members that user joined!
	} else {
		//create channel
		toJoin = server.getChannels().createChannel(*message.getParams().begin());
		toJoin->getMembers()->push_back(&user);
		//notify other channel members that user joined!
	}
	return 0;
}
