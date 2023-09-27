/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:40:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/27 11:49:57 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <string>
# include "User.hpp"

class Message
{
	public:
		Message();
		Message(Message const& src);
		~Message();

		Message &	operator=(Message const& rhs);

	private:
		std::string		p_command;
		User&			p_sender;
		User&			p_recipient;
		std::string[15] p_params;
};

#endif