/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 10:32:59 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int cmd_pong(IRCServer& server, User& user, Message& message){
	Message me(":127.0.0.1 PONG 127.0.0.1 :" + user.getUserName()); //?????
	const char* toAdd = me.toString();
	user.getSendBuffer().addToBuffer(toAdd);
	delete[] toAdd;
	(void)server;
	(void)message;
	return 0;
}
