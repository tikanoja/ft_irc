/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uvector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:53:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/11 09:40:05 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVECTOR_HPP
# define UVECTOR_HPP

# include <iostream>
# include <vector>
# include <typeinfo>
# include "User.hpp"

class Uvector : public std::vector<User*>
{
	public:
		Uvector();
		Uvector(Uvector const& src);
		~Uvector();

		Uvector &	operator=(Uvector const & rhs);
		std::string toIRCLower(std::string const & str) const;
		User*		findUserBySocket(int const socket_fd) const;
		User*		findUserByNick(std::string const & nick) const;
		User*		findUserByIP(std::string const & ip_address) const;

	private:
		class UserNotFound : public std::exception{
			char const * what() const throw();
		};
};

#endif
