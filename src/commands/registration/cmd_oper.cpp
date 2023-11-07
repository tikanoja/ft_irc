/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_oper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:26:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:15:13 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

enum CheckType { CHECK_NICK, CHECK_IP, CHECK_PW };

static bool checkOpers(std::vector<Operator> const & opers,
	std::string const & input, CheckType checkType);
	
static bool hasOperAccount(IRCServer const & server, User & user,
	std::vector<std::string> const & params);


int cmd_oper(IRCServer& server, User& user, Message& message){

	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	std::vector<std::string> const & params = message.getParams();
	if (params.size() < 2 || params[0].empty() || params[1].empty()){
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		server.log("Rejected " + user.getNick() + " from becoming oper", __FILE__, __LINE__);
		return 1;
	}
	if (!hasOperAccount(server, user, params)){
		server.log("Rejected " + user.getNick() + " from becoming oper", __FILE__, __LINE__);
		return 1;
	}
	try {
		server.getOperByNick(params[0]).setUser(&user);
		user.setMode(IRCServer::Oper);
		user.send(RPL_YOUREOPER(server.getName(), user.getNick()));
		server.log("Set " + user.getNick() + " to oper", __FILE__, __LINE__);
		return 0;
	} catch (std::exception & e){
		user.send(ERR_NOOPERHOST(server.getName()));
		server.log("Rejected " + user.getNick() + " from becoming oper", __FILE__, __LINE__);
		return 1;
	}
	user.send(RPL_YOUREOPER(server.getName(), user.getNick()));
}

static bool checkOpers(std::vector<Operator> const & opers,
	std::string const & input, CheckType checkType){

	for (std::vector<Operator>::const_iterator it = opers.begin();
		it != opers.end(); ++it){
			
		std::string toCompare;
		switch (checkType){
			case CHECK_NICK:
				toCompare = it->getNick();
				break;
			case CHECK_IP:
				toCompare = it->getIP();
				break;
			case CHECK_PW:
				toCompare = it->getPW();
				break;
		}
		if (input == toCompare){
			return true;
		}
	}
	return false;
}

static bool hasOperAccount(IRCServer const & server, User & user,
	std::vector<std::string> const & params){

	std::vector<Operator> const & opers = server.getOpers();

	if (!checkOpers(opers, params[0], CHECK_NICK)){
		user.send(ERR_NOOPERHOST(server.getName()));
		return false;
	}
	if (!checkOpers(opers, user.getIP(), CHECK_IP)){
		user.send(ERR_NOOPERHOST(server.getName()));
		return false;
	}
	if (!checkOpers(opers, params[1], CHECK_PW)){
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return false;
	}
	return true;
}
