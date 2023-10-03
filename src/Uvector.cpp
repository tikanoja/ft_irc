/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uvector.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:16:04 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/03 15:11:50 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Uvector.hpp"

char const * Uvector::UserNotFound::what() const throw(){
		return "User not found";
}

Uvector::Uvector()
{}

Uvector::Uvector(Uvector const& src)
{
	*this = src;
}

Uvector::~Uvector()
{}

Uvector& Uvector::operator=(Uvector const & rhs)
{
	if (this != &rhs)
		copy(rhs.begin(), rhs.end(), this->begin());
	return *this;
}

User*		Uvector::findUserBySocket(int const socket_fd)
{
	for (std::vector<User*>::iterator it = this->begin(); it != this->end(); it++){
		if ((*it)->getSocket() == socket_fd)
			return (*it);
	}
	return NULL;
}

User*		Uvector::findUserByNick(std::string const & nick)
{
	for (std::vector<User*>::iterator it = this->begin(); it != this->end(); it++){
		if ((*it)->getNick() == nick)
			return (*it);
	}
	throw(UserNotFound());
}
