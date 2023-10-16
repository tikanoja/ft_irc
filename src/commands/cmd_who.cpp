/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:36 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 13:06:01 by ttikanoj         ###   ########.fr       */
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


	// if no name, list all visible users. (common channel & no +i mode)
	
	//same result with name "0" and "*"

	// * must work.. "WHO *.fi" must return all users who match against "*.fi"
	
	// if parameter o is passed, only operators matching against the name mask are returned!
	// "WHO jto* o" must list all users who match against "jto*" and are an operator!

	
	
	return 0;
}