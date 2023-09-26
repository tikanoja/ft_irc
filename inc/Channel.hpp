/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:24:23 by tuukka            #+#    #+#             */
/*   Updated: 2023/09/26 09:23:29 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include <string>
#include <iostream>
#include <vector>
#include <string>

class User;

class Channel {
	private:
		std::string name;
		std::vector<User*> members;
		
	public:
		Channel(const std::string& name);
		~Channel(void);
};

#endif
