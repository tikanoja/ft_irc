/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:21:45 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/23 12:47:11 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"
#include "../inc/Commands.hpp"
#include "../inc/Utils.hpp"

// void bitsToStream(short num, std::ostream& os) {
//     int numBits = sizeof(num) * 8; // Number of bits in a short

//     for (int i = numBits - 1; i >= 0; i--) {
//         // Use bitwise AND to check the i-th bit
//         int bit = (num >> i) & 1;
//         os << bit;
//     }
// }

void signalHandler(int signum) {
	if (signum == SIGINT) {
		std::cout << std::endl << "Server quit." << std::endl;
		//delete p_users
			//(and their buffers ?)
		//delete p_channels
		exit(0);
	}
}

IRCServer::IRCServer(uint16_t port) : p_port(port){
	// std::cout << "IRCServer constructor called" << std::endl;
	p_pfds.reserve(MAXCLIENTS);
	p_users.reserve(MAXCLIENTS);
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
	initCommands();
	initOperators();
	return ;
}

void IRCServer::initCommands() {
	static const std::string cmdNames[] = {
		"PASS",
		"NICK",
		"USER",
		"MODE",
		"QUIT",
		"JOIN",
		"PING",
		"PONG",
		"PRIVMSG",
		"KILL",
		"PART",
		"TOPIC",
		"KICK"
	};

	static const CommandFunction cmdFunctions[] = {
		cmd_pass,
		cmd_nick,
		cmd_user,
		cmd_mode,
		cmd_quit,
		chan_cmd_join,
		cmd_ping,
		cmd_pong,
		cmd_privmsg,
		cmd_kill,
		chan_cmd_part,
		chan_cmd_topic,
		chan_cmd_kick
	};
	for (size_t i = 0; i < N_COMMANDS; i++)
		p_commandMap[cmdNames[i]] = cmdFunctions[i];
}

std::string const & IRCServer::getName() const{
	return p_serverName;
}

std::string const & IRCServer::getPassword() const{
	return p_password;
}

Uvector const &	IRCServer::getUsers() const{
	return p_users;
}

Cvector & IRCServer::getChannels(){
	return p_channels;
}

std::vector<std::string> const &		IRCServer::getBlocked() const{
	return p_blockeUserNames;
}

std::vector<Operator> const &	IRCServer::getOpers() const{
	return p_opers;
}

void IRCServer::setBlocked(std::string nick){
	p_blockeUserNames.push_back(nick);
}

bool	IRCServer::isBlocked(std::string nick) const{

	std::vector<std::string>::const_iterator it;

	for (it = p_blockeUserNames.begin(); it != p_blockeUserNames.end(); it++){
		if (*it == nick)
			return true;
	}
	return false;
}

void IRCServer::delUser(User& user) {
	for (size_t i = 0; i < p_users.size(); i++) {
		if (user.getSocket() == p_users[i]->getSocket()) {
			p_users.erase(p_users.begin() + static_cast<ssize_t>(i));
			break ;
		}
	}
}

void IRCServer::delFd(User& user) {
	for (size_t i = 0; i < p_pfds.size(); i++) {
		if (user.getSocket() == p_pfds[i].fd) {
			p_pfds.erase(p_pfds.begin() + static_cast<ssize_t>(i));
			p_fd_count--;
			break ;
		}
	}
}

void IRCServer::initOperators(){

	std::ifstream operFile;

	operFile.open("config/operators.config", std::fstream::in);
	if (!operFile.good() || !operFile.is_open() || operFile.peek() < 0){
		std::cout << "Cannot set any operators" << std::endl;
		return ;
	}
	char line[256];
	std::vector<std::string> rawOper;
	while (operFile.getline(line, 256)){
		std::cout << line << std::endl;
		std::string string = line;
		rawOper = split(string, ' ');
		p_opers.push_back(Operator(rawOper[0], rawOper[1], rawOper[2]));
	}
}

int IRCServer::receiveMsg(User* user, nfds_t i) {
	char buf[MAXDATASIZE];
	memset(buf, '\0', MAXDATASIZE);
	ssize_t numbytes;
	numbytes = recv(p_pfds[i].fd, buf, MAXDATASIZE - 1, 0);
	if (numbytes <= 0) {
		dropConnection(numbytes, i);
		return (-1);
	}
	if (numbytes == 1) {
		std::cout << "Recieved empty message. (Just a newline from nc?)" << std::endl;
		return (0);
	}
	user->getRecvBuffer().addToBuffer(buf);
	return (0);
}

int IRCServer::checkRecvBuffer(User* user, nfds_t i) {
	if (user->getRecvBuffer().findCRLF() == -1) { //do we have a complete msg ???
		// std::cout << "did not detect CRLF" << std::endl;
		return (0);
	}
	std::string msg = user->getRecvBuffer().extractBuffer();
	Message m(msg);
	std::cout << std::endl << "RECEIVED: ";
	m.printContent();
	std::cout << std::endl;
	executeCommand(*user, m);
	(void)i;
	return 0;
}

int IRCServer::checkSendBuffer(User* user) {
	if (user->getSendBuffer().emptyCheck() == 0) {
		return 0;
	} if (user->getSendBuffer().emptyCheck() == 1) {
		std::string toSend = user->getSendBuffer().extractBuffer();
		std::cout << "SENDING: " << std::endl << toSend << std::endl;
		ssize_t toSendLen = static_cast<ssize_t>(toSend.length());
		char* toSendC = new char[toSendLen];
		memset(toSendC, '\0', static_cast<size_t>(toSendLen)); //this fixed the buffer duplicating...
		for (size_t i = 0; i < static_cast<size_t>(toSendLen); i++)
			toSendC[i] = toSend[i];
		ssize_t n_sent = 0;
		if ( (n_sent = send(user->getSocket(),  &(toSendC[0]), static_cast<size_t>(toSendLen), 0) ) <= 0)
			std::cerr << "Send failed" << std::endl;
		if (n_sent > 0 && n_sent < toSendLen) {
			toSend.erase(0, static_cast<size_t>(n_sent));
			const char* toBuffer = toSend.c_str();
			user->getSendBuffer().addToBuffer(toBuffer, toSendLen - n_sent);
		}
		delete[] toSendC;
	}
	return 0;
}

//check for POLLNVAL & POLLERR
int IRCServer::pollingRoutine() {
	int poll_count;
	int j = 0;
	p_fd_count = static_cast<nfds_t>(p_pfds.size());
	signal(SIGINT, signalHandler);
	while (1) {
		if ((poll_count = poll(&(p_pfds[0]), p_fd_count, 50)) == -1) //!!!!!!!!!!!! TIMEOUT
			return (-1);
		for (nfds_t i = 0; i < p_fd_count; i++) {
			if (p_pfds[i].revents & (POLLIN | POLLOUT | POLLNVAL | POLLERR | POLLHUP)) {
				if (i == 0) { //Listener has a client in accept queue
					if (acceptClient())
						continue ;
				} else if (p_pfds[i].revents & POLLIN) { //A client has sent us a message, add to buffer!
					std::cout << "Received msgs:" << j++ << std::endl;
 					if (receiveMsg(p_users.findUserBySocket(p_pfds[i].fd), i))
						continue ;
				} else if (p_pfds[i].revents & POLLOUT) { //A client has sent us a message, add to buffer!
					std::cout << "Ready to receive!" << std::endl;
				} else if (p_pfds[i].revents & POLLHUP) {
					std::cout << "They hang up!" << std::endl;
				} else {
					std::cout << "Polling invalid / error!" << std::endl;
					std::cout << "p_fd_count: " << p_fd_count << std::endl;
					std::cout << "p_pfds.size(): " << p_pfds.size() << std::endl;
					std::cout << "p_users.size() " << p_users.size() << std::endl;
					dropConnection(-1, i);
				}
				// std::cout << "our bits: ";
				// bitsToStream(p_pfds[i].revents, std::cout);
				// std::cout << std::endl;
			}
			if (i != 0) {
				checkSendBuffer(p_users.findUserBySocket(p_pfds[i].fd));
				checkRecvBuffer(p_users.findUserBySocket(p_pfds[i].fd), i);
			}
		}
	}
	for (nfds_t i = 0; i < p_fd_count; i++) {
		close(p_pfds[i].fd);
	}
	return (0);
}
