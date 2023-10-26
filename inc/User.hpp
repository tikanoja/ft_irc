/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:20 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/26 14:48:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <netinet/in.h>
# include "../inc/CircularBuffer.hpp"

class IRCServer;

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
		int					getMode(void) const;
		std::string	const &	getNick(void) const;
		std::string	const &	getOldNick(void) const;
		std::string	const &	getRealName(void) const;
		std::string	const &	getUserName(void) const;
		std::string	const &	getAwayMsg(void) const;

		void	setIP(char const * ip);
		void	setSocket(int socketfd);
		bool	setMode(int mode);
		void	setNick(std::string nickname);
		void	setOldNick(std::string nickname);
		bool	unsetMode(int mode);
		void	setRealName(std::string realname);
		void	setUserName(std::string username);
		void	setAwayMsg(std::string const & comment);
		void 	send(std::string str);

		void	setRegistrationFlag(int i, User& user, IRCServer& server);

		CircularBuffer &	getRecvBuffer(void);
		CircularBuffer &	getSendBuffer(void);
		void				resetBuffers(void);

	private:
		std::string		p_nickname;
		std::string		p_oldNick;
		std::string		p_username;
		std::string		p_realname;
		std::string		p_awaymsg;
		int32_t			p_mode;
		int				p_socket_fd;
		char			p_ipaddress[INET6_ADDRSTRLEN];
		CircularBuffer	p_recvBuffer;
		CircularBuffer	p_sendBuffer;

		bool			nickFlag;
		bool			userFlag;
		bool			passFlag;
		bool			welcomeFlag;
};

std::ostream & operator<<( std::ostream & o, User const & user);

#endif
