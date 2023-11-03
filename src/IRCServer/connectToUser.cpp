/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connectToUser.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:42:16 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/03 07:33:07 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/IRCServer.hpp"

int IRCServer::getListenerSocket()
{

	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;
	int yes = 1;

	std::stringstream ss;
	ss << p_port;
	std::string str = ss.str();
	const char *server_port = str.c_str();

	// init & configure socket
	std::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	if ((rv = getaddrinfo(NULL, server_port, &hints, &servinfo)))
	{ // resolve addr & port
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		return (-1);
	}

	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) // create a socket
			continue;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
		{
			std::cerr << "Failed to create a socket" << std::endl;
			return (-1);
		}
		fcntl(sockfd, F_SETFL, O_NONBLOCK); // set fd to non-blocking
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{ // bind port to socket
			close(sockfd);
			continue;
		}
		break;
	}
	freeaddrinfo(servinfo);

	if (p == NULL)
	{
		std::cerr << "Failed to connect socket" << std::endl;
		return (-1);
	}
	if (listen(sockfd, MAXCLIENTS) == -1)
	{
		std::cerr << "Failed to listen" << std::endl;
		return (-1);
	}

	struct pollfd pfd;
	pfd.fd = sockfd;
	pfd.events = POLLIN;
	p_pfds.push_back(pfd);

	return (0);
}

void *IRCServer::get_in_addr(struct sockaddr *sa)
{

	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in *)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}

int IRCServer::acceptClient()
{

	char s[INET6_ADDRSTRLEN];
	struct sockaddr_storage their_addr;
	socklen_t sin_size;
	int new_fd;

	if (p_pfds.size() < MAXCLIENTS + 1)
	{
		sin_size = sizeof(their_addr);
		new_fd = accept(p_pfds[0].fd, (struct sockaddr *)&their_addr, &sin_size);
		fcntl(new_fd, F_SETFL, O_NONBLOCK);
		if (new_fd == -1)
		{
			p_logger->log("Unable to accept connection from " + static_cast<std::string>(s), __FILE__, __LINE__);
			return (-1);
		}
		else
		{
			struct pollfd pfd;
			pfd.fd = new_fd;
			pfd.events = POLLIN | POLLOUT;
			p_pfds.push_back(pfd);
			p_fd_count++;
			inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);

			p_users.push_back(new User(new_fd, s, this->getName()));
			p_logger->log("New client accepted from " + static_cast<std::string>(s), __FILE__, __LINE__);
		}
	}
	return (0);
}

void static cleanupChannels(IRCServer &server, User *user)
{

	for (std::vector<Channel *>::iterator it = server.getChannels().begin(); it != server.getChannels().end();)
	{
		if ((*it)->getInvitelist()->findUserByNick(user->getNick()))
		{
			(*it)->removeFromInvlist(*user);
			server.log("Removed " + user->getNick() + "from invite list to " + (*it)->getName(), __FILE__, __LINE__);
		}
		if ((*it)->getMembers()->findUserByNick(user->getNick()) != NULL)
		{
			(*it)->broadcastToChannel(":" + USER_ID(user->getNick(), user->getUserName(), user->getIP()) + " QUIT\r\n", user);
			(*it)->removeFromChops(*user);
			(*it)->removeFromMembers(*user);
		}
		if ((*it)->getMembers()->size() == 0)
		{
			delete (*it);
			std::vector<Channel *>::iterator itBackup = server.getChannels().erase(it);
			it = itBackup;
		}
		else
			it++;
	}
}

void IRCServer::dropConnection(ssize_t numbytes, nfds_t fd_index)
{

	std::stringstream stream;
	stream << fd_index;

	if (numbytes == 0)
	{
		p_logger->log("Connection #" + stream.str() + " closed.", __FILE__, __LINE__);
	}
	else
	{
		p_logger->log("Recv failure: Connection #" + stream.str() + " closed.", __FILE__, __LINE__);
	}
	close(p_pfds[fd_index].fd);
	User *userToRemove = p_users.findUserBySocket(p_pfds[fd_index].fd);
	cleanupChannels(*this, userToRemove);
	if (userToRemove)
		delete userToRemove;
	p_users.erase(std::remove(p_users.begin(), p_users.end(), userToRemove), p_users.end());
	p_pfds.erase(p_pfds.begin() + fd_index);
	p_fd_count--;
	return;
}

void IRCServer::delUser(User &user)
{

	for (size_t i = 0; i < p_users.size(); i++)
	{
		if (user.getSocket() == p_users[i]->getSocket())
		{
			p_users.erase(p_users.begin() + static_cast<ssize_t>(i));
			break;
		}
	}
}

void IRCServer::delFd(User &user)
{

	for (size_t i = 0; i < p_pfds.size(); i++)
	{
		if (user.getSocket() == p_pfds[i].fd)
		{
			p_pfds.erase(p_pfds.begin() + static_cast<ssize_t>(i));
			p_fd_count--;
			break;
		}
	}
}
