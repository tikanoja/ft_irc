/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:52:25 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 08:12:12 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include <string>
#include <iterator>
#include <algorithm>
#include "IRCServer.hpp"
#include "Message.hpp"
#include "Uvector.hpp"
#include "Cvector.hpp"
#include "User.hpp"
#include "Reply.hpp"
#include "Error.hpp"
#include "Channel.hpp"

class IRCServer;
class User;
class Uvector;
class Channel;
class Message;
class Operator;

//Registration functions

int cmd_cap(IRCServer& server, User& user, Message& message);
int cmd_pass(IRCServer& server, User& user, Message& message);
int cmd_nick(IRCServer& server, User& user, Message& message);
int cmd_user(IRCServer& server, User& user, Message& message);
int cmd_mode(IRCServer& server, User& user, Message& message);
int cmd_quit(IRCServer& server, User &user, Message &message);
int cmd_away(IRCServer& server, User &user, Message &message);
int cmd_motd(IRCServer& server, User& user, Message& message);

int motd(IRCServer& server, User& user);

// Operator functions
int cmd_kill(IRCServer& server, User &user, Message &message);
int cmd_oper(IRCServer& server, User &user, Message &message);
int cmd_notice(IRCServer& server, User &user, Message &message);
int cmd_privmsg(IRCServer& server, User &user, Message &message);
int cmd_ping(IRCServer& server, User &user, Message &message);
int cmd_pong(IRCServer& server, User &user, Message &message);
int cmd_who(IRCServer& server, User& user, Message& message);
int cmd_whois(IRCServer& server, User& user, Message& message);

//Channel functions

int chan_cmd_join(IRCServer& server, User& user, Message& message);
int chan_cmd_part(IRCServer& server, User& user, Message& message);
int chan_cmd_topic(IRCServer& server, User& user, Message& message);
int chan_cmd_kick(IRCServer& server, User& user, Message& message);
int chan_cmd_invite(IRCServer& server, User& user, Message& message);
int chan_cmd_mode(IRCServer& server, User& user, Message& message);

// Utils
void removeCommonCharacters(std::string& str1, std::string& str2);
std::string getSetValues(std::vector<std::string> const & params,
	std::vector<size_t> const & indeces);

#endif
