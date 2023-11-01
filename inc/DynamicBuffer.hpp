/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DynamicBuffer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:35:31 by tuukka            #+#    #+#             */
/*   Updated: 2023/11/01 16:57:45 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYNAMICBUFFER_HPP
# define DYNAMICBUFFER_HPP

# include <typeinfo>
# include <iostream>
# include <string>
# include <cstdlib>

# ifndef MAXDATASIZE
	# define MAXDATASIZE 512
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
