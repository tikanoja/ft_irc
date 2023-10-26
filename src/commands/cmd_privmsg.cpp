/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_privmsg.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/26 14:51:22 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

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
		if (target[0] == '#' || target[0] == '&' || target[0] == '!'){ //what else ?
			Channel* chan = server.getChannels().findChannel(target);
			if (chan == NULL) {
				user.send(ERR_NOSUCHCHANNEL(server.getName(), target));
				continue ;
			}
			if (chan->getMembers()->findUserByNick(user.getNick()) == NULL) {
				user.send(ERR_NOTONCHANNEL(server.getName(), chan->getName()));
				continue ;
			}
			if (message.getTrailing().empty()) {
				user.send(ERR_NOTEXTTOSEND(server.getName()));
				continue ;
			}
			std::string msg = ":" + user.getNick() + "!add_user_host_here" + " PRIVMSG " + target + " :" + message.getTrailing() + "\r\n";
			chan->broadcastToChannel(msg, &user);
		} else {
			User* recipient = server.getUsers().findUserByNick(target);
			if (recipient == NULL) {
				user.send(ERR_NOSUCHNICK(server.getName(),
					recipient->getNick(), "user"));
				return 1;
			}
			if ((recipient->getMode() >> IRCServer::away) & 1)
				user.send(RPL_AWAY(server.getName(),
					recipient->getNick(), recipient->getAwayMsg()));
			if (message.getTrailing().empty()) {
				user.send(ERR_NOTEXTTOSEND(server.getName()));
				return 1;
			}
			std::string msg = ":" + user.getNick() + "!add_user_host_here" + " PRIVMSG " + target + " :" + message.getTrailing() + "\r\n";
			recipient->send(msg);
		}
	}
	return 0;
}
