/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/16 10:08:21 by djagusch         ###   ########.fr       */
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
# include <sys/types.h> //types needed for socket() functions
# include <sys/socket.h> //socket(), connect(), struct sockaddr
# include "CircularBuffer.hpp"
# include "Uvector.hpp"
# include "Cvector.hpp"
# include "Message.hpp"
# include "User.hpp"
# include "Commands.hpp"

# define MAXCLIENTS 10

# ifndef MAXDATASIZE
#  define MAXDATASIZE 512
# endif

# ifndef N_COMMANDS
#  define N_COMMANDS 10
# endif

class User;
class Channel;
class CircularBuffer;
class Message;

class IRCServer {
	private:

		uint16_t					p_port;
		std::string	const 			p_password;
		Uvector						p_users;
		Uvector						p_opers;
		Cvector						p_channels;
		nfds_t 						p_fd_count;

		std::vector<struct pollfd>	p_pfds;
		std::string					p_serverName;
		std::string					p_creationDate;
		clock_t						p_runningDateTime;
		std::string					p_version;
		std::vector<std::string>	p_blockeUserNames;

		typedef int (*CommandFunction)(IRCServer&, User&, Message&);
		std::map<std::string, CommandFunction>	p_commandMap;

		int									getListenerSocket();
		void								initServer();
		void 								initCommands();
		void*								get_in_addr(struct sockaddr *sa);
		int									acceptClient();
		int									receiveMsg(User* user, nfds_t i);
		int									checkRecvBuffer(User* user, nfds_t i);
		int									checkSendBuffer(User* user);
		void								dropConnection(ssize_t numbytes, nfds_t i);

		std::vector<std::string> const &	getBlocked() const;
		void								setBlocked(std::string nick);

	public:
		enum e_uperm{
			away = 0x0001,			// user is flagged as away;
			wallops = 0x0002,		// user receives wallops;
			invisible = 0x0004,		// marks a users as invisible;
			restricted = 0x0008,	// restricted user connection;
			oper = 0x0010,			// operator flag;
			Oper = 0x0020,			// local operator flag;
			server_notice = 0x0040,	// marks a user for receipt of server notices.
			registered = 0x0080	// user has completed registration
		};

		IRCServer(uint16_t port);
		~IRCServer(void);

		int					pollingRoutine();
		int					executeCommand(User& user, Message& message);
		std::string	const & getName();
		std::string	const &	getPassword() const;
		Uvector		const &	getUsers() const;
		Cvector			  & getChannels();
		bool				isBlocked(std::string nick) const;
		void				delFd(User& user);
		void				delUser(User& user);

		bool				getUserMode(User & user, e_uperm mode) const;
		void				setUserMode(User & user, e_uperm mode);
		void				unsetUserMode(User & user, e_uperm mode);
		std::string			setBatchMode(User & user, std::string const & modes, size_t *index);
		std::string			unsetBatchMode(User & user, std::string const & modes, size_t *index);
		std::string			getModeStr(User const &user);
};

#endif
