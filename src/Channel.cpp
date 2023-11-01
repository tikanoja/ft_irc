/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:29:10 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/31 14:15:33 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sstream>

Channel::Channel(const std::string name) : p_name(name)
{
	std::cout << "Channel constructor called" << std::endl;
	p_mode = static_cast<chanModes>(0);
	return ;
}

Channel::~Channel(void)
{
	std::cout << "Channel destructor called" << std::endl;
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
			this->p_chops.erase(it); //remove the user from p_chops
			break;
		}
	}
}

void Channel::removeFromInvlist(User& user)
{

	for (std::vector<User*>::iterator it = this->p_invitelist.begin(); \
		it != this->p_invitelist.end(); it++){
		if ((*it) == &user) {
			this->p_invitelist.erase(it); //remove the user from p_chops
			break;
		}
	}
}

void Channel::removeFromMembers(User& user)
{
	for (std::vector<User*>::iterator it = this->p_members.begin(); \
		it != this->p_members.end(); it++){
		if ((*it) == &user) {
			this->p_members.erase(it); //remove the user from p_chops
			break;
		}
	}
}

bool Channel::setUserlimit(std::string limitstr) {
	std::stringstream ss(limitstr);
	unsigned int limit;
	ss >> limit;
	if (ss.fail()) {
		std::cout << "failed to convert user limit to int!" << std::endl;
		return false;
	}
	this->p_maxusers = limit;
	return true;
}

bool Channel::setChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		std::cout << "new chop candidate not found on channel" << std::endl;
		return false;
	}
	if (this->getChops()->findUserByNick(target) != NULL) {
		std::cout << "the user is already a chop, no need to add" << std::endl;
		return false;
	}
	this->getChops()->push_back(newChop);
	std::cout << "GZ new chop " << newChop->getNick() << std::endl;
	return true;
}

bool Channel::unsetChop(std::string target) {
	User* newChop = this->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		std::cout << "new chop candidate not found on channel" << std::endl;
		return false;
	} 
	if (this->getChops()->findUserByNick(target) == NULL) {
		std::cout << "the user is not a chop, no need to remove rights" << std::endl;
		return false;
	}
	for (std::vector<User*>::iterator it = this->getChops()->begin(); \
		it != this->getChops()->end(); it++){
		if ((*it) == newChop) {
			this->getChops()->erase(it); //remove the user from p_chops!!!!
			std::cout << "User " << newChop->getNick() << " just got their chops removed!" << std::endl;
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

std::string	Channel::setBatchMode(std::vector<std::string> const & modes, size_t & word,
	size_t & character, std::vector<size_t> & indeces){

	std::string					opsdone = "";
	static const std::string	characters = "itkol";
	size_t						move_flag = 0;

	if (modes.at(word)[character] == '+')
	{
		for (; character < modes.at(word).size(); character++ ){
			switch (modes.at(word)[character]){
				case ('i'):
					if (this->setMode(invite))
						opsdone += characters[0];
					break;
				case ('t'):
					if (this->setMode(topic_rest))
						opsdone += characters[1];
					break;
				case ('k'):
					if (word + ++move_flag < modes.size()){
							this->setMode(key);
							this->setKey(modes.at((word + move_flag)));
							indeces.push_back(word + move_flag);
							opsdone += characters[2];
					}
					break;
				case ('o'):
					if (word + ++move_flag < modes.size()){
							std::cout << modes.at(word + move_flag) << std::endl;
						if (this->setChop(modes.at(word + move_flag))){
							indeces.push_back(word + move_flag);
							opsdone += characters[3];
						}
					}
					break;
				case ('l'):
					if (word + ++move_flag < modes.size()){
							this->setMode(limit);
							indeces.push_back(word + move_flag);
							opsdone += characters[4];
					}
					break;
				case ('-'):
					opsdone += "-" + unsetBatchMode(modes, word, character, indeces);
					return opsdone;
				default:
					continue;
			}
		}
	}
	word += move_flag;
	return opsdone;
}

std::string	Channel::unsetBatchMode(std::vector<std::string> const & modes, size_t & word,
	size_t & character, std::vector<size_t> & indeces){

	std::string					opsdone = "";
	static const std::string	characters = "itkol";
	size_t						move_flag = 1;

	if (modes.at(word)[character] == '-')
	{
		for (; character < modes.at(word).size(); character++ ){
			switch (modes.at(word)[character]){
				case ('i'):
					if (this->setMode(invite))
						opsdone += characters[0];
					break;
				case ('t'):
					if (this->setMode(topic_rest))
						opsdone += characters[1];
					break;
				case ('k'):
					if (this->unsetMode(key)){
						opsdone += characters[2];
					}
					break;
				case ('o'):
					if (word + ++move_flag < modes.size()){
						std::cout << modes.at(word + move_flag) << std::endl;
						if (this->unsetChop(modes.at(word + move_flag))){
							opsdone += characters[3];
							indeces.push_back(word + move_flag);
						}
					}
					break;
				case ('l'):
					if (this->unsetMode(limit)){
							opsdone += characters[4];
					}
					break;
				case ('+'):
					opsdone += "+" + setBatchMode(modes, word, character, indeces);
					return opsdone;
				default:
					continue;
			}
		}
	}
	word += move_flag - 1;
	return opsdone;
}
