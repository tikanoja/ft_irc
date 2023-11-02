/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:33:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 11:03:20 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

#define NICKAPPENDICES "_123456789"

static bool isNickvalid(std::string& nick);

int cmd_nick(IRCServer& server, User& user, Message& message){
	if (user.getPassFlag() == false) {
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return 1;
	}
	std::string new_nick = message.getParams().front();
	std::cout << "NICK EMPTY? " << std::boolalpha << new_nick.empty() << std::endl;
	if (new_nick.empty()){
		std::cout << "We're here, we're queer, get used to it" << std::endl;
		user.send(ERR_NONICKNAMEGIVEN(server.getName()));
		return 1;
	}
	std::cout << "NICK VALID? " << std::boolalpha << isNickvalid(new_nick) << std::endl;
	if (!isNickvalid(new_nick)){
		user.send(ERR_ERRONEUSNICKNAME(server.getName(),
			new_nick));
		return 1;
	}
	User * found_user = server.getUsers().findUserByNick(new_nick);
	if (found_user == NULL)
		std::cout << "not in use!" << std::endl;
	if (found_user != NULL){
		user.send(ERR_NICKNAMEINUSE(server.getName(), new_nick));
		return 1;
	}
	std::cout << "NICK CHANGE TO " << new_nick << std::endl;
	server.log("Changed nickname " + user.getNick() + "->" + new_nick, __FILE__, __LINE__);
	user.setNick(new_nick);
	user.setRegistrationFlag(1, user, server);
	std::cout << "NICK WAS CHANGED TO " << user.getNick() << std::endl;
	return 0;
}

static bool isNickvalid(std::string& nick){

	if (nick[0] == '$' || nick[0] == ':' || nick[0] == '#' || nick[0] == '+'){
		return false;
	}
	if (nick.find_first_of(",*?! @.", 0) != std::string::npos){
		return false;
	}
	return true;
}
