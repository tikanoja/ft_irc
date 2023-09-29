/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/27 12:39:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>

class Channel
{
	public:
		Channel();
		Channel(Channel const& src);
		~Channel();

		Channel &	operator=(Channel const& rhs);

	private:

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
		p_ATTRIBUTE = rhs.p_ATTRIBUTE;
	return *this;
}

#endif