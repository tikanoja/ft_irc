/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:20 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/03 14:51:46 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <netinet/in.h>
# include "../inc/CircularBuffer.hpp"

class User
{
	public:
		User();
		User(const std::string password, const std::string nickname, const std::string username);
		User(User const& src);
		~User();

		User &				operator=(User const& rhs);
		char const *		getIP(void) const;
		int					getSocket(void) const;
		std::string	const &	getNick(void) const;
		int					getMode(void) const;
		std::string	const &	getRealName(void) const;
		std::string	const &	getUserName(void) const;

		void	setIP(char const * ip);
		void	setSocket(int socketfd);
		void	setNick(std::string nickname);
		void	setMode(int mode);
		void	setRealName(std::string realname);
		void	setUserName(std::string username);

		CircularBuffer &	getRecvBuffer(void);
		CircularBuffer &	getSendBuffer(void);
		void				resetBuffers(void);

	private:
		std::string		p_password;
		std::string		p_nickname;
		std::string		p_username;
		std::string		p_realname;
		int32_t			p_mode;
		int				p_socket_fd;
		char			p_ipaddress[INET6_ADDRSTRLEN];
		CircularBuffer	p_recvBuffer;
		CircularBuffer	p_sendBuffer;

};

#endif
