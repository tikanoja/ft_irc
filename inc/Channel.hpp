/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/10/04 11:01:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

class Channel
{
	public:
		Channel::Channel(const std::string name);
		Channel(Channel const& src);
		~Channel();

		Channel &	operator=(Channel const& rhs);

	private:
		Channel();
		std::string	p_name;
};

Channel::Channel()
{}

Channel::Channel(Channel const& src)
{
	*this = src;
}

Channel::~Channel()
{}

Channel& Channel::operator=(Channel const& rhs)
{
	if(this != &rhs)
		p_name = rhs.p_name;
	return *this;
}

#endif