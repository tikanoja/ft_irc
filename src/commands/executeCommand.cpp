/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/12 14:25:34 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int IRCServer::executeCommand(User& user, Message& message) {

	std::map<std::string, CommandFunction>::iterator it = p_commandMap.find(message.getCommand());
	// std::cout << "cmd: " << message.getCommand() << " and map string: " << it->first << std::endl;
	if (it != p_commandMap.end()) {
		CommandFunction func = it->second;
		return func(*this, user, message);
	} else {
		std::cout << "Command not found...!" << std::endl;
		user.getSendBuffer().addToBuffer(ERR_UNKNOWNCOMMAND(getName(), message.getCommand()).c_str());
		return 1;
	}
}
