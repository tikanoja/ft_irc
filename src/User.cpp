/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:33:50 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/29 11:49:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User(const std::string password, const std::string nickname,
	const std::string username) : p_password(password), p_nickname(nickname), p_username(username){
	std::cout << "User param constructor called" << std::endl;
}


User::User()
{
	std::cout << "User constructor called" << std::endl;
}

User::User(User const& src)
{
	*this = src; 
}

User::~User()
{
	std::cout << "User destructor called" << std::endl;
}

User& User::operator=(User const& rhs)
{
	if(this != &rhs){
		p_password = rhs.p_password;
		p_nickname = rhs.p_nickname;
		p_username = rhs.p_username;
		p_realname = rhs.p_realname;
		p_mode = rhs.p_mode;
		p_socket_fd = rhs.p_socket_fd;
		memcpy(p_ipaddress,rhs.p_ipaddress, INET6_ADDRSTRLEN);
	}
	return *this;
}

void	User::setIP(char const * ip){
	memcpy(p_ipaddress, ip, INET6_ADDRSTRLEN);
}

void	User::setSocket(int socketfd){
	p_socket_fd = socketfd;
}

char*	User::getIP(void){
	return p_ipaddress;
}

int		User::getSocket(void){
	return p_socket_fd;
}
