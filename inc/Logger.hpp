/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 10:57:05 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 14:45:02 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGGER_HPP
# define LOGGER_HPP

# include <iostream>
# include <iomanip>
# include <fstream>
# include <ctime>
# include <cstdlib>

class Logger
{
	public:
		Logger(char const * file);
		~Logger();
		void		log(std::string const str);

	private:
		Logger();
		Logger(Logger const& src);
		Logger &	operator=(Logger const& rhs);

		std::ofstream	p_outstream;

		void 			p_displayTimestamp();
};

#endif
