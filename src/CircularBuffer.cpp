#include "../inc/CircularBuffer.hpp"

CircularBuffer::CircularBuffer() : p_head(0), p_tail(0) {
	try {
 		buffer = new unsigned char[MAXDATASIZE * 2];
	} catch (std::exception & e){
		std::cerr << e.what() << std::endl;
	}
	memset(buffer, 0, MAXDATASIZE * 2);
}

CircularBuffer::CircularBuffer( CircularBuffer const & src ) {
	this->buffer = NULL;
	*this = src; 
}

CircularBuffer::~CircularBuffer() {
	delete[] buffer;
}

CircularBuffer&	CircularBuffer::operator=( CircularBuffer const & rhs ) {
	if( this != &rhs ) {
		p_head = rhs.p_head;
		p_tail = rhs.p_tail;
		if (this->buffer)
			delete [] buffer;
		this->buffer = new unsigned char[2 * MAXDATASIZE];
		memset(this->buffer, 0, MAXDATASIZE * 2);
		for (int i = 0; rhs.buffer[i]; i++) {
			this->buffer[i] = rhs.buffer[i];
		}
	}
	return (*this);
}

void CircularBuffer::addToBuffer(char* buf, ssize_t numbytes) {
	for (ssize_t i = 0; i < numbytes; i++) {
		this->buffer[p_head] = static_cast<unsigned char> (buf[i]);
		p_head++;
		if (p_head == MAXDATASIZE * 2)
			p_head = 0;
	}
}

int CircularBuffer::findCRLF() const {
	for (int i = p_tail; buffer[i + 1]; i++) {
		if (buffer[i] == '\r' || buffer[i + 1] == '\n' || (buffer[i] == '\r' && buffer[i + 1] == '\n'))
			return (i);
	}
	return (-1);
}

std::string CircularBuffer::extractBuffer() {
	int templen = 0;
	int tail_backup = p_tail;
	while (p_tail != p_head) { //calculating len of the buffered msg
		p_tail++;
		if (p_tail == MAXDATASIZE * 2)
			p_tail = 0;
		templen++;
	}
	
	unsigned char* tempbuffer = new unsigned char[templen];
	for (int i = 0; tail_backup != p_head; i++) { //copy buffer to temp & zero buffer
		tempbuffer[i] = buffer[tail_backup];
		buffer[tail_backup] = '\0';
		tail_backup++;
		if (tail_backup == MAXDATASIZE * 2)
			tail_backup = 0;
	}

	std::string bufferString(reinterpret_cast<char*>(tempbuffer)); //cast and save as string
	delete[] tempbuffer; //free temp

	size_t index = 0;
    while ((index = bufferString.find("^D", index)) != std::string::npos) // find "^D"
        bufferString.replace(index, 2, ""); //replace "^D" with ""

	return (bufferString);
}
