/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:03:46 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/07 11:19:06 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Operator.hpp"


Operator::Operator(): p_nick(""), p_ip(""), p_password("")
{}

Operator::Operator(std::string const nick, std::string const ip,
			std::string const password) : p_nick(nick), p_password(password){
	
	p_ip = convertToIPv6(ip);
}

Operator::Operator(Operator const& src) : p_nick(src.p_nick), p_ip(src.p_ip),
	p_password(src.p_password){
}

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

std::string Operator::convertToIPv6(std::string const& configAddress){
	
	struct in6_addr ipv6Address;

	// Try to convert the IP address to an IPv6 format.
	if (inet_pton(AF_INET6, configAddress.c_str(), &ipv6Address) > 0)
	{
		char buffer[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &ipv6Address, buffer, INET6_ADDRSTRLEN);
		return std::string(buffer);
	}

	// If conversion to IPv6 fails, consider it an IPv4 address and convert it to IPv6-mapped.
	struct in_addr ipv4Address;
	if (inet_pton(AF_INET, configAddress.c_str(), &ipv4Address) <= 0)
	{
		std::cerr << "Error converting IP address." << std::endl;
		// Handle the error appropriately.
	}
	else
	{
		in6_addr ipv6MappedAddress;
		std::memset(&ipv6MappedAddress, 0, sizeof(ipv6MappedAddress));
		ipv6MappedAddress.s6_addr[10] = 0xff;
		ipv6MappedAddress.s6_addr[11] = 0xff;
		std::memcpy(&ipv6MappedAddress.s6_addr[12], &ipv4Address.s_addr, 4);

		char buffer[INET6_ADDRSTRLEN];
		inet_ntop(AF_INET6, &ipv6MappedAddress, buffer, INET6_ADDRSTRLEN);
		return std::string(buffer);
	}
	
	// If both conversions fail, return an error string.
	return "Invalid IP Address";
}
