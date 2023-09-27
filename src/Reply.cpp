/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:44:14 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/27 11:50:15 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reply.hpp"

Reply::Reply()
{}

Reply::Reply(Reply const& src)
{
	*this = src;
}

Reply::~Reply()
{}

Reply& Reply::operator=(Reply const& rhs)
{
	if(this != &rhs)
		p_ATTRIBUTE = rhs.p_ATTRIBUTE;
	return *this;
}