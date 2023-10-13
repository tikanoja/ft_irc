/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:20 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/13 09:52:15 by djagusch         ###   ########.fr       */
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
		User(int const socket_fd, char const * ipaddress );
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
		bool	setMode(int mode);
		bool	unsetMode(int mode);
		void	setRealName(std::string realname);
		void	setUserName(std::string username);

		CircularBuffer &	getRecvBuffer(void);
		CircularBuffer &	getSendBuffer(void);
		void				resetBuffers(void);

	private:
		std::string		p_nickname;
		std::string		p_username;
		std::string		p_realname;
		int32_t			p_mode;
		int				p_socket_fd;
		char			p_ipaddress[INET6_ADDRSTRLEN];
		CircularBuffer	p_recvBuffer;
		CircularBuffer	p_sendBuffer;

};

std::ostream & operator<<( std::ostream & o, User const & user);

#endif
