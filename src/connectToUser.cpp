/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectToUser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/31 10:28:38 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

int IRCServer::getListenerSocket() {
	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;
	int yes = 1;

	std::stringstream ss;
	ss << p_port;
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
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1){
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
	p_pfds.push_back(pfd);

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
	new_fd = accept(p_pfds[0].fd, (struct sockaddr *)&their_addr, &sin_size);
	fcntl(new_fd, F_SETFL, O_NONBLOCK); // ?
	if (new_fd == -1) {
		std::cerr << "Failed to accept client" << std::endl;
		return (-1);
	} else {
		struct pollfd pfd;
		pfd.fd = new_fd;
		pfd.events = POLLIN;
		p_pfds.push_back(pfd);
		p_fd_count++;
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);

		p_users.push_back(new User(new_fd, s));
		std::cout << "Server: new connection from: " << s << std::endl;
	}
	return (0);
}

void static cleanupChannels(IRCServer &server, User* user) {
	for(std::vector<Channel*>::iterator it = server.getChannels().begin(); it != server.getChannels().end();){
		if ((*it)->getInvitelist()->findUserByNick(user->getNick())) {//remove from invitelist
			(*it)->removeFromInvlist(*user);
			std::cout << "Disconnected user removed from invite list!" << std::endl;
		}
		if ((*it)->getMembers()->findUserByNick(user->getNick()) != NULL) { //they are on channel
			(*it)->removeFromChops(*user); //remove from chops
			(*it)->removeFromMembers(*user); //remove from members
		}
		if ((*it)->getMembers()->size() == 0) { //channel emptied
			delete (*it);
			std::vector<Channel*>::iterator itBackup = server.getChannels().erase(it);
			it = itBackup;
		}
		else
			it++;
	}
}

void IRCServer::dropConnection(ssize_t numbytes, nfds_t fd_index) {
	if (numbytes == 0)
		std::cout << "Connection #" << fd_index << " closed." << std::endl;
	else {
		std::cerr << "Recv failed. Numbytes: " << numbytes << std::endl;
	}
	close(p_pfds[fd_index].fd);
	User *userToRemove = p_users.findUserBySocket(p_pfds[fd_index].fd);
	//channel cleanup!!!!!!
		//check channels
			//if present, remove from chops, invitelist, p_members
	cleanupChannels(*this, userToRemove);
	//correct order for these?
	if (userToRemove)
		delete userToRemove;
	p_users.erase(std::remove(p_users.begin(), p_users.end(), userToRemove), p_users.end());
	p_pfds.erase(p_pfds.begin() + fd_index);
	p_fd_count--;
	return ;
}
