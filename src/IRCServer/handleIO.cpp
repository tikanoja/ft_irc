/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:39:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 12:59:19 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IRCServer.hpp"

int IRCServer::receiveMsg(User* user, nfds_t i) {
	
	char buf[MAXDATASIZE];
	std::memset(buf, '\0', MAXDATASIZE);
	ssize_t numbytes;
	numbytes = recv(p_pfds[i].fd, buf, MAXDATASIZE - 1, 0);
	if (numbytes <= 0) {
		dropConnection(numbytes, i);
		return (-1);
	}
	if (buf[0] == '\n')
		return 0;
	user->getRecvBuffer().addToBuffer(buf);
	return (0);
}

int IRCServer::checkRecvBuffer(User* user, nfds_t i) {
	
	if (user->getRecvBuffer().findCRLF() == -1) {
		return (0);
	}
	std::string msg = user->getRecvBuffer().extractBuffer();
	p_logger->log("Received message from " + user->getNick(), __FILE__, __LINE__);
	Message m(msg);
	executeCommand(*user, m);
	(void)i;
	return 0;
}

int IRCServer::checkSendBuffer(User* user) {
	
	if (user->getSendBuffer().emptyCheck() == 0) {
		return 0;
	} 
	if (user->getSendBuffer().emptyCheck() == 1) {
		std::string toSend = user->getSendBuffer().extractBuffer();
		ssize_t toSendLen = static_cast<ssize_t>(toSend.length());
		char* toSendC = new char[toSendLen];
		std::memset(toSendC, '\0', static_cast<size_t>(toSendLen));
		for (size_t i = 0; i < static_cast<size_t>(toSendLen); i++)
			toSendC[i] = toSend[i];
		ssize_t n_sent = 0;
		if ( (n_sent = send(user->getSocket(),  &(toSendC[0]), static_cast<size_t>(toSendLen), 0) ) <= 0)
			p_logger->log("Failed to send to " + user->getNick(), __FILE__, __LINE__);
		if (n_sent > 0 && n_sent < toSendLen) {
			toSend.erase(0, static_cast<size_t>(n_sent));
			user->getSendBuffer().replaceUnsent(toSend);
		}
		delete[] toSendC;
	}
	return 0;
}
