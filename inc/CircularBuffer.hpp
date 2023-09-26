

#ifndef CIRCULARBUFFER_HPP
# define CIRCULARBUFFER_HPP

# include "IRCServer.hpp"
# include <exception>

class CircularBuffer {
	public:
		CircularBuffer();
		~CircularBuffer();
		CircularBuffer(CircularBuffer const & src);

		void addToBuffer(char* buf, ssize_t numbytes);
		int findCRLF() const; // -1 not found, on success returns index of \n
		unsigned char* getBuffer() const;
		unsigned char* buffer;

	private:
		CircularBuffer &	operator=( CircularBuffer const & rhs );
		int head;
		int tail;
		size_t fill;
};

#endif
