/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chan_cmd_names.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:40:59 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/23 09:34:44 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/Commands.hpp"

/*
	REPLIES
		RPL_NAMREPLY	353
		RPL_ENDOFNAMES	366

	EXAMPLES
		NAMES #twilight_zone,#42	; list visible users on #twilight_zone
                                   	and #42 if the channels are visible to you.
		NAMES						; list all visible channels and users
*/

int chan_cmd_names(IRCServer& server, User& user, Message& message){
	if (message.getParams().front() == "") {
		std::cout << "Name query for all visible chans and users" << std::endl;
		// list all visible channels and users
	} else {
		Channel* chan = server.getChannels().findChannel(message.getParams().front());
		if (chan == NULL) {
			std::cout << "Name query for a nonexistent chan..." << std::endl;
			return 1;
			//the channel they requested the name list for does not exist
		} else {
			std::cout << "Name query for channel: " << message.getParams().front() << std::endl;
			//the channel DOES exist, list names in that channel
		}
	}
	return 0;
}

//actually not required by the subject, do this later!
