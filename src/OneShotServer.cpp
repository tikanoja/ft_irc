/*
** a simple test client that will fire one msg to the server
*/

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring> // C-style string manip.
#include <unistd.h> //close()


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

int main (void) {
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
		return (1);
	}

	//loop to create a socket & connect to available addr
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) { //create a socket
			perror("socket");
			continue ;
		}
		fcntl(sockfd, F_SETFL, O_NONBLOCK);
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}
		//accept()
		break ;
	}

	if (p == NULL) {
		std::cerr << "getaddrinfo: failed to connect :(" << std::endl;
		freeaddrinfo(servinfo); //cleanup
		return (1);
	}
	freeaddrinfo(servinfo);

		if (listen(sockfd, BACKLOG) == -1) {
			perror("listen");
			exit(1);
		}
	int new_fd;
	while (1) {
		sin_size = sizeof their_addr;
		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1) {
			//perror("accept");
			// return 1;
			continue;
		}
		else {
			inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
			printf("server: got connection from %s\n", s);
			break;
		}
	}

	char buf[MAXDATASIZE];
	ssize_t numbytes;
	if ((numbytes = recv(new_fd, buf, MAXDATASIZE-1, 0)) == -1) {
		perror("recv");
		exit(1);
	}
	buf[numbytes] = '\0';
	printf("client: received: '%s'\n",buf);

	std::string message = "Sever received the message";
	char	*msg = strdup(message.c_str());
	size_t	msg_len = strlen(msg);
	std::cout << "Message length: " << msg_len << std::endl;
	ssize_t total = 0;
	ssize_t n_sent = 0;
	while (total < static_cast<ssize_t>(msg_len) ){
		if ( (n_sent = send( sockfd,  &(msg[total]), msg_len, 0 ) ) <= 0)
			perror("send");
		total += n_sent;
		std::cout << "Sent: " << n_sent << "\tSent total:" << total << std::endl;
}

	close(sockfd);
	close(new_fd);

	
	return (0);
}
