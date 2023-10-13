/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ping.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:43:27 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/13 10:03:36 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Commands.hpp"

int cmd_ping(IRCServer& server, User& user, Message& message){
	std::cout << "this guy just pinged: " << std::endl;
	std::cout << " nick:" << user.getNick() << " username: " << user.getUserName() << " realname: " <<user.getRealName() << std::endl;
	cmd_pong(server, user, message);
	return 0;
}
