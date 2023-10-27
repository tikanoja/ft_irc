/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:05:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/27 16:37:54 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_pass(IRCServer& server, User& user, Message& message){
	if (message.getParams()[0].empty()){
		user.send(ERR_NEEDMOREPARAMS(server.getName(),
			message.getCommand()));
		return 1;
	}
	if (server.getPassword() != message.getParams()[0]){
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return 1;
	}
	if (!user.getIP()){
		user.send(ERR_ALREADYREGISTRED(server.getName()));
		return 1;
	}
	//if not registered
	user.setRegistrationFlag(3, user, server);
		//welcome
	return 0;
}
