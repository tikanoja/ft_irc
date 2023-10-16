/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:33:50 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/16 09:09:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User(int const socket_fd, char const * ipaddress) : p_socket_fd(socket_fd){
	std::cout << "User param constructor called" << std::endl;
	memcpy(p_ipaddress, ipaddress, INET6_ADDRSTRLEN);
	p_mode = 0;
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
	if (this != &rhs){
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

void	User::setNick(std::string nickname){
		p_nickname = nickname.substr(0, 9);
}

bool	User::setMode(int mode){
	if (!(p_mode & mode)){
		p_mode |= mode;
		return true;
	}
	return false;
}

bool	User::unsetMode(int mode){
		
	if ((p_mode & mode)){
		p_mode &= ~mode;
		return true;
	}
	return false;
}

void User::setRealName(std::string realname){
		p_realname = realname;
}

void User::setUserName(std::string username){
		p_username = username;
}

char const * User::getIP(void) const {
	return p_ipaddress;
}

int User::getSocket(void) const {
	return p_socket_fd;
}

std::string	const &	User::getNick(void) const {
	return p_nickname;
}

int	User::getMode(void) const {
	return p_mode;
}

std::string	const &	User::getRealName(void) const {
	return p_realname;
}

std::string	const &	User::getUserName(void) const {
	return p_username;
}

CircularBuffer & User::getRecvBuffer(void) {
	return p_recvBuffer;
}

CircularBuffer & User::getSendBuffer(void) {
	return p_sendBuffer;
}

void	User::resetBuffers(void){
	p_recvBuffer.clear();
	p_sendBuffer.clear();
}


std::ostream & operator<<( std::ostream & o, User const & user){

	o 	<< "USER CONTNENT\n" 
		<< "Nick: " << user.getNick() << "\n"
		<< "User:"<< user.getUserName() << "\n"
		<< "Real:"<< user.getRealName() << "\n"
		<< "Mode:"<< user.getMode() << "\n"
		<< "Socket: "<< user.getSocket() << "\n"
		<< "IP Address: "<< user.getIP() << std::endl;
	return o;
}

void	User::setAwayMsg(std::string const & comment){
	p_awaymsg = comment;
}
