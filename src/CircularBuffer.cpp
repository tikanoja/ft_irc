#include "../inc/CircularBuffer.hpp"

CircularBuffer::CircularBuffer() : p_head(0), p_tail(0) {
	p_buffer = new unsigned char[MAXDATASIZE * 2];
	memset(p_buffer, '\0', MAXDATASIZE * 2);
}

CircularBuffer::CircularBuffer( CircularBuffer const & src ) {
	p_buffer = NULL;
	*this = src;
}

CircularBuffer::~CircularBuffer() {
	delete[] p_buffer;
}

CircularBuffer&	CircularBuffer::operator=( CircularBuffer const & rhs ) {
	if( this != &rhs ) {
		p_head = rhs.p_head;
		p_tail = rhs.p_tail;
		if (p_buffer != NULL)
			delete [] p_buffer;
		p_buffer = new unsigned char[2 * MAXDATASIZE];
		memset(p_buffer, 0, MAXDATASIZE * 2);
		for (int i = 0; rhs.p_buffer[i]; i++) {
			p_buffer[i] = rhs.p_buffer[i];
		}
	}
	return (*this);
}

int CircularBuffer::emptyCheck() {
	//empty or full check for null heh rhymes!
	if (p_tail == p_head)
		return 0;
	return 1;
}

void CircularBuffer::addToBuffer(const char* buf, ssize_t numbytes) {
	for (ssize_t i = 0; i < numbytes; i++) {
		p_buffer[p_head] = static_cast<unsigned char> (buf[i]);
		p_head++;
		if (p_head == MAXDATASIZE * 2 - 1)
			p_head = 0;
	}
}

void CircularBuffer::addToBuffer(const char* buf) {
	size_t len = strlen(buf);
	for (size_t i = 0; i <  len; i++) {
		p_buffer[p_head] = static_cast<unsigned char> (buf[i]);
		p_head++;
		if (p_head == MAXDATASIZE * 2 - 1)
			p_head = 0;
	}
}

int CircularBuffer::findCRLF() const {
	for (int i = p_tail; p_buffer[i] != '\0'; i++) {
		if (p_buffer[i] == '\r' || p_buffer[i] == '\n')// || (p_buffer[i] == '\r' && p_buffer[i + 1] == '\n'))
			return (i);
	}
	return (-1);
}

std::string CircularBuffer::extractBuffer() {
	std::string bufferString;
	while (p_tail != p_head) { //calculating len of the buffered msg
		if (p_tail == MAXDATASIZE * 2 - 1)
			p_tail = 0;
		bufferString.push_back(static_cast<char>(p_buffer[p_tail]));
		if (p_buffer[p_tail] == '\n') {
			p_buffer[p_tail] = '\0';
			p_tail++;
			break ;
		}
		p_buffer[p_tail] = '\0';
		p_tail++;
	}

	size_t index = 0;
    while ((index = bufferString.find("^D", index)) != std::string::npos) // find "^D"
        bufferString.replace(index, 2, ""); //replace "^D" with ""

	return (bufferString);
}


void CircularBuffer::clear(){
	memset(this, 0, MAXDATASIZE);
	p_head = 0;
	p_tail = 0;
}

void CircularBuffer::printbuf() {
	std::cout << "Tail is at: " << p_tail << ", Head is at: " << p_head << std::endl;
	std::cout << "In buffer: ";
	for (int i = p_tail; i != p_head; i++) {
		if (i == MAXDATASIZE * 2 - 1) {
			i = 0;
		}
		std::cout << p_buffer[i];
	}
	std::cout << std::endl;
	return ;
}
