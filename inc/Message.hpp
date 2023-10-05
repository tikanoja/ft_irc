/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:40:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/05 09:55:01 by djagusch         ###   ########.fr       */
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
		std::string getPrefix();
		std::string getCommand();
		std::string getParams();
		std::string getTrailing();
		const char* toString();

	private:
		std::string					p_command;
		std::string 				p_prefix;
		std::string					p_command;
		std::vector<std::string>	p_params;
		std::string					p_trailing;
		User*						p_sender;		//changed & to * to compile
		User*						p_recipient;	//changed & to * to compile
};

#endif
