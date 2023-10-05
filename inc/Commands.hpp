/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:52:25 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/05 12:08:24 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

#include "IRCServer.hpp"
#include "Message.hpp"
#include "Uvector.hpp"
#include "User.hpp"
#include "Reply.hpp"
#include "Error.hpp"

class IRCServer;
class User;
class Uvector;
class Message;

//Registration functions

int cmd_pass(IRCServer& server, User& user, Message& message);
int cmd_nick(IRCServer& server, User& user, Message& message);
int cmd_user(IRCServer& server, User& user, Message& message);
int cmd_mode(IRCServer& server, User& user, Message& message);
// int cmd_user(IRCServer& server, User &user, Message &message);
// int cmd_oper(IRCServer& server, User &user, Message &message);
// int cmd_quit(IRCServer& server, User &user, Message &message);
// int cmd_squit(IRCServer& server, User &user, Message &message);
// int cmd_mode(IRCServer& server, User &user, Message &message);

// //Operator functions

// int cmd_away(IRCServer& server, User &user, Message &message);
// int cmd_kill(IRCServer& server, User &user, Message &message);
// int cmd_luser(IRCServer& server, User &user, Message &message);
// int cmd_notice(IRCServer& server, User &user, Message &message);
// int cmd_ping(IRCServer& server, User &user, Message &message);
// int cmd_pong(IRCServer& server, User &user, Message &message);
// int cmd_privmsg(IRCServer& server, User &user, Message &message);
// int cmd_who(IRCServer& server, User &user, Message &message);
// int cmd_whois(IRCServer& server, User &user, Message &message);

#endif
