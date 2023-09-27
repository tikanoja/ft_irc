#include "../inc/CircularBuffer.hpp"

CircularBuffer::CircularBuffer() : head(0), tail(0), fill(0) {
	try {
 		buffer = new unsigned char[MAXDATASIZE * 2];
	} catch (std::exception & e){
		std::cerr << e.what() << std::endl;
	}
	memset(buffer, 0, MAXDATASIZE * 2);
}

CircularBuffer::CircularBuffer( CircularBuffer const & src ) {
	*this = src; 
}

CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}

CircularBuffer&	CircularBuffer::operator=( CircularBuffer const & rhs ) {
	if( this != &rhs ) {
		head = rhs.head;
		tail = rhs.tail;
		fill = rhs.fill;
		if (buffer)
			delete [] buffer;
		buffer = new unsigned char[2 * MAXDATASIZE];
		for (int i = 0; rhs.buffer[i]; i++) {
			this->buffer[i] = rhs.buffer[i];
		}
	}
	return (*this);
}

void CircularBuffer::addToBuffer(char* buf, ssize_t numbytes) {
	for (ssize_t i = 0; i < numbytes; i++) {
		this->buffer[head] = static_cast<unsigned char> (buf[i]);
		head++;
		if (head == MAXDATASIZE * 2)
			head = 0;
	}
}

int CircularBuffer::findCRLF() const {
	for (int i = 0; buffer[i + 1]; i++) {
		if (buffer[i] == '\r' && buffer[i + 1] == '\n')
			return (i);
	}
	return (-1);
}

unsigned char* CircularBuffer::getBuffer() const {
	return (this->buffer);
}
