/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uvector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:53:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/03 13:18:36 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UVECTOR_HPP
# define UVECTOR_HPP

# include <iostream>
# include <vector>
# include <typeinfo>
# include <poll.h>
# include "User.hpp"

class Uvector : public std::vector<User*>
{
	public:
		Uvector();
		Uvector(Uvector const& src);
		~Uvector();

		Uvector &	operator=(Uvector const & rhs);
		User*		findUserBySocket(int const socket_fd);
		User*		findUserByNick(std::string const & nick);

	private:
		class UserNotFound : public std::exception{
			char const * what() const throw();
		};
};

#endif
