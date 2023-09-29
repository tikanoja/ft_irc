/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:20 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/29 11:46:32 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

# include <iostream>
# include <string>
# include <netinet/in.h>

class User
{
	public:
		User();
		User(const std::string password, const std::string nickname, const std::string username);
		User(User const& src);
		~User();

		User &	operator=(User const& rhs);
		void	setIP(char const * ip);
		void	setSocket(int socketfd);
		char*	getIP(void);
		int		getSocket(void);

	private:
		std::string	p_password;
		std::string	p_nickname;
		std::string	p_username;
		std::string	p_realname;
		int8_t		p_mode;
		int			p_socket_fd;
		char		p_ipaddress[INET6_ADDRSTRLEN];

};

#endif
