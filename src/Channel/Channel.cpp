/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:29:10 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/01 14:55:42 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"
#include <sstream>

Channel::Channel(const std::string name) : p_name(name)
{
	p_mode = static_cast<chanModes>(0);
	return ;
}

Channel::~Channel(void)
{
	return ;
}

std::string Channel::getName()
{
	return p_name;
}

std::string Channel::getTopic()
{
	return p_topic;
}

unsigned int Channel::getMode()
{
	return p_mode;
}

std::string	Channel::getChanModes(){
	static const chanModes permissions[] = {invite, topic_rest, key, limit};
	static const std::string characters = "itkl";
	std::string result = "+";
	unsigned int mode = this->getMode();

	for(size_t i = 0; i < characters.size(); i++) {
		if (mode & permissions[i])
			result += characters[i];
	}
	return result;
}
std::string		Channel::getChanStr(){
	std::string modestr = "";
	std::stringstream ss;
	ss << p_maxusers;

	if (this->p_key != "" && (this->getMode() & key))
		modestr += p_key;
	if (this->getMode() & limit)
		modestr += ss.str();
	return modestr;
}

void Channel::setTopic(std::string newTopic)
{
	p_topic = newTopic;
}

Uvector* Channel::getMembers()
{
	return &p_members;
}

Uvector* Channel::getChops()
{
	return &p_chops;
}

Uvector* Channel::getInvitelist()
{
	return &p_invitelist;
}

bool Channel::getUserlimit()
{
	return p_maxusers;
}

std::string Channel::getKey()
{
	return p_key;
}

size_t Channel::getMaxusers()
{
	return this->p_maxusers;
}

void Channel::broadcastToChannel(std::string message, User* sender)
{
	for (size_t i = 0; i < p_members.size(); i++) {
		if (sender != NULL && p_members[i]->getNick() == sender->getNick())
			continue ;
		p_members[i]->send(message);
	}
}

bool Channel::isChop(User& user)
{
	if (this->getChops()->findUserByNick(user.getNick()) != NULL)
		return true;
	else
		return false;
}

void Channel::setKey(std::string key){
	p_key = key;
}

void Channel::removeFromChops(User& user)
{
	for (std::vector<User*>::iterator it = this->p_chops.begin(); \
		it != this->p_chops.end(); it++){
		if ((*it) == &user) {
			this->p_chops.erase(it);
			break;
		}
	}
}

void Channel::removeFromInvlist(User& user)
{

	for (std::vector<User*>::iterator it = this->p_invitelist.begin(); \
		it != this->p_invitelist.end(); it++){
		if ((*it) == &user) {
			this->p_invitelist.erase(it);
			break;
		}
	}
}

void Channel::removeFromMembers(User& user)
{
	for (std::vector<User*>::iterator it = this->p_members.begin(); \
		it != this->p_members.end(); it++){
		if ((*it) == &user) {
			this->p_members.erase(it);
			break;
		}
	}
}

bool Channel::setUserlimit(std::string limitstr) {
	std::stringstream ss(limitstr);
	unsigned int limit;
	ss >> limit;
	if (ss.fail()) {
		return false;
	}
	this->p_maxusers = limit;
	return true;
}

bool Channel::setChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		return false;
	}
	if (this->getChops()->findUserByNick(target) != NULL) {
		return false;
	}
	this->getChops()->push_back(newChop);
	return true;
}

bool Channel::unsetChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		return false;
	} 
	if (this->getChops()->findUserByNick(target) == NULL) {
		return false;
	}
	for (std::vector<User*>::iterator it = this->getChops()->begin(); \
		it != this->getChops()->end(); it++){
		if ((*it) == newChop) {
			this->getChops()->erase(it);
			break;
		}
	}
	return true;
}

bool	Channel::setMode(chanModes mode){
	if (!(p_mode & mode)){
		p_mode = static_cast<Channel::chanModes>(p_mode | mode);
		return true;
	}
	return false;
}

bool	Channel::unsetMode(chanModes mode){
	if ((p_mode & mode)){
		p_mode = static_cast<Channel::chanModes>(p_mode & ~mode);
		return true;
	}
	return false;
}