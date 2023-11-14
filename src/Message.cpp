/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Message.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:43:52 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/14 10:52:18 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Message.hpp"

Message::Message()
{}

Message::Message(std::string msg)
{
	size_t in = 0;
	while ((in = msg.find('\r', in)) != std::string::npos)
        msg.replace(in, 1, "");
	std::istringstream iss(msg);
	std::string token;
	int index = 0;
	p_prefix = "";
	p_command = "";
	p_params.push_back("");
	p_trailing = "";
	while (iss >> token) {
		if (index == 0 && token[0] == ':')
			p_prefix = token.substr(1);
		else if (index == 0 && token[0] != ':')
			p_command = token;
		else if (index == 1 && p_prefix != "")
			p_command = token;
		else if (index >= 1 && token[0] != ':') {
			if (p_params.size() == 1 && p_params[0] == "")
				p_params.pop_back();
			p_params.push_back(token);
		}
		else if (index >= 1 && token[0] == ':')
		{
			if ((p_command == "TOPIC" || p_command == "topic") && token.length() == 1) {
				p_trailing = ":";
				break ;
			}
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

Message::Message(Message const& src){
	*this = src; 
}

Message::~Message()
{}

Message& Message::operator=(Message const& rhs){
	
	if(this != &rhs)
	{
		p_command = rhs.p_command;
		p_sender = rhs.p_sender;
		p_recipient = rhs.p_recipient;
		p_params = rhs.p_params;
	}
	return *this;
}

std::string Message::combineParams() {
	
	std::string combinedParams;
	for (size_t i = 0; i < p_params.size(); i++) {
		combinedParams += p_params[i];
		if (i + 1 != p_params.size())
			combinedParams += " ";
	}
	return combinedParams;
}

const char* Message::toString() {
	
	std::string temp = "";
	if (p_prefix != "") {
		temp = ":";
		temp += p_prefix;
		temp += " ";
	}
	if (p_command != "") {
		temp += p_command;
		temp += " ";
	}
	if (p_params.size() > 0 && p_params[0] != "") {
		temp += combineParams();
		temp += " ";
	}
	if (p_trailing != "") {
		temp += ":";
		temp += p_trailing;
	}
	temp += "\r\n";
	size_t len = temp.length();
	char* str = new char[len + 1];
	str[len] = '\0';
	
	for (size_t i = 0; i < temp.length(); i++) {
		str[i] = temp[i];
	}
	return str;
}

std::string const &	Message::getPrefix() const{

	return p_prefix;
}

std::vector<std::string> const &	Message::getParams() const {

	return p_params;
}

std::string const &	Message::getTrailing() const {

	return p_trailing;
}

User const *	Message::getSender() const {
	
	return p_sender;
}

User const *	Message::getRecipient() const {

	return p_recipient;
}

std::string const &	Message::getCommand() const {
	
	return p_command;
}
