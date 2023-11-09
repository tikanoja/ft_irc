/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:33:50 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/09 08:40:59 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/User.hpp"
#include "../../inc/IRCServer.hpp"
#include "../../inc/Reply.hpp"

User::User(int const socket_fd, char const * ipaddress, std::string host) : p_socket_fd(socket_fd){

	std::memcpy(p_ipaddress, ipaddress, INET6_ADDRSTRLEN);
	p_host = host;

	p_mode = 0;
	p_nickFlag = false;
	p_userFlag = false;
	p_passFlag = false;
	p_welcomeFlag = false;
}

User::User()
{}

User::User(User const& src)
{
	*this = src; 
}

User::~User()
{}

User& User::operator=(User const& rhs)
{
	if (this != &rhs){
		p_nickname = rhs.p_nickname;
		p_username = rhs.p_username;
		p_realname = rhs.p_realname;
		p_mode = rhs.p_mode;
		p_socket_fd = rhs.p_socket_fd;
		std::memcpy(p_ipaddress,rhs.p_ipaddress, INET6_ADDRSTRLEN);
	}
	return *this;
}

void	User::setIP(char const * ip){
	std::memcpy(p_ipaddress, ip, INET6_ADDRSTRLEN);
}

void	User::setSocket(int socketfd){
	p_socket_fd = socketfd;
}

void	User::setNick(std::string nickname){
		p_oldNick = p_nickname;
		p_nickname = nickname.substr(0, 9);
}

void	User::setOldNick(std::string nickname){
		p_oldNick = nickname.substr(0, 9);
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

void User::setHostServer(std::string hostname){
		p_host = hostname;
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

std::string	const &	User::getOldNick(void) const {
	return p_oldNick;
}

int	User::getMode(void) const {
	return p_mode;
}

std::string	const & User::getHostServer(void) const {
	return p_host;
}

std::string	const &	User::getRealName(void) const {
	return p_realname;
}

std::string	const &	User::getUserName(void) const {
	return p_username;
}

DynamicBuffer & User::getRecvBuffer(void) {
	return p_recvBuffer;
}

DynamicBuffer & User::getSendBuffer(void) {
	return p_sendBuffer;
}

void	User::resetBuffers(void){
	p_recvBuffer.clear();
	p_sendBuffer.clear();
}

void	User::setAwayMsg(std::string const & comment){
	p_awaymsg = comment;
}

std::string	const &	User::getAwayMsg(void) const{
	return p_awaymsg;
}

void User::send(std::string str) {
	this->getSendBuffer().addToBuffer(str.c_str());
}

void	User::setRegistrationFlag(int i, IRCServer& server)
{
	if (i == 1)
		p_nickFlag = true;
	else if (i == 2)
		p_userFlag = true;
	else if (i == 3) {
		if (p_passFlag == true)
			return ;
		p_passFlag = true;
		this->send(":PawsitiveIRC NOTICE * :Pawsword accepted! Please proceed with NICK and USER commands.\r\n");
	}

	if (p_welcomeFlag == false && p_nickFlag == true && p_userFlag == true && p_passFlag == true) {
		p_welcomeFlag = true;
		this->setMode(IRCServer::registered);
		this->send(RPL_WELCOME(server.getName(), this->getNick(), this->getUserName(), server.getName()));
		this->send(RPL_YOURHOST(server.getName(), server.getVersion()));
		this->send(RPL_CREATED(server.getName(), server.getDate()));
		this->send(RPL_MYINFO(server.getName(), server.getVersion(), server.getUmodes(), server.getCmodes()));
		motd(server, *this);
	}
}

bool User::getPassFlag()
{
	return this->p_passFlag;
}
