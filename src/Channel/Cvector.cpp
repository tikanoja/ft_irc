/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cvector.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:57:06 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/01 14:46:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Cvector.hpp"

Cvector::Cvector()
{}

Cvector::Cvector(Cvector const& src)
{
	*this = src;
}

Cvector::~Cvector()
{}

Cvector& Cvector::operator=(Cvector const & rhs)
{
	if (this != &rhs)
		copy(rhs.begin(), rhs.end(), this->begin());
	return *this;
}

std::string Cvector::toIRCLower(std::string const & str) const {
	
	std::string result;
	
	for (size_t i = 0; i < str.size(); i++)
		result += (str[i] >= 'A' && str[i] <= '^' ? str[i] + 32 : str[i]);
	return (result);
}

Channel*		Cvector::findChannel(std::string const & name) const
{
	for (std::vector<Channel*>::const_iterator it = this->begin(); it != this->end(); it++){
		if (toIRCLower((*it)->getName()) == toIRCLower(name))
			return (*it);
	}
	return (NULL);
}

Channel* Cvector::createChannel(std::string const & name)
{
	this->push_back(new Channel(name));
	return this->back();
}

void Cvector::deleteChannel(Channel* toDelete)
{
	for (std::vector<Channel*>::iterator it = this->begin(); it != this->end(); it++){
		if ((*it) == toDelete) {
			delete *it; //delete channel
			it = this->erase(it); //remove channel from vectorx
			std::cout << "Channel removed from vector and deleted!" << std::endl;
			break;
		}
	}
}
