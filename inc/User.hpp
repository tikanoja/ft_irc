/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:20 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/27 11:35:19 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef USER_HPP
# define USER_HPP

# include <iostream>

class User
{
	public:
		User(const std::string password, const std::string nickname, const std::string username);
		User(User const& src);
		~User();

		User &	operator=(User const& rhs);

	private:
		User();
		std::string	p_password;
		std::string	p_nickname;
		std::string	p_username;
		std::string	p_realname;
		int8_t		p_mode;
		

};

#endif