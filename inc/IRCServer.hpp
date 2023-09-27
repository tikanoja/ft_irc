/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/27 13:21:11 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

#include <vector>
#include <iostream>
#include <sstream>
#include <cstdint>
#include <cstring>
#include <string>
#include <poll.h>
#include <netdb.h>
#include <sstream>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <netinet/in.h>
#include <arpa/inet.h> //inet
#include <sys/types.h> //types needed for socket() ftions
#include <sys/socket.h> //socket(), connect(), struct sockaddr
#include "CircularBuffer.hpp"
#define MAXCLIENTS 10
#define MAXDATASIZE 512

class User;
class Channel;
class CircularBuffer;

class IRCServer {
	private:
		uint16_t					port;
		std::vector<User*> 			users;
		std::vector<Channel*> 		cchannels;
		
		std::vector<struct pollfd>	pfds;
		std::vector<CircularBuffer>	circularBuffers;
		std::string					creationDate;
		std::string					runningDateTime;
		std::string					version;

		void initServer();
		int getListenerSocket();
		// void addToPfds();
		// void delFromPfds();
		void* get_in_addr(struct sockaddr *sa);
		int acceptClient();
		int receiveMsg(nfds_t i);
		void dropConnection(ssize_t numbytes, nfds_t i);
		void replyToMsg(nfds_t i);

	public:
		IRCServer(uint16_t port);
		int pollingRoutine();
		~IRCServer(void);
};

#endif
