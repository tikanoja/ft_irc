/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printOut.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 11:33:49 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/11/01 16:02:29 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Utils.hpp"
#include <iostream>

void printOut(int i, std::string msg) {

	if (i == 3) {
		std::cerr << "\033[31m[ERROR]\033[0m" << std::endl;
		std::cerr << msg << std::endl << std::endl;
		return ;
	}
	if (i == 1)
		std::cout << "\033[32m[Server]\033[0m" << std::endl;
	else if (i == 2)
		std::cout << "\033[34m[Client]\033[0m" << std::endl;
	std::cout << msg << std::endl << std::endl;
}
