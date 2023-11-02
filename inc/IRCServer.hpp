/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/02 07:15:43 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <vector>
# include <map>
# include <utility>
# include <iostream>
# include <sstream>
# include <fstream>
# include <cstdint>
# include <cstring>
# include <time.h>
# include <string>
# include <poll.h>
# include <netdb.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdexcept>
# include <exception>
# include <netinet/in.h>
# include <arpa/inet.h> //inet
# include <sys/types.h> //types needed for socket() functions
# include <sys/socket.h> //socket(), connect(), struct sockaddr
# include "DynamicBuffer.hpp"
# include "Uvector.hpp"
# include "Cvector.hpp"
# include "Message.hpp"
# include "User.hpp"
# include "Operator.hpp"
# include "Logger.hpp"
# include "Commands.hpp"
# include "Utils.hpp"

# define MAXCLIENTS 10

# ifndef MAXDATASIZE
#  define MAXDATASIZE 512
# endif

# ifndef UNAMELEN
#  define UNAMELEN 10
# endif

class User;
class Channel;
class DynamicBuffer;
class Message;

class IRCServer {
	private:
		uint16_t					p_port;
		std::string	const 			p_password;
		Uvector						p_users;
		std::vector<Operator>		p_opers;
		Cvector						p_channels;
		nfds_t 						p_fd_count;

		std::vector<struct pollfd>	p_pfds;
		std::string					p_serverName;
		std::string					p_creationDate;
		clock_t						p_runningDateTime;
		std::string					p_version;

		Logger *					p_logger;

		typedef int (*CommandFunction)(IRCServer&, User&, Message&);
		std::map<std::string, CommandFunction>	p_commandMap;

		void								initServer();
		void 								initCommands();
		void								initOperators();
		
		int									getListenerSocket();
		void*								get_in_addr(struct sockaddr *sa);
		int									acceptClient();
		void								dropConnection(ssize_t numbytes, nfds_t i);
		
		int									receiveMsg(User* user, nfds_t i);
		int									checkRecvBuffer(User* user, nfds_t i);
		int									checkSendBuffer(User* user);

	public:
		enum e_uperm{
			away = 0x01,			// user is flagged as away;
			wallops = 0x02,		// user receives wallops;
			invisible = 0x04,		// marks a users as invisible;
			restricted = 0x08,	// restricted user connection;
			oper = 0x10,			// operator flag;
			Oper = 0x20,			// local operator flag;
			server_notice = 0x40,	// marks a user for receipt of server notices.
			registered = 0x80		// user has completed registration
		};

		// class UserNotFound : public std::exception{
		// 	public:
		// 		virtual char const * what() const throw();
		// };

		IRCServer(uint16_t port, std::string password);
		~IRCServer(void);

		int								pollingRoutine();
		
		std::string	const & 			getName() const;
		std::string	const &				getPassword() const;
		Uvector		const &				getUsers() const;
		Cvector			  &				getChannels();
		std::string						getModeStr(User const &user);
		std::vector<Operator> const &	getOpers() const;
		Operator &						getOperByNick(std::string nick);
		bool							getUserMode(User & user, e_uperm mode) const;

		void							delFd(User& user);
		void							delUser(User& user);

		void							log(std::string);

		int								executeCommand(User& user, Message& message);
		void							setUserMode(User & user, e_uperm mode);
		void							unsetUserMode(User & user, e_uperm mode);
		std::string						setBatchMode(User & user, std::string const & modes, size_t *index);
		std::string						unsetBatchMode(User & user, std::string const & modes, size_t *index);

		void 							broadcastToUsers(std::string const & message, User* sender, std::string const & mask);
};

#endif
