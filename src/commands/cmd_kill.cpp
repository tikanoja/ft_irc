/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_kill.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:17 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/04 12:47:52 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

//    Command: KILL
//    Parameters: <nickname> <comment>

int cmd_kill(IRCServer& server, User& user, Message& message){


	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (message.getParams()[0].empty() 
		|| (message.getParams().size() > 1 &&  message.getParams()[1].empty())){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (!(user.getMode() & IRCServer::Oper) && !(user.getMode() & IRCServer::oper)){
		user.send(ERR_NOPRIVILEGES(server.getName()));
		return 1;
	}
	if (message.getParams()[0] == user.getNick()){
		close(user.getSocket());
		return 0;
	}
	User *toBeKilled = server.getUsers().findUserByNick(message.getParams()[0]);
	if (!toBeKilled){
		user.send(ERR_NOSUCHNICK(server.getName(),
			user.getNick(), "user"));
		return 1;
	}
	close(toBeKilled->getSocket());
	return 0;
}
