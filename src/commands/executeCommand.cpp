/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/03 06:30:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int IRCServer::executeCommand(User& user, Message& message) {

	commandMap::iterator it = p_commandMap.find(message.getCommand());
	if (it != p_commandMap.end()) {
		commandFunction func = it->second;
		return func(*this, user, message);
	} else {
		user.send(ERR_UNKNOWNCOMMAND(getName(), message.getCommand()));
		return 1;
	}
}
