/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pong.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 09:58:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

int cmd_pong(IRCServer& server, User& user, Message& message){
	Message me(":127.0.0.1 PONG 127.0.0.1 :" + user.getUserName()); //?????
	me.printContent();
	const char* toAdd = me.toString();
	user.send(toAdd);
	delete[] toAdd;
	(void)server;
	(void)message;
	return 0;
}
