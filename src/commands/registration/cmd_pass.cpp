/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:05:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:15:09 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_pass(IRCServer& server, User& user, Message& message){
	std::string IP = user.getIP();

	if (message.getParams()[0].empty()){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		server.log("Refused login from " + IP, __FILE__, __LINE__);
		return 1;
	}
	if (server.getPassword() != message.getParams()[0]){
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		server.log("Refused login from " + IP, __FILE__, __LINE__);
		return 1;
	}
	if (!user.getIP()){
		user.send(ERR_ALREADYREGISTRED(server.getName()));
		server.log("Refused login from " + IP, __FILE__, __LINE__);
		return 1;
	}

	user.setRegistrationFlag(3, server);
	return 0;
}
