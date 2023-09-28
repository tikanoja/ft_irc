/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:21:45 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/27 19:54:07 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"
#include "../inc/Message.hpp"

IRCServer::IRCServer(uint16_t port) : port(port){
	// std::cout << "IRCServer constructor called" << std::endl;
	pfds.reserve(10);
	circularBuffers.reserve(10);
	initServer();
	return ;
}

IRCServer::~IRCServer(void) {
	std::cout << "IRCServer destructor called" << std::endl;
	return ;
}

void IRCServer::initServer() {
	if (getListenerSocket())
		throw std::runtime_error("Failed to create listener socket");
	// if (pollingRoutine())
	// 	throw std::runtime_error("Polling failed");
	return ;
}

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

	CircularBuffer cb;
	this->circularBuffers.push_back(cb);
	return (0);
}

// void IRCServer::addToPfds(){
// 	return ;
// }

// void IRCServer::delFromPfds(){
// 	return ;
// }

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
		CircularBuffer cbuf;
		this->circularBuffers.push_back(cbuf);
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
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
	pfds.erase(this->pfds.begin() + i);
	return ;
}

void IRCServer::replyToMsg(nfds_t i) {
	std::ostringstream messageStream;
    messageStream << "Hello client number " << i << " !\r\n";
    std::string message = messageStream.str();
	const char* msg = message.c_str();
	
	size_t	msg_len = strlen(msg);
	ssize_t total = 0;
	ssize_t n_sent = 0;
	while (total < static_cast<ssize_t>(msg_len) ){
		if ( (n_sent = send( pfds[i].fd,  &(msg[total]), msg_len, 0 ) ) <= 0)
			std::cerr << "Send failed" << std::endl;
		total += n_sent;
	}
	std::cout << "Sent: " << n_sent << "/" << total << "bytes." << std::endl;
}

int IRCServer::receiveMsg(nfds_t i) {
	char buf[MAXDATASIZE];
	ssize_t numbytes;
	numbytes = recv(this->pfds[i].fd, buf, MAXDATASIZE-1, 0);
	if (numbytes <= 0) {
		dropConnection(numbytes, i);
		return (-1);
	}
	buf[numbytes] = '\0';
	this->circularBuffers[i].addToBuffer(buf, numbytes);
	if (circularBuffers[i].findCRLF() == -1) {
		std::cout << "did not detect CRLF" << std::endl;
		return (0);
	}
	std::string msg = circularBuffers[i].extractBuffer();
	std::cout << "Server: received message: " << msg << std::endl;
	//parse message to message object
	//analyze
	replyToMsg(i);
	return (0);
}

int IRCServer::pollingRoutine() {
	int poll_count;
	int j = 0;
	nfds_t fd_count = static_cast<nfds_t>(this->pfds.size());
	while (1) {
		if ((poll_count = poll(&(pfds[0]), fd_count, -1)) == -1)//of &pfds[0]
			return (-1);
		for (nfds_t i = 0; i < fd_count; i++) {
			if (this->pfds[i].revents & POLLIN) { //We have a new event
				if (i == 0) { //Listener has a client in accept queue
					if (acceptClient())
						continue ;
					fd_count++;
				} else { //A client has sent us a message
					std::cout <<"Received msgs:" << j++ << std::endl;
 					if (receiveMsg(i)) {
						fd_count--;
						continue ;
					}
				}
			}
		}
	}
	for (nfds_t i = 0; i < fd_count; i++) {
		close(pfds[i].fd);
	}
	return (0);
}
