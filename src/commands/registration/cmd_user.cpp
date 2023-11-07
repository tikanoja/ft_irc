/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:44:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:14:56 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

//USER guest 0 * :Ronnie Reagan

int cmd_user(IRCServer& server, User& user, Message& message){
	if (user.getPassFlag() == false){
		user.send(ERR_RESTRICTED(server.getName()));
		return 1;
	}
	if (message.getParams().size() < 3 || 
		(message.getParams().size() >= 3 && (message.getParams()[0].empty()
			|| message.getParams()[1].empty() || message.getTrailing().empty()))){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return 1;
	}
	if ((user.getMode() & IRCServer::registered)){
		user.send(ERR_ALREADYREGISTRED(server.getName()));
		return 1;
	}
	user.setUserName(message.getParams()[0]);
	user.setRealName(message.getParams()[1]);
	if (message.getParams()[2] == "2")
		user.setMode(IRCServer::wallops);
	if (message.getParams()[2] == "8")
		user.setMode(IRCServer::invisible);

	user.setRegistrationFlag(2, server);
	server.log(user.getNick() + " was registered", __FILE__, __LINE__);
	return 0;
}
