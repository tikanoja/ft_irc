/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 22:45:35 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/03 16:45:59 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/IRCServer.hpp"

int main(int ac, char** av) {

	try {
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

		IRCServer server(port, password);
		if (server.pollingRoutine())
			throw std::runtime_error("Polling failed");
	}
	catch (std::exception& e) {
		std::cerr << "Server quit: " << e.what() << std::endl;
	}
	catch (std::bad_alloc& e) {
		std::cerr << "Server quit: " << e.what() << std::endl;
	}
	return (0);
}
