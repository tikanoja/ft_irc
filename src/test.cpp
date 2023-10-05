/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 07:32:30 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/05 07:47:28 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

std::string toIRCLower(std::string str){
	
	std::string result;
	
	for (size_t i = 0; i < str.size(); i++)
		result += (str[i] >= 'A' && str[i] <= '^' ? str[i] + 32 : str[i]);
	return (result);
}

int main(){
	std::string str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ()*\"\'/[]{}\\|^~";
	
	printf("%s", toIRCLower(str).c_str());

}