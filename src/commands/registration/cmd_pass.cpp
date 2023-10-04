/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pass.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:05:53 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 16:32:51 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_pass(IRCServer& server, User &user, Message &message){
	
	if (message.getParams()[0].empty()){
		user.getSendBuffer().addToBuffer(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()).c_str());
		return 1;
	}
	if (server.getPassword() != message.getParams()[0]){
		user.getSendBuffer().addToBuffer(ERR_PASSWDMISMATCH(server.getName()).c_str());
		return 1;
	}
	if (!user.getIP()){
		user.getSendBuffer().addToBuffer(ERR_ALREADYREGISTRED(server.getName()).c_str());
		return 1;
	}
}