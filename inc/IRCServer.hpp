/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/09 07:28:07 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

# include <vector>
# include <map>
# include <utility>
# include <iostream>
# include <csignal>
# include <sstream>
# include <fstream>
# include <cstring>
# include <ctime>
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
# include "Cvector.hpp"
# include "Channel.hpp"
# include "Uvector.hpp"
# include "Uvector.hpp"
# include "Message.hpp"
# include "User.hpp"
# include "Operator.hpp"
# include "Logger.hpp"
# include "Commands.hpp"
# include "Utils.hpp"

# define MAXCLIENTS 32

# ifndef MAXDATASIZE
#  define MAXDATASIZE 512
# endif

# ifndef UNAMELEN
#  define UNAMELEN 10
# endif

#define COLOR_END "\033[0m"
#define COLOR_BLACK "\033[0;30m"
#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_MAGENTA "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"
#define COLOR_WHITE "\033[0;37m"
#define BRIGHT_COLOR_BLACK "\033[1;30m"
#define BRIGHT_COLOR_RED "\033[1;31m"
#define BRIGHT_COLOR_GREEN "\033[1;32m"
#define BRIGHT_COLOR_YELLOW "\033[1;33m"
#define BRIGHT_COLOR_BLUE "\033[1;34m"
#define BRIGHT_COLOR_MAGENTA "\033[1;35m"
#define BRIGHT_COLOR_CYAN "\033[1;36m"
#define BRIGHT_COLOR_WHITE "\033[1;37m"

class User;
class Channel;
class Cvector;
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
		std::string					p_version;
		std::string					p_modes;
		std::string					p_chanModes;

		Logger *					p_logger;

		typedef int (*commandFunction)(IRCServer&, User&, Message&);
		typedef std::map<std::string, commandFunction> commandMap;

		commandMap	p_commandMap;

		void								initServer();
		void								setGlobals();
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
			away = 0x001,				// user is flagged as away;
			wallops = 0x002,				// user receives wallops;
			invisible = 0x004,			// marks a users as invisible;
			restricted = 0x008,			// restricted user connection;
			oper = 0x010,				// operator flag;
			Oper = 0x020,				// local operator flag;
			server_notice = 0x040,		// marks a user for receipt of server notices.
			registered = 0x080,			// user has completed registration
			cap_negotiation = 0x100		// capability negotiation ongoing?
		};

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
		std::string const & 			getDate(void) const;
		std::string const & 			getVersion(void) const;
		std::string const & 			getUmodes(void) const;
		std::string const & 			getCmodes(void) const;

		void							delFd(User& user);
		void							delUser(User& user);

		void							log(std::string, std::string file, int line);

		int								executeCommand(User& user, Message& message);
		void							setUserMode(User & user, e_uperm mode);
		void							unsetUserMode(User & user, e_uperm mode);
		std::string						setBatchMode(User & user, std::string const & modes, size_t *index);
		std::string						unsetBatchMode(User & user, std::string const & modes, size_t *index);

		void 							broadcastToUsers(std::string const & message, User* sender, std::string const & mask);
};

#endif
