/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 20:44:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/03 06:37:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

//USER guest 0 * :Ronnie Reagan

int cmd_user(IRCServer& server, User& user, Message& message){
	if (user.getPassFlag() == false){// || user.getNick().empty() ) { !!!!! this helped
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return 1;
	}
	// if (user.getNick().empty()){
	// 	user.send(ERR_NONICKNAMEGIVEN(server.getName()));
	// 	return 1;
	// }
	if (message.getParams()[2].empty() || message.getTrailing().empty()){
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
