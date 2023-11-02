/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:32:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/11/01 11:05:48 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULARBUFFER_HPP
# define CIRCULARBUFFER_HPP

# include <typeinfo>
# include <iostream>
# include <string>
# include <cstdlib>
# include <exception>

# ifndef MAXDATASIZE
	# define MAXDATASIZE 2048
# endif

class CircularBuffer {
	public:
		CircularBuffer();
		~CircularBuffer();
		CircularBuffer(CircularBuffer const & src);
		CircularBuffer &	operator=( CircularBuffer const & rhs );

		void			addToBuffer(const char* buf);
		void			addToBuffer(const char* buf, ssize_t numbytes);
		int				findCRLF() const; // -1 not found, on success returns index of \n
		std::string		extractBuffer();
		int				emptyCheck();
		void			printbuf();
		void			clear();
		
		unsigned char*	p_buffer;

	private:
		int p_head;
		int p_tail;
	
};

#endif
