/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 12:47:38 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int IRCServer::executeCommand(User& user, Message& message) {

	std::map<std::string, CommandFunction>::iterator it = p_commandMap.find(message.getCommand());
	if (it != p_commandMap.end()) {
		CommandFunction func = it->second;
		return func(*this, user, message);
	} else {
		user.send(ERR_UNKNOWNCOMMAND(getName(), message.getCommand()));
		return 1;
	}
}
