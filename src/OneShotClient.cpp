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

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT "6667"
#define MAXDATASIZE 512

#define WAIT 0

int main ( int ac, char **av ) {
	
	if (ac != 2){
		std::cout << "Provide a message to be sent to server" << std::endl;
		return 1;
	}

	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;

	memset(&hints, 0, sizeof(hints)); //init & configure socket
	hints.ai_family = AF_UNSPEC; //set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM; // tcp bestttt

	if ((rv = getaddrinfo(SERVER_ADDR, SERVER_PORT, &hints, &servinfo))) { //resolve addr & port
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

	char	*msg = av[1];
	size_t	msg_len = strlen(msg);
	std::cout << "Message length: " << msg_len << std::endl;
	ssize_t total = 0;
	ssize_t n_sent = 0;
	while ( total < static_cast<ssize_t>( msg_len ) ){
		if ( (n_sent = send( sockfd, &(msg[total]), msg_len, 0 ) ) < 0 )
			std::cerr << "Error: Sending data failed" << std::endl;
		if ( n_sent == 0 )
			std::cerr << "Error: Server closed connection" << std::endl;
		total += n_sent;
		std::cout << "Sent: " << n_sent << "\tSent total:" << total << std::endl;
	}

	char buf[MAXDATASIZE];
	ssize_t numbytes;
	if ((numbytes = recv(sockfd, buf, MAXDATASIZE - 1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("Confirmed: '%s'\n", buf);

	// if (WAIT) {
	// 	// recv() from server
	// }

	close(sockfd);
	freeaddrinfo(servinfo);
	
	return (0);
}
