/*
** a simple test server that will print out msgs that clients send
*/

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring> // C-style string manip.
#include <unistd.h> //close()
#include <cstdlib>

#include <poll.h> //struct pollfd
#include <fcntl.h> //fcntl
#include <sys/types.h> //types needed for socket() ftions
#include <sys/socket.h> //socket(), connect(), struct sockaddr
#include <netdb.h> //get- & freeaddrinfo(), gai_strerror()
#include <arpa/inet.h> //inet
#include <netinet/in.h> //??????

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT "6667"
#define BACKLOG 10
#define MAXDATASIZE 512

#define WAIT 0

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int get_listener_socket(void) {
	struct addrinfo hints, *servinfo, *p;
	int sockfd, rv;

	memset(&hints, 0, sizeof(hints)); //init & configure socket
	hints.ai_family = AF_UNSPEC; //set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM; // tcp bestttt
	hints.ai_flags = AI_PASSIVE;
	char s[INET6_ADDRSTRLEN];

	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;

	if ((rv = getaddrinfo(NULL, SERVER_PORT, &hints, &servinfo))) { //resolve addr & port
		std::cerr << "getaddrinfo: " << gai_strerror(rv) << std::endl;
		return (-1);
	}

	//loop to create a socket & connect to available addr
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) { //create a socket
			perror("socket");
			continue ;
		}
		// fcntl(sockfd, F_SETFL, O_NONBLOCK);
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		//accept()
		break ;
	}

	freeaddrinfo(servinfo); //no need for this anymore

	if (p == NULL) {
		std::cerr << "getaddrinfo: failed to connect :(" << std::endl;
		return (-1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		return (-1);
	}

	return (sockfd);
}

//void add_to_pfds(struct pollfd *pfds[], int newfd, int *fd_count, int *fd_size);
//void del_from_pfds(struct pollfd pfds[], int i, int *fd_count);

int main (void) {
	int sockfd = get_listener_socket();
	if (sockfd == -1) {
		std::cerr << "failed to create listening socket" << std::endl;
		return (1);
	}

	char s[INET6_ADDRSTRLEN];
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;

	int fd_size = 5;
	int fd_count = 0;
	struct pollfd *pfds;
	pfds = (struct pollfd*)malloc(sizeof(struct pollfd) * fd_size);

	pfds[0].fd = sockfd; //storing the listener in index 0 :)
	pfds[0].events = POLLIN; //and specifying that this will be used to register incoming traffic
	fd_count++; //since we just added one...

	int new_fd; //for storing the fd of new clients

	while (1) {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			perror("accept");
			continue;
		}
		else {
			inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
			printf("server: got connection from %s\n", s);
			break;
		}
	}

	//we have a connection!
	char buf[MAXDATASIZE];
	int numbytes;
	if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("server: received '%s'\n",buf);

	close(sockfd);
	close(new_fd);

	return (0);
}
