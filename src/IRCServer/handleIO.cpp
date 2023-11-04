/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleIO.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:39:39 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/04 11:26:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IRCServer.hpp"

int IRCServer::receiveMsg(User* user, nfds_t i) {
	
	char buf[MAXDATASIZE * 4];
	std::memset(buf, '\0', MAXDATASIZE * 4);
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
		bool tooLong = false;
		std::string toSend = user->getSendBuffer().extractBuffer();
		ssize_t toSendLen = static_cast<ssize_t>(toSend.length());
		if (toSendLen > 512) {
			toSendLen = 512;
			tooLong = true;
		}
		char* toSendC = new char[static_cast<size_t>(toSendLen)];
		std::memset(toSendC, '\0', static_cast<size_t>(toSendLen)); //is this necessary since we are filling it up to its len anyways?
		for (size_t i = 0; i < static_cast<size_t>(toSendLen); i++)
			toSendC[i] = toSend[i];
		if (tooLong == true) {
			toSendC[510] = '\r';
			toSendC[511] = '\n';
		}
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
