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

	if (user.getMode() & IRCServer::registered){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (message.getParams()[0].empty()){
		user.send(RPL_UNAWAY(server.getName()));
		user.unsetMode(IRCServer::away);
	} else {
		user.send(RPL_NOWAWAY(server.getName()));
		user.setMode(IRCServer::away);
	}
	user.setAwayMsg(message.getParams()[0]);

	return 0;
}
