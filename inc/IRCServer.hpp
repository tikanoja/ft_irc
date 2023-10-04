/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/04 16:43:47 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <vector>
# include <map>
# include <iostream>
# include <sstream>
# include <cstdint>
# include <cstring>
# include <time.h>
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
# include "Message.hpp"
# include "User.hpp"
# include "Commands.hpp"

# define MAXCLIENTS 10

# ifndef MAXDATASIZE
#  define MAXDATASIZE 512
# endif

# ifndef N_COMMANDS
#  define N_COMMANDS 1
# endif

class User;
class Channel;
class CircularBuffer;

class IRCServer {
	private:
		enum e_uperm{
			away = 0x0001,			// user is flagged as away;
			wallops = 0x0002,		// user receives wallops;
			invisible = 0x0004,		// marks a users as invisible;
			restricted = 0x0008,	// restricted user connection;
			oper = 0x0010,			// operator flag;
			Oper = 0x0020,			// local operator flag;
			server_notice = 0x0040,	// marks a user for receipt of server notices.
			registered = 0x0080,	// user has completed registration
			online = 0x0100			// user is online
		};

		uint16_t					port;
		std::string	const 			password;
		Uvector						users;
		std::vector<Channel*>		channels;

		std::vector<struct pollfd>	pfds;
		std::string					serverName;
		std::string					creationDate;
		clock_t						runningDateTime;
		std::string					version;

		typedef int (*CommandFunction)(IRCServer&, User&, Message&);
		std::map<std::string, CommandFunction>	command_map;

		int				getListenerSocket();
		void			initServer();
		void 			initCommands();
		void*			get_in_addr(struct sockaddr *sa);
		int				acceptClient();
		int				receiveMsg(User* user, nfds_t i);
		void			dropConnection(ssize_t numbytes, nfds_t i);
		void			replyToMsg(nfds_t i);
		
		bool			getUserMode(User & user, e_uperm mode) const;
		void			setUserMode(User & user, e_uperm mode);


	public:
		IRCServer(uint16_t port);
		~IRCServer(void);
		
		int pollingRoutine();
		std::string	const & getName();
		std::string const &	getPassword() const;
		Uvector		const &	getUsers() const;
};

#endif
