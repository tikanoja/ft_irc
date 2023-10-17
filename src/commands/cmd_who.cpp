/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/17 12:14:12 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"

	// Numeric replies: ERR_NOSUCHSERVER RPL_WHOREPLY RPL_ENDOFWHO
	// Command: WHO
	// Parameres: <name> <o>

	// RPL_WHOREPLY:
	// "<channel> <user> <host> <server> <nick> <H|G>[*][@|+] :<hopcount> <real name>"
	// H = Here, G = Away (gone...), * = op, @ = chan op, + = voice mode enabled in chan (ex. H@ means here and chop)
	
int cmd_who(IRCServer& server, User &user, Message &message){
	// if no name, list all visible users. (not common channel & no +i mode)
	if (message.getParams().front() == "" || message.getParams().front() == "0" || message.getParams().front() == "*") {
		for (std::vector<User*>::const_iterator it = server.getUsers().begin(); it != server.getUsers().end(); it++) {
			// if there is +i in mode, continue.
			// if the user is in the same channel as we are, continue
			// if the user is ME, continue
			// else, RPL_WHOREPLY
		}
	}
	else if (message.getParams().front()[0] == '#' || \
	message.getParams().front()[0] == '&' || \
	message.getParams().front()[0] == '!' || \
	message.getParams().front()[0] == '+') {
		//if there is * in there: ":nonstop.ix.me.dal.net 403 tuukka #tes* :No such channel"
		//if channel not found: ":nonstop.ix.me.dal.net 403 tuukka #jonnebis :No such channel"
		//if channel found
		//list ALL users in the channel who dont have +i, including me
	}

	//check host
	//check server
	//check nickname
	//check real name
	//no need to check USERNAME!!!

	// * must work.. "WHO *.fi" must return all users who match against "*.fi"
	
	// if parameter o is passed, only operators matching against the name mask are returned!
	// "WHO jto* o" must list all users who match against "jto*" and are an operator!

	
	
	return 0;
}