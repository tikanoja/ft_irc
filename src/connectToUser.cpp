/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectToUser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 11:42:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

int IRCServer::getListenerSocket() {
	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;
	int yes = 1;
	
	std::stringstream ss;
	ss << this->port;
	std::string str = ss.str();
	const char* server_port = str.c_str();

	//init & configure socket
	memset(&hints, 0, sizeof(hints)); //can we use memset ???
	hints.ai_family = AF_UNSPEC; //set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, server_port, &hints, &servinfo))) { //resolve addr & port
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		return (-1);
	}

	//loop to create a socket & connect to available addr
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) //create a socket
			continue ;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
			std::cerr << "Failed to create a socket" << std::endl;
			return (-1);
		}
		fcntl(sockfd, F_SETFL, O_NONBLOCK); //set fd to non-blocking
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) { //bind port to socket
			close(sockfd);
			continue;
		}
		break ;
	}
	freeaddrinfo(servinfo);

	if (p == NULL) {
		std::cerr << "Failed to connect socket" << std::endl;
		return (-1);
	}
	if (listen(sockfd, MAXCLIENTS) == -1) {
		std::cerr << "Failed to listen" << std::endl;
		return (-1);
	}
	
	//create pollfd & save to pfds[0]
	struct pollfd pfd;
	pfd.fd = sockfd;
	pfd.events = POLLIN;
	this->pfds.push_back(pfd);

	return (0);
}

void* IRCServer::get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int IRCServer::acceptClient() {
	char s[INET6_ADDRSTRLEN];
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;
	int new_fd;
	
	sin_size = sizeof(their_addr);
	new_fd = accept(this->pfds[0].fd, (struct sockaddr *)&their_addr, &sin_size);
	if (new_fd == -1) {
		std::cerr << "Failed to accept client" << std::endl;
		return (-1);
	} else {
		struct pollfd pfd;
		pfd.fd = new_fd;
		pfd.events = POLLIN;
		this->pfds.push_back(pfd);

		users.push_back(new User());
		
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		users.back()->setIP(s);
		users.back()->setSocket(new_fd);
		std::cout << "Server: new connection from: " << s << std::endl;
	}
	return (0);
}

void IRCServer::dropConnection(ssize_t numbytes, nfds_t i) {
	if (numbytes == 0)
		std::cout << "Connection #" << i << " closed." << std::endl;
	else {
		std::cerr << "Recv failed. Numbytes: " << numbytes << std::endl;
	}	
	close(this->pfds[i].fd);
	users.findUserBySocket(this->pfds[i].fd)->resetBuffers();
	pfds.erase(this->pfds.begin() + i);
	return ;
}

void IRCServer::replyToMsg(nfds_t i) {
	std::ostringstream messageStream;
    messageStream << "Hello client number " << i << " !\r\n";
    std::string msg = messageStream.str();
	for (size_t in = 0; in < msg.length(); in++) {
		if (msg[in] == 26) {//ctrl+z control character
			msg.erase(in, 1);
			i--;
		}
		else if (msg[in + 1] && msg[in] == '^' && msg[in + 1] == 'Z') {
			msg.erase(in, 2);
			in--;
		}
	}
	const char* msgc = msg.c_str();

	size_t	msg_len = strlen(msgc);
	ssize_t total = 0;
	ssize_t n_sent = 0;
	while (total < static_cast<ssize_t>(msg_len) ){
		if ( (n_sent = send( pfds[i].fd,  &(msgc[total]), MAXDATASIZE, 0 ) ) <= 0)
			std::cerr << "Send failed" << std::endl;
		std::cout << "sent " << n_sent << " bytes." << std::endl;
		total += n_sent;
	}
	std::cout << "Sent: " << n_sent << "/" << msg_len << "bytes." << std::endl;
}