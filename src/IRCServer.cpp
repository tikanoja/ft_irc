/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:21:45 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/04 16:44:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

IRCServer::IRCServer(uint16_t port) : port(port){
	// std::cout << "IRCServer constructor called" << std::endl;
	pfds.reserve(MAXCLIENTS);
	users.reserve(MAXCLIENTS);
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

void IRCServer::initCommands() {
	static const std::string cmd_names[] = {
		"PASS",
		"NICK"
	};

	static const CommandFunction cmd_functions[] = {
		cmd_pass,
		cmd_nick
	};
	
	for (size_t i = 0; i < N_COMMANDS; i++)
		command_map[cmd_names[i]] = cmd_functions[i];
}

std::string const & IRCServer::getName(){
	return serverName;
}

std::string const & IRCServer::getPassword() const{
	return (password);
}

Uvector		const &	IRCServer::getUsers() const{
	return (users);
}

int IRCServer::receiveMsg(User* user, nfds_t i) {
	char buf[MAXDATASIZE];
	ssize_t numbytes;
	numbytes = recv(this->pfds[i].fd, buf, MAXDATASIZE - 1, 0);
	if (numbytes <= 0) {
		dropConnection(numbytes, i);
		return (-1);
	}
	buf[numbytes] = '\0';
	user->getRecvBuffer().addToBuffer(buf);
	if (user->getRecvBuffer().findCRLF() == -1) {
		std::cout << "did not detect CRLF" << std::endl;
		return (0);
	}
	std::string msg = user->getRecvBuffer().extractBuffer();
	std::cout << "Server: received message: " << msg << std::endl;
	Message m(msg);
	m.printContent();
	// command & function pointer map or something ???
	// respond to the client

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
			if (this->pfds[i].revents & (POLLIN | POLLOUT)) { //We have a new event!! also check for
				if (i == 0) { //Listener has a client in accept queue
					if (acceptClient())
						continue ;
					fd_count++;
				} else { //A client has sent us a message
					std::cout <<"Received msgs:" << j++ << std::endl;
 					if (receiveMsg(users.findUserBySocket(static_cast<int>(i)), i)) {
						fd_count--;
						continue ;
					}
					replyToMsg(i);
				}
			}
		}
	}
	for (nfds_t i = 0; i < fd_count; i++) {
		close(pfds[i].fd);
	}
	return (0);
}
