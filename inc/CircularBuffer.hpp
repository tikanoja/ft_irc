/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:32:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 15:59:34 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULARBUFFER_HPP
# define CIRCULARBUFFER_HPP

# include <typeinfo>
# include <iostream>
# include <string>
# include <exception>

# define MAXDATASIZE 512

class CircularBuffer {
	public:
		CircularBuffer();
		~CircularBuffer();
		CircularBuffer(CircularBuffer const & src);
		CircularBuffer &	operator=( CircularBuffer const & rhs );

		void			addToBuffer(const char* buf, ssize_t numbytes);
		int				findCRLF() const; // -1 not found, on success returns index of \n
		std::string		extractBuffer();
		int				emptyCheck();
		unsigned char*	buffer;
		void printbuf();

		void			free();

	private:
		int p_head;
		int p_tail;
	
};

#endif
