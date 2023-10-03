/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:43:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/03 09:31:45 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Message.hpp"

Message::Message()
{}

Message::Message(std::string msg)
{
	std::istringstream iss(msg);
	std::string token;
	int index = 0;
	
	/*
	** this loop expects the input to be in format:
	** :irc.example.com PRIVMSG #channel other param :Hello, everyone!
	** ^prefix          ^cmd    ^param[0] ^p[1] ^p[2] ^trailing
	** cmd not optional!
	*/
	while (iss >> token) {
		if (index == 0 && token[0] == ':')
			p_prefix = token.substr(1);
		else if (index == 0 && token[0] != ':')
		{
			p_prefix = "";
			p_command = token;
		}
		else if (index == 1 && p_prefix != "")
			p_command = token;
		else if (index >= 1 && token[0] != ':')
			p_params.push_back(token);
		else if (index >= 1 && token[0] == ':')
		{
			p_trailing = token.substr(1);
			std::string temp;
			std::getline(iss, temp, '\n');
			p_trailing += temp;
			break ;
		}
		index++;
	}
	return ;
}

void Message::printContent()
{
	std::cout << "$ directly after param to spot whitespace/nondisp" << std::endl;
	std::cout << "Prefix: " << this->p_prefix << "$" << std::endl;
	std::cout << "Command: " << this->p_command << "$" << std::endl;
	for (unsigned long i = 0; i < p_params.size(); i++)
		std::cout << "Params[" << i << "]: " << p_params[i] << "$" << std::endl;
	std::cout << "Trailing: " << this->p_trailing << "$" << std::endl;
}

Message::Message(Message const& src)
{
	*this = src; 
}

Message::~Message()
{}

Message& Message::operator=(Message const& rhs)
{
	if(this != &rhs)
	{
		p_command = rhs.p_command;
		p_sender = rhs.p_sender;
		p_recipient = rhs.p_recipient;
		p_params = rhs.p_params;
	}
	return *this;
}
