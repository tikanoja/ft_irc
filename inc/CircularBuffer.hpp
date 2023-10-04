/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CircularBuffer.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 09:32:47 by djagusch          #+#    #+#             */
/*   Updated: 2023/10/04 07:36:38 by djagusch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CIRCULARBUFFER_HPP
# define CIRCULARBUFFER_HPP

# include "IRCServer.hpp"
# include <exception>

# define MAXDATASIZE 512

class CircularBuffer {
	public:
		CircularBuffer();
		~CircularBuffer();
		CircularBuffer(CircularBuffer const & src);
		CircularBuffer &	operator=( CircularBuffer const & rhs );

		void			addToBuffer(char* buf, ssize_t numbytes);
		int				findCRLF() const; // -1 not found, on success returns index of \n
		std::string		extractBuffer();
		unsigned char*	buffer;

		void			clear();

	private:
		int p_head;
		int p_tail;
};

#endif
