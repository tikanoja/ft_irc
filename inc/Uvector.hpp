/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uvector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 08:53:33 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 16:13:34 by djagusch         ###   ########.fr       */
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
		User*		findUserBySocket(int const socket_fd) const;
		User*		findUserByNick(std::string const & nick) const;

	private:
		class UserNotFound : public std::exception{
			char const * what() const throw();
		};
};

#endif
