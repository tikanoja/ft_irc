/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChannelBatchMode.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:56:03 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 16:05:36 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Channel.hpp"

std::string	Channel::setBatchMode(std::vector<std::string> const & modes, size_t & word,
	size_t & character, std::vector<size_t> & indeces){

	std::string					opsdone = "";
	static const std::string	characters = "itkol";
	size_t						move_flag = 0;

	if (modes.at(word)[character] == '+')
	{
		for (; character < modes.at(word).size(); character++ ){
			switch (modes.at(word)[character]){
				case ('i'):
					if (this->setMode(invite))
						opsdone += characters[0];
					break;
				case ('t'):
					if (this->setMode(topic_rest))
						opsdone += characters[1];
					break;
				case ('k'):
					if (word + ++move_flag < modes.size()){
							this->setMode(key);
							this->setKey(modes.at((word + move_flag)));
							indeces.push_back(word + move_flag);
							opsdone += characters[2];
					}
					break;
				case ('o'):
					if (word + ++move_flag < modes.size()){
							std::cout << modes.at(word + move_flag) << std::endl;
						if (this->setChop(modes.at(word + move_flag))){
							indeces.push_back(word + move_flag);
							opsdone += characters[3];
						}
					}
					break;
				case ('l'):
					if (word + ++move_flag < modes.size()){
							this->setMode(limit);
							indeces.push_back(word + move_flag);
							opsdone += characters[4];
					}
					break;
				case ('-'):
					opsdone += "-" + unsetBatchMode(modes, word, character, indeces);
					return opsdone;
				default:
					continue;
			}
		}
	}
	word += move_flag;
	return opsdone;
}

std::string	Channel::unsetBatchMode(std::vector<std::string> const & modes, size_t & word,
	size_t & character, std::vector<size_t> & indeces){

	std::string					opsdone = "";
	static const std::string	characters = "itkol";
	size_t						move_flag = 1;

	if (modes.at(word)[character] == '-')
	{
		for (; character < modes.at(word).size(); character++ ){
			switch (modes.at(word)[character]){
				case ('i'):
					if (this->setMode(invite))
						opsdone += characters[0];
					break;
				case ('t'):
					if (this->setMode(topic_rest))
						opsdone += characters[1];
					break;
				case ('k'):
					if (this->unsetMode(key)){
						opsdone += characters[2];
					}
					break;
				case ('o'):
					if (word + ++move_flag < modes.size()){
						std::cout << modes.at(word + move_flag) << std::endl;
						if (this->unsetChop(modes.at(word + move_flag))){
							opsdone += characters[3];
							indeces.push_back(word + move_flag);
						}
					}
					break;
				case ('l'):
					if (this->unsetMode(limit)){
							opsdone += characters[4];
					}
					break;
				case ('+'):
					opsdone += "+" + setBatchMode(modes, word, character, indeces);
					return opsdone;
				default:
					continue;
			}
		}
	}
	word += move_flag - 1;
	return opsdone;
}
