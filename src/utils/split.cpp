/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/17 15:49:55 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Utils.hpp"

std::vector<std::string> split(const std::string& str, char c){

	std::vector<std::string>	tokens;
	std::istringstream			stream(str);
	std::string					token;
	size_t						i = 0;
	
	while (!stream.eof())
	{
		std::getline(stream, token, c);
		tokens[i] = token;
	}
	return (tokens);
}
