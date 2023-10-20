/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_names.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 14:50:03 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	REPLIES
		RPL_NAMREPLY	353
		RPL_ENDOFNAMES	366
*/

int chan_cmd_names(IRCServer& server, User& user, Message& message){
	Channel* chan = server.getChannels().findChannel(message.getParams().front());
	
	return 0;
}
