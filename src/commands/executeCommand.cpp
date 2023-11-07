/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executeCommand.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:52:00 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:17:12 by ttikanoj         ###   ########.fr       */
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

	commandMap::iterator it = p_commandMap.find(strToLower(message.getCommand()));
	if (it != p_commandMap.end()) {
		commandFunction func = it->second;
		return func(*this, user, message);
	} else {
		user.send(ERR_UNKNOWNCOMMAND(getName(), message.getCommand()));
		return 1;
	}
}
