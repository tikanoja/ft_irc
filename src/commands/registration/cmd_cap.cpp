/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cap.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:40:28 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:15:26 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

int cmd_cap(IRCServer& server, User& user, Message& message){

	std::string type = message.getParams()[0];
	if (type == "LS" || type == "LIST" || type == "REQ"
		|| type == "ACK" || type == "NAK" || type == "REQ"){
		user.setMode(IRCServer::cap_negotiation);
		user.send(RPL_CAP(server.getName(), type, ""));
		return 0;
	}
	if (type == "END"){
		user.unsetMode(IRCServer::cap_negotiation);
		return 0;
	}
	user.send(ERR_INVALIDCAPCMD(server.getName(), user.getNick(), type));
	return 1;
}
