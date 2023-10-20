/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_oper.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:26:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 11:52:25 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"


static bool checkOpers(std::vector<Operator> const & opers, std::string const & input,
	Operator::OperFunct function){
	
	size_t i = 0;
	for ( ; opers.size(); i++){
		if (input == (opers[i].*function)())
			return true;
	}
	return false;
}

static bool hasOperAccount(IRCServer const & server, User & user, std::vector<std::string> const & params){

	std::vector<Operator> const &	opers = server.getOpers();

	if (!checkOpers(opers, params[0], Operator::getNick)){
		user.send(ERR_NOOPERHOST(server.getName()));
		return false;
	}
	if (!checkOpers(opers, user.getIP(), Operator::getIP)){
		user.send(ERR_NOOPERHOST(server.getName()));
		return false;
	}
	if (!checkOpers(opers, params[1], Operator::getPW)){
		user.send(ERR_PASSWDMISMATCH(server.getName()));
		return false;
	}
	return true;
}

int cmd_oper(IRCServer& server, User& user, Message& message){

	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(), message.getCommand()));
		return 1;
	}
	std::vector<std::string> const & params = message.getParams();
	if (params.size() < 2 || params[0].empty() || params[1].empty()){
		user.send(ERR_NEEDMOREPARAMS(server.getName(), message.getCommand()));
		return 1;
	}
	if (hasOperAccount(server, user, params))
		user.setMode(IRCServer::Oper);
	return 0;
}