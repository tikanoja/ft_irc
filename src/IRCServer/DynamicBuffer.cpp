/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicBuffer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:38:17 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/06 16:12:42 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/DynamicBuffer.hpp"
#include "../inc/Utils.hpp"

DynamicBuffer::DynamicBuffer() {
}

DynamicBuffer::~DynamicBuffer() {
}

int DynamicBuffer::emptyCheck() {
	if (p_buf.size() == 0 || findCRLF() == -1)
		return 0;
	return 1;
}

int DynamicBuffer::findCRLF() const {
	if (p_buf.size() == 0)
		return -1;

	std::string message = p_buf.front();
	if (message.find("\n") != std::string::npos)
		return 0;
	else if (message.find("\r") != std::string::npos)
		return 0;

	return -1;
}

void DynamicBuffer::clear() {
	p_buf.clear();
}

std::vector<std::string> nlsplit(const std::string& str, char c){

	std::vector<std::string>	tokens;
	std::istringstream			stream(str);
	std::string					token;

	while (std::getline(stream, token, c)) {
		tokens.push_back(token);
		if (!stream.eof())
			tokens.back() += c;
	}
	return (tokens);
}

void DynamicBuffer::addToBuffer(const char* buf) {
	std::string toAdd = buf;
	size_t index = 0;
	while ((index = toAdd.find("^D", index)) != std::string::npos)
		toAdd.replace(index, 2, "");

	std::vector<std::string> toAddVec = nlsplit(toAdd, '\n');
	for (size_t j = 0; j < toAddVec.size(); j++) {
		toAdd = toAddVec[j];
		bool appended = false;
		for (size_t i = 0; i < p_buf.size(); ++i) {
			if (p_buf[i].find("\n") == std::string::npos) {
				p_buf[i] += toAdd;
				appended = true;
				break;
			}
		}
		if (appended == false)
			p_buf.push_back(toAdd);
	}
}

std::string DynamicBuffer::extractBuffer() {
	std::string bufferString;
	bufferString = p_buf.front();
	p_buf.erase(p_buf.begin());
	return (bufferString);
}

void DynamicBuffer::replaceUnsent(std::string message) {
	p_buf.insert(p_buf.begin(), message);
	return ;
}
