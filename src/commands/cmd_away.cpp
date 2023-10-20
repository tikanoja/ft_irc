/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_away.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 09:57:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int cmd_away(IRCServer& server, User &user, Message &message){

	if (user.getMode() & 0x0080){
		user.getSendBuffer().addToBuffer(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()).c_str());
		return 1;
	}
	if (message.getParams()[0].empty()){
		user.getSendBuffer().addToBuffer(RPL_UNAWAY(server.getName()).c_str());
		user.unsetMode(0x0001);
	} else {
		user.getSendBuffer().addToBuffer(RPL_NOWAWAY(server.getName()).c_str());
		user.setMode(0x0001);
	}
	user.setAwayMsg(message.getParams()[0]);

	return 0;
}
