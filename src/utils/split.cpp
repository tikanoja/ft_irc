/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:23:55 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/19 17:52:08 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Utils.hpp"
#include <iostream>

std::vector<std::string> split(const std::string& str, char c){

	std::vector<std::string>	tokens;
	std::istringstream			stream(str);
	std::string					token;
	size_t						i = 0;
	
	for (; i < 3 && std::getline(stream, token, c); i++)
		tokens[i] = token;
	std::cout << token << std::endl;
	return (tokens);
}
