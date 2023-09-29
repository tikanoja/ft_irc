/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:40:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/09/28 13:41:28 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_HPP
# define MESSAGE_HPP

# include <iostream>
# include <string>
# include <vector>
# include <sstream>
# include "User.hpp"

class User;

class Message
{
	public:
		Message();
		Message(std::string msg);
		Message(Message const& src);
		~Message();
		Message &	operator=(Message const& rhs);

		void printContent();

	private:
		std::string 				p_prefix;
		std::string					p_command;
		std::vector<std::string>	p_params;
		std::string					p_trailing;
		User*						p_sender; //changed & to * to compile
		User*						p_recipient; //changed & to * to compile
};

#endif
