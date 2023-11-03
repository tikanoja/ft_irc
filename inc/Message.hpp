/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:40:09 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/03 16:33:13 by ttikanoj         ###   ########.fr       */
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

		std::string const &					getPrefix() const;
		std::vector<std::string> const &	getParams() const;
		std::string const &					getTrailing() const;
		User const *						getSender() const;
		User const *						getRecipient() const;
		std::string const &					getCommand() const;

		std::string							combineParams();
		const char*							toString();
		
		User*						p_recipient;	//changed & to * to compile // MOVE BACK TO PRIVATE! NEEDED FOR TESTING IN PUBLIC
		User*						p_sender;		//changed & to * to compile //MOVE BACK TO PRIVATE! NEEDED FOR TESTING IN PUBLIC
		
	private:
		std::string					p_command;
		std::string 				p_prefix;
		std::vector<std::string>	p_params;
		std::string					p_trailing;

};

#endif
