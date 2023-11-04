/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cvector.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:57:09 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/04 10:57:56 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CVECTOR_HPP
# define CVECTOR_HPP

# include <iostream>
# include <vector>
# include <typeinfo>
# include "Channel.hpp"

class Cvector : public std::vector<Channel*>
{
	public:
		Cvector();
		Cvector(Cvector const& src);
		~Cvector();
		Cvector &	operator=(Cvector const & rhs);

		Channel*	findChannel(std::string const & name) const;
		Channel*	createChannel(std::string const & name);
		void		deleteChannel(Channel* toDelete);
		Cvector		findChannelsByUser(std::string const & name) const;

	private:
		std::string toIRCLower(std::string const & str) const;
};

#endif
