/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_join.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:42 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/13 09:46:33 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int chan_cmd_join(IRCServer& server, User& user, Message& message){
	if (message.getParams().front() == "") { //irssi expects this reply for some reason w registering...
		Message me(":127.0.0.1 451 * JOIN :You must finish connecting with another nickname first.");
		me.printContent();
		const char* toAdd = me.toString();
		user.getSendBuffer().addToBuffer(toAdd);
		delete[] toAdd;
		return 1;
	}
	//check p_channels for the chan requested
	if (*message.getParams().begin() == "") {
		std::cout << "Join target not specified!" << std::endl;
		return 0;
	}
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
