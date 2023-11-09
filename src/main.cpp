/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:45:35 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/09 08:30:33 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

int main(int ac, char** av) {

	try {
		if (ac != 3) {
			std::cerr << "usage: " << av[0] << " <port> <password>" << std::endl;
			return (1);
		}
		if (std::strncmp(av[2], "", 1) == 0) {
			std::cerr << "Error: Pawsword must not be an empty string" << std::endl;
			return (1);
		}
		if (std::string(av[2]).find_first_of(" \t\n\r\f\v") != std::string::npos) {
			std::cerr << "Error: Pawsword must not contain whitespaces" << std::endl;
			return (1);
		}
		int portInt = 0;
		std::istringstream(av[1]) >> portInt;
		if (portInt <= 0 || portInt > 65535) {
			std::cerr << "Error: bad port number: " << av[1] << std::endl;
			return (1);
		}
		uint16_t port = static_cast<uint16_t>(portInt);
		std::string password(av[2]);

		IRCServer server(port, password);
		if (server.pollingRoutine())
			throw std::runtime_error("Polling failed");
	}
	catch (std::exception& e) {
		std::cerr << "Server quit: " << e.what() << std::endl;
		exit (1);
	}
	return (0);
}
