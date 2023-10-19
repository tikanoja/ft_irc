/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:29:10 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/19 15:00:07 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

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
	return &(this->p_members);
}

void Channel::broadcastToChannel(std::string message)
{
	for (size_t i = 0; i < p_members.size(); i++) {
		p_members[i]->send(message);
	}
}
