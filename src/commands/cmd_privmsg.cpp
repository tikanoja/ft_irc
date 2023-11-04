/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/04 13:16:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"


static void sendToUser(IRCServer& server, User& user, Message& message,
	std::string const & target);

static void sendToMask(IRCServer& server, User& user, Message& message,
	std::string const & target);

static void sendToChannel(IRCServer& server, User& user, Message& message,
	std::string const & target);

int cmd_privmsg(IRCServer& server, User& user, Message& message){
	
	if (!(user.getMode() & IRCServer::registered)){
		user.send(ERR_NOTREGISTERED(server.getName(),
		message.getCommand()));
		return 1;
	}

	std::vector<std::string> recipients = split(message.getParams()[0], ',');
	size_t num_recipients = recipients.size();

	for (size_t i = 0; i < num_recipients; i++){
		std::string target = recipients[i];
		if (target == "") {
			user.send(ERR_NORECIPIENT(server.getName(),
			message.getCommand()));
			continue ;
		}
		if (message.getTrailing().empty()) {
			user.send(ERR_NOTEXTTOSEND(server.getName()));
			continue ;
		}
		if ((target[0] == '#' || target[0] == '&') &&
			target.find('.') == std::string::npos)
			sendToChannel(server, user, message, target);
		else if ((user.getMode() & (IRCServer::oper | IRCServer::Oper))
			&& (target[0] == '#' || target[0] == '$'))
			sendToMask(server, user, message, target);
		else
			sendToUser(server, user, message, target);
	}
	return 0;
}

static void sendToUser(IRCServer& server, User& user, Message& message, std::string const & target){
	
	User* recipient = server.getUsers().findUserByNick(target);
	if (recipient == NULL) {
		user.send(ERR_NOSUCHNICK(server.getName(),
			message.getParams()[0], "user"));
		return ;
	}
	if (recipient->getMode() & IRCServer::away){
		user.send(RPL_AWAY(server.getName(), user.getNick(),
			recipient->getNick(), recipient->getAwayMsg()));
	}
	std::string msg =  ":" + USER_ID(user.getNick(), user.getUserName(), "127.0.0.1") +
		" PRIVMSG " + target + " :" + message.getTrailing() + "\r\n";
	recipient->send(msg);
}

static void sendToMask(IRCServer& server, User& user, Message& message, std::string const & target){

	if (target[0] == '$' && target.find('.') == std::string::npos){
		user.send(ERR_NOTOPLEVEL(server.getName(), target));
		return ;
	}
	if (!isValidWildchard(target)){
		user.send(ERR_WILDTOPLEVEL(server.getName(), target));
		return ;
	}
	std::string msg = ":" + USER_ID(user.getNick(), user.getUserName(), server.getName()) +
		" PRIVMSG " + target + " :" + message.getTrailing() + "\r\n";
	server.broadcastToUsers(msg, &user, target);
}

static void sendToChannel(IRCServer& server, User& user, Message& message, std::string const & target){

	Channel* chan = server.getChannels().findChannel(target);
	if (chan == NULL) {
		user.send(ERR_NOSUCHCHANNEL(server.getName(), user.getNick(), target));
		return ;
	}
	if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) {
		user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
		return ;
	}
	std::string msg = ":" + USER_ID(user.getNick(), user.getUserName(), server.getName()) +
		" PRIVMSG " + target + " :" + message.getTrailing() + "\r\n";
	chan->broadcastToChannel(msg, &user);
}
