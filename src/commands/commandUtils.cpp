/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 07:08:15 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/16 07:46:54 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Commands.hpp"

void removeCommonCharacters(std::string& str1, std::string& str2){

	for (size_t i = 0; i < str1.length(); ) {
		size_t found = str2.find(str1[i]);
		if (found != std::string::npos) {
			str1.erase(i, 1);
			str2.erase(found, 1);
		} else {
			i++;
		}
	}
}
