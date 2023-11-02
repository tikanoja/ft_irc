/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:17:44 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 16:02:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

bool isValidWildchard(const std::string& pattern){
	
	if ((pattern.find_last_of('.') < pattern.find_last_of('*') 
			&& pattern.find_last_of('*') != std::string::npos)
		|| (pattern.find_last_of('.') < pattern.find_last_of('?')
			&& pattern.find_last_of('?') != std::string::npos))
		return false;
	return true;
}

bool matchWildcard(const std::string& pattern, const std::string& str) {

	size_t i = 0;
	size_t j = 0;

	while (i < pattern.size() && j < str.size()) {
		if (pattern[i] == str[j] || pattern[i] == '?') {
			i++;
			j++;
		} else if (pattern[i] == '*') {
			while (i < pattern.size() && pattern[i] == '*') {
				i++;
			}
			if (i == pattern.size()) {
				return true;
			}
			while (j < str.size() && str[j] != pattern[i] && pattern[i] != '?') {
				j++;
			}
		} else {
			return false;
		}
	}

	while (i < pattern.size() && pattern[i] == '*') {
		i++;
	}

	return i == pattern.size() && j == str.size();
}
