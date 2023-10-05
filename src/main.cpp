/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:45:35 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/05 09:40:00 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

int main(int ac, char** av) {
	if (ac != 3) {
		std::cerr << "usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}
	
	int portInt = 0;
	std::istringstream(av[1]) >> portInt;
	if (portInt <= 0 || portInt > 65535) {
		std::cerr << "bad port number: " << av[1] << std::endl;
		return (1);
	}
	uint16_t port = static_cast<uint16_t>(portInt);
	std::string password(av[2]);

	try {
		IRCServer server(port);
		if (server.pollingRoutine())
			throw std::runtime_error("Polling failed");
	} catch (std::exception& e) {
		std::cerr << "Server quit: " << e.what() << std::endl;
	}
	return (0);
}
