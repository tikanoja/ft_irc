/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:33:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/27 13:07:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

#define NICKAPPENDICES "_123456789"

// std::string changeNick(IRCServer const &server, std::string const & nick){

// 	for (size_t i = 0; i < MAXCLIENTS; i++)
// 	{
// 		std::string new_nick = nick.substr(0, UNAMELEN - 1).append(1, NICKAPPENDICES[i]);
// 		if (!server.getUsers().findUserByNick(new_nick))
// 			return new_nick;
// 	}
// 	return "";
// }

bool	isNickvalid(std::string & nick){

	if (nick[0] == '$' || nick[0] == ':' || nick[0] == '#' || nick[0] == '+'){
		std::cout << "Here1" << std::endl;
		return false;
	}
	if (nick.find_first_of(",*?! @.", 0) != std::string::npos){
		return false;
	}
	return true;
}

int cmd_nick(IRCServer& server, User& user, Message& message){

	std::string new_nick = message.getParams()[0];
	std::cout << "Given NICK " << new_nick << " is empty " << std::boolalpha << new_nick.empty() << std::endl;
	if (new_nick.empty()){
		std::cout << "No NICK given" << std::endl;
		user.send(ERR_NONICKNAMEGIVEN(server.getName()));
		return 1;
	}
	if (!isNickvalid(new_nick)){
		std::cout << "Erroneus NICK" << std::endl;
		user.send(ERR_ERRONEUSNICKNAME(server.getName(),
			new_nick));
		return 1;
	}
	User * found_user = server.getUsers().findUserByNick(new_nick);
	// std::string temp_nick = changeNick(server, new_nick);
	if (found_user != NULL){
		// if (user.getMode() & IRCServer::registered){
			// std::cout << "NICK in use" << std::endl;
			user.send(ERR_NICKNAMEINUSE(server.getName(), new_nick));
			// if (temp_nick.empty())
				return 1;
			// user.setOldNick(temp_nick.substr(0, UNAMELEN));
			// new_nick = temp_nick;
		// } else {
		// 	// std::cout << "NICK collide" << std::endl;
		// 	// new_nick = changeNick(server, new_nick);
		// 	// if (new_nick.empty()){
		// 		user.send(ERR_NICKCOLLISION(server.getName(),
		// 			new_nick, found_user->getNick(), found_user->getIP()));
		// 		close(user.getSocket());
		// 		return 1;
		// 	// }
			// user.send(ERR_NICKNAMEINUSE(server.getName(),new_nick));
		// }
	}
	if (server.isBlocked(new_nick)){
		user.send(ERR_UNAVAILRESOURCE(server.getName(),
			new_nick, "nick"));
		return 1;
	}
	user.setNick(new_nick);
	//if not registered
	user.setRegistrationFlag(1, user, server);
		//welcome
	return 0;
}
