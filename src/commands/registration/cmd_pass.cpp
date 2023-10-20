/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:05:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 09:57:12 by djagusch         ###   ########.fr       */
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
	return 0;
}
