/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:17:03 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

int cmd_who(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
		message.getCommand()));
		return 1;
	}
	if (message.getParams().size() > 1)
		user.send(RPL_ENDOFWHO(server.getName(), user.getNick(), message.getParams()[1]));
	else
		user.send(RPL_ENDOFWHO2(server.getName(), user.getNick()));
	return 0;
}

int cmd_whois(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
		message.getCommand()));
		return 1;
	}
	user.send(RPL_ENDOFWHOIS(server.getName(), user.getNick()));
	return 0;
}
