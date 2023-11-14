/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/14 11:14:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"


static std::string strToLower(std::string str){
	
	for (size_t i = 0; i < str.size(); i++)
	{
		str[i] = char(std::tolower(str[i]));
	}
	return str;
}

int IRCServer::executeCommand(User& user, Message& message) {

	// std::cout << BRIGHT_COLOR_MAGENTA << "Processing command " << message.getCommand() << COLOR_END << std::endl;
	// std::cout << BRIGHT_COLOR_BLACK << " //requested by ";
	// if (!(user.getMode() & IRCServer::registered))
	// 	std::cout << "an unregistered user" << COLOR_END << std::endl;
	// else
	// 	std::cout << user.getNick() << COLOR_END << std::endl;
	commandMap::iterator it = p_commandMap.find(strToLower(message.getCommand()));
	if (it != p_commandMap.end()) {
		commandFunction func = it->second;
		return func(*this, user, message);
	} else {
		user.send(ERR_UNKNOWNCOMMAND(getName(), message.getCommand()));
		return 1;
	}
}
