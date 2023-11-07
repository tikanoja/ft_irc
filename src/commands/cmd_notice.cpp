/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_notice.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:24 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:16:35 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

static void sendToUser(IRCServer& server, User& user, Message& message,
	std::string const & target);

static void sendToMask(IRCServer& server, User& user, Message& message,
	std::string const & target);
	
static void sendToChannel(IRCServer& server, User& user, Message& message,
	std::string const & target);


int cmd_notice(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		return 1;
	}
	std::vector<std::string> recipients = split(message.getParams()[0], ',');
	size_t num_recipients = recipients.size();
	for (size_t i = 0; i < num_recipients; i++){
		std::string target = recipients[i];
		if (target == "") {
			continue ;
		}
		if (message.getTrailing().empty()) {
			continue ;
		}
		if ((target[0] == '#' || target[0] == '&')
			&& target.find('.') == std::string::npos)
			sendToChannel(server, user, message, target);
		else if ((user.getMode() & (IRCServer::oper | IRCServer::Oper))
			&& (target[0] == '#' || target[0] == '$')){
			sendToMask(server, user, message, target);
		} else
			sendToUser(server, user, message, target);
	}
	return 0;
}

static void sendToUser(IRCServer& server, User& user, Message& message, std::string const & target){
	User* recipient = server.getUsers().findUserByNick(target);
	if (recipient == NULL)
		return ;
	std::string msg = ":" + USER_ID(user.getNick(), user.getUserName(), server.getName()) +
		" NOTICE " + target + " :" + message.getTrailing() + "\r\n";
	recipient->send(msg);
}

static void sendToMask(IRCServer& server, User& user, Message& message, std::string const & target){

	if (target[0] == '$' && target.find('.') != std::string::npos)
		return ;
	if (!isValidWildchard(target))
		return ;
	std::string msg = ":" + USER_ID(user.getNick(), user.getUserName(), server.getName()) +
		" NOTICE " + target + " :" + message.getTrailing() + "\r\n";
	server.broadcastToUsers(msg, &user, target.substr(1));
}

static void sendToChannel(IRCServer& server, User& user, Message& message, std::string const & target){

	Channel* chan = server.getChannels().findChannel(target);
	if (chan == NULL)
		return ;
	if (chan->getMembers()->findUserByNick(user.getNick()) == NULL)
		return ;
	std::string msg = ":" + USER_ID(user.getNick(), user.getUserName(), server.getName()) +
		" NOTICE " + target + " :" + message.getTrailing() + "\r\n";
	chan->broadcastToChannel(msg, &user);
}
