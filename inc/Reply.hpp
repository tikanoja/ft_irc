/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reply.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:38:18 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/27 11:45:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPLY_HPP
# define REPLY_HPP

# include <iostream>
# include <map>
# include "Message.hpp"

class Reply
{
	public:
		Reply();
		Reply(Reply const& src);
		~Reply();

		Reply &	operator=(Reply const& rhs);

	private:
		std::map<std::string, Message>replies;

};

#endif