/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:03:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/19 17:12:18 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Operator.hpp"

Operator::Operator(): p_nick(""), p_ip(""), p_password("")
{}

Operator::Operator(std::string const nick, std::string const ip, std::string const password) :
p_nick(nick), p_ip(ip), p_password(password)
{}

Operator::Operator(Operator const& src) : p_nick(src.p_nick), p_ip(src.p_ip), p_password(src.p_password)
{}

Operator::~Operator()
{}

std::string const & Operator::getNick() const{
	return p_nick;
}

std::string const & Operator::getIP() const{
	return p_ip;
}

std::string const & Operator::getPW() const{
	return p_password;
}

void Operator::setUser(User *user){
	p_user = user;
}
