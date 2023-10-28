/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:29:10 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/28 16:09:51 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <sstream>

Channel::Channel(const std::string name) : p_name(name)
{
	std::cout << "Channel constructor called" << std::endl;
	return ;
}

Channel::Channel(Channel const& src)
{
	*this = src;
}

Channel& Channel::operator=(Channel const& rhs)
{
	if(this != &rhs) {
		p_name = rhs.p_name;
	}
	return *this;
}

Channel::~Channel(void)
{
	std::cout << "Channel destructor called" << std::endl;
	return ;
}

std::string Channel::getName()
{
	return this->p_name;
}


std::string Channel::getTopic()
{
	return this->p_topic;
}

void Channel::setTopic(std::string newTopic)
{
	this->p_topic = newTopic;
}

Uvector* Channel::getMembers()
{
	return &this->p_members;
}

Uvector* Channel::getChops()
{
	return &this->p_chops;
}

Uvector* Channel::getInvitelist()
{
	return &this->p_invitelist;
}

void Channel::broadcastToChannel(std::string message, User* sender)
{
	for (size_t i = 0; i < p_members.size(); i++) {
		if (sender != NULL && p_members[i]->getNick() == sender->getNick())
			continue ;
		p_members[i]->send(message);
	}
}

void Channel::toggleInviteonly(bool status) {
	if (status == true)
		this->p_inviteonly = true;
	else
		this->p_inviteonly = false;
}

void Channel::toggleTopicrestricted(bool status) {
	if (status == true)
		this->p_topicrestricted = true;
	else
		this->p_topicrestricted = false;
}

void Channel::toggleKeyneeded(bool status, std::string key) {
	if (status == true) {
		this->p_keyneeded = true;
		this->p_key = key;
	}
	else {
		this->p_keyneeded = false;
		this->p_key = "";
	}
}

void Channel::toggleUserlimit(bool status, std::string limitstr) {
	std::stringstream ss(limitstr);
    int limit;
    ss >> limit;
    if (ss.fail()) {
        std::cout << "failed to convert user limit to int!" << std::endl;
    }
	//if limit is a crazy number (bigger than max connections?) do something
	if (status == true) {
		this->p_userlimit = true;
		this->p_maxusers = limit;
	}
	else
		this->p_userlimit = false;
		//this->p_maxusers = default value ?
}

void Channel::toggleChoprights(bool status, std::string target, Channel* chan) {
	User* newChop = chan->getMembers()->findUserByNick(target);
	if (newChop == NULL) {
		std::cout << "new chop candidate not found on channel" << std::endl;
		return;
	}
	
	if (status == true) { //adding a new chop
		if (chan->getChops()->findUserByNick(target) != NULL) {
			std::cout << "the user is already a chop, no need to add" << std::endl;
			return ;
		}
		chan->getChops()->push_back(newChop);
		std::cout << "GZ new chop " << newChop->getNick() << std::endl;
	}
	else { //removing current chop
		//make it so that the OG chop cannot get rights removed ?
		if (chan->getChops()->findUserByNick(target) == NULL) {
			std::cout << "the user is not a chop, no need to remove rights" << std::endl;
			return ;
		}
		for (std::vector<User*>::iterator it = chan->getChops()->begin(); \
			it != chan->getChops()->end(); it++){
			if ((*it) == newChop) {
				chan->getChops()->erase(it); //remove the user from p_chops!!!!
				std::cout << "User " << newChop->getNick() << " just got their chops removed!" << std::endl;
				break;
			}
		}
	}
}
