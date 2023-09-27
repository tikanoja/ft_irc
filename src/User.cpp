/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:33:50 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/27 11:32:23 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/User.hpp"

User::User(const std::string password, const std::string nickname,
	const std::string username) : p_password(password), p_username(username),
	p_nickname(nickname){
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
	if(this != &rhs)
		p_ATTRIBUTE = rhs.p_ATTRIBUTE;
	return *this;
}

User User::createUser(const std::string password, const std::string username)