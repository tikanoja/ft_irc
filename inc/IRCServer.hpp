/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/03 15:26:29 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <vector>
# include <iostream>
# include <sstream>
# include <cstdint>
# include <cstring>
# include <string>
# include <poll.h>
# include <netdb.h>
# include <sstream>
# include <unistd.h>
# include <fcntl.h>
# include <stdexcept>
# include <netinet/in.h>
# include <arpa/inet.h> //inet
# include <sys/types.h> //types needed for socket() ftions
# include <sys/socket.h> //socket(), connect(), struct sockaddr
# include "CircularBuffer.hpp"
# include "Uvector.hpp"
# include "User.hpp"
# define MAXCLIENTS 10
# define MAXDATASIZE 512

class User;
class Channel;
class CircularBuffer;

class IRCServer {
	private:
		enum e_uperm{
			away = 0x0001,			// user is flagged as away;
			wallops = 0x0002,		// user receives wallops;
			invisible = 0x0004,		// marks a users as invisible;
			restricted = 0x0008,		// restricted user connection;
			oper = 0x0010,			// operator flag;
			Oper = 0x0020,			// local operator flag;
			server_notice = 0x0040,	// marks a user for receipt of server notices.
			registered = 0x0080,		// user has completed registration
			online = 0x0100			// user is online
		};

		uint16_t					port;
		Uvector						users;
		std::vector<Channel*>		channels;

		std::vector<struct pollfd>	pfds;
		std::string					creationDate;
		std::string					runningDateTime;
		std::string					version;


		int			getListenerSocket();
		void		initServer();
		void*		get_in_addr(struct sockaddr *sa);
		int			acceptClient();
		int			receiveMsg(User* user, nfds_t i);
		void		dropConnection(ssize_t numbytes, nfds_t i);
		void		replyToMsg(User *user);
		
		bool		getUserMode(User & user, e_uperm mode);
		void		setUserMode(User & user, e_uperm mode);

	public:
		IRCServer(uint16_t port);
		~IRCServer(void);
		int pollingRoutine();
};

#endif
