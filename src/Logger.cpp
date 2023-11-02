/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 11:14:29 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/02 09:20:40 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Logger.hpp"

Logger::Logger(){}

Logger::Logger(char const * file){

	p_outstream.open(file, std::fstream::out);
	if (!p_outstream.is_open() || !p_outstream.good()){
		std::cerr << "Error initialising Logger" << std::endl;
		exit(2);
	}
		p_outstream << "Loging start: ";
		p_displayTimestamp();
}

Logger::Logger(Logger const& src){

	*this = src;
}

Logger::~Logger(){
	p_outstream << "_________________________________________________" << std::endl;
	p_outstream.close();
}

Logger& Logger::operator=(Logger const& rhs){
	if(this != &rhs)
		;
	return *this;
}

void Logger::p_displayTimestamp(){
	
	std::time_t p_cur_time = std::time(0);
	std::tm* now = std::localtime(&p_cur_time);

	p_outstream << std::setfill('0') << "[" << 1900 + now->tm_year
				<< std::setw(2) << 1 + now->tm_mon
				<<  std::setw(2) << now->tm_mday
				<<  "_"
				<<  std::setw(2) << now->tm_hour
				<<  std::setw(2) << now->tm_min
				<<  std::setw(2) << now->tm_sec
				<< "] " << std::flush;

}

void	Logger::log(std::string const str, std::string file, int line){
	
	p_displayTimestamp();
	p_outstream << str << "\t" << file << " " << line << "\n";
}
