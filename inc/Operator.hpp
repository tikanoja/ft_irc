/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:21:34 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/20 11:52:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATOR_HPP
# define OPERATOR_HPP

# include <string>
# include "User.hpp"

class Operator
{
	public:
		Operator();
		Operator(std::string const nick, std::string const ip, std::string const password);
		Operator(Operator const& src);
		~Operator();

		std::string const & getNick() const;
		std::string const & getIP() const;
		std::string const & getPW() const;
		void				setUser(User *user);

		typedef std::string const & (Operator::*OperFunct)() const;

	private:
		std::string const p_nick;
		std::string const p_ip;
		std::string const p_password;
		User*			p_user;
};

#endif
