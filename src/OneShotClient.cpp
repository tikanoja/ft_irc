/*
** a simple test client that will fire one msg to the server
*/

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring> // C-style string manip.
#include <unistd.h> //close()

#include <sys/types.h> //types needed for socket() ftions
#include <sys/socket.h> //socket(), connect(), struct sockaddr
#include <netdb.h> //get- & freeaddrinfo(), gai_strerror()

#define SERVER_ADDR "irc.server.net"
#define SERVER_PORT "6667"
#define MESSAGE "oh my god it worked\r\n"

#define WAIT 0

int main (void) {
	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;

	memset(&hints, 0, sizeof(hints)); //init & configure socket
	hints.ai_family = AF_UNSPEC; //set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM; // tcp bestttt

	if (rv = getaddrinfo(SERVER_ADDR, SERVER_PORT, &hints, &servinfo)) { //resolve addr & port
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		return (1);
	}

	//loop to create a socket & connect to available addr
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) { //create a socket
			perror("socket");
			continue ;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) { //connect socket to server addr
			close(sockfd); // close socket if no dice
			perror("connect");
			continue ;
		}
		break ;
	}

	if (p == NULL) {
		std::cerr << "getaddrinfo: failed to connect :(" << std::endl;
		freeaddrinfo(servinfo); //cleanup
		return (1);
	}

	//we have a connection!

	std::string msg = MESSAGE;
	send(sockfd, msg.c_str(), msg.size(), 0);

	// if (WAIT) {
	// 	// recv() from server
	// }

	close(sockfd);
	freeaddrinfo(servinfo);
	
	return (0);
}
