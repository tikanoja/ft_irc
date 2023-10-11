/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:05:15 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/10/10 14:25:20 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_quit(IRCServer& server, User& user, Message& message){
	//close fd
	close(user.getSocket());
	
	//del user from p_pfds
	server.delFd(user);
	
	//del user from p_users
	server.delUser(user);

	//del user
	delete &user;

	//add confirmation to other users on channel! TODO!!
	std::cout << "User has quit and vecs handled!" << std::endl;
	(void)message;
	return 0;
}
