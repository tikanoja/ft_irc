/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:43:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/27 11:44:05 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Message.hpp"

Message::Message()
{}

Message::Message(Message const& src)
{
	*this = src; 
}

Message::~Message()
{}

Message& Message::operator=(Message const& rhs)
{
	if(this != &rhs)
		p_ATTRIBUTE = rhs.p_ATTRIBUTE;
	return *this;
}
