/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_away.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:41:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:16:17 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int cmd_away(IRCServer& server, User &user, Message &message){

	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (message.getTrailing().empty()){
		user.send(RPL_UNAWAY(server.getName()));
		user.unsetMode(IRCServer::away);
	} else {
		user.send(RPL_NOWAWAY(server.getName()));
		user.setMode(IRCServer::away);
	}
	user.setAwayMsg(message.getTrailing());
	server.log(user.getNick() + " was set as away", __FILE__, __LINE__);

	return 0;
}
