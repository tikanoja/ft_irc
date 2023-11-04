/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:29:10 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/04 14:35:39 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"
#include "../../inc/Reply.hpp"
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

std::string const & Channel::getName() const
{
	return p_name;
}

std::string const & Channel::getTopic() const
{
	return p_topic;
}

unsigned int Channel::getMode() const
{
	return p_mode;
}

std::string	Channel::getChanModes() const {
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

std::string	Channel::getChanStr() const{
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

bool Channel::getUserlimit() const
{
	return p_maxusers;
}

std::string const & Channel::getKey() const
{
	return p_key;
}

size_t Channel::getMaxusers() const
{
	return this->p_maxusers;
}

std::string	Channel::getNicks() const{
	
	std::string result;

	for (Uvector::const_iterator it = p_members.begin(); it != p_members.end(); it++){

		User* op = p_chops.findUserByNick((*it)->getNick());
		if (it != p_members.begin())
			result += " ";
		if (op)
			result += "@";
		result += (*it)->getNick();
	}
	return result;
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

int Channel::setChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		return 1;
	}
	if (this->getChops()->findUserByNick(target) != NULL) {
		return 2;
	}
	this->getChops()->push_back(newChop);
	return 0;
}

int Channel::unsetChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		return 1;
	} 
	if (this->getChops()->findUserByNick(target) == NULL) {
		return 2;
	}
	for (std::vector<User*>::iterator it = this->getChops()->begin(); \
		it != this->getChops()->end(); it++){
		if ((*it) == newChop) {
			this->getChops()->erase(it);
			break;
		}
	}
	return 0;
}

void Channel::reopChannel(std::string const & servername){

	if (this->getMembers()->size() > 0 && this->getChops()->size() == 0){
		User *new_chop = this->getMembers()->front();
		this->setChop(new_chop->getNick());
		this->broadcastToChannel(RPL_CHANNELMODEIS(servername, new_chop->getNick(),
			this->getName(), "+o", new_chop->getNick()), NULL);
	}
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
