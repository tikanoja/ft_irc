/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:35:31 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/02 10:07:35 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICBUFFER_HPP
# define DYNAMICBUFFER_HPP

# include <typeinfo>
# include <iostream>
# include <string>
# include <cstdlib>
# include <vector>

# ifndef MAXDATASIZE
	# define MAXDATASIZE 2048
# endif

class DynamicBuffer {
	public:
		DynamicBuffer();
		~DynamicBuffer();

		void			addToBuffer(const char* buf);
		void			addToBuffer(const char* buf, ssize_t numbytes);
		int				findCRLF() const; // -1 not found, on success returns index of \n
		std::string		extractBuffer();
		void			replaceUnsent(std::string message);
		int				emptyCheck();
		void			printbuf() const;
		void			clear();
		
		std::vector<std::string> p_buf;
};

#endif
