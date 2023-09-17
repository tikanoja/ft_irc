/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRCServer.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:12:09 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/17 23:52:15 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCSERVER_HPP
# define IRCSERVER_HPP

#include <vector>
#include <iostream>
#include <cstdint>

class User;
class Channel;

class IRCServer {
	private:
		uint16_t port;
		std::vector<User*> users;
		std::vector<Channel*> channels;
		
	public:
		IRCServer(uint16_t port);
		~IRCServer(void);
};

#endif
