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
#define MAXCLIENTS 10
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
	int yes = 1;

	memset(&hints, 0, sizeof(hints)); //init & configure socket
	hints.ai_family = AF_UNSPEC; //set to IPv agnostic
	hints.ai_socktype = SOCK_STREAM; // tcp bestttt
	hints.ai_flags = AI_PASSIVE;

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
		if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
			perror("setsockopt");
			exit(1);
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

	freeaddrinfo(servinfo); //no need for this anymore

	if (p == NULL) {
		std::cerr << "getaddrinfo: failed to connect :(" << std::endl;
		return (-1);
	}

	if (listen(sockfd, MAXCLIENTS) == -1) {
		perror("listen");
		return (-1);
	}

	return (sockfd);
}

void add_to_pfds(struct pollfd pfds[], int new_fd, nfds_t *fd_count) {
	pfds[*fd_count].fd = new_fd; //storing the new connection
	pfds[*fd_count].events = POLLIN; //and specifying that this will be used to register incoming traffic
	(*fd_count)++;//since we just added one...
}
void del_from_pfds(struct pollfd pfds[], nfds_t i, nfds_t *fd_count) {
	pfds[i] = pfds[*fd_count];
	(*fd_count)--;
}

int main (void) {
	int sockfd = get_listener_socket();
	if (sockfd == -1) {
		std::cerr << "failed to create listening socket" << std::endl;
		return (1);
	}

	char s[INET6_ADDRSTRLEN];
	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size;

	nfds_t fd_count = 0;
	struct pollfd pfds[MAXCLIENTS];

	pfds[0].fd = sockfd; //storing the listener in index 0 :)
	pfds[0].events = POLLIN; //and specifying that this will be used to register incoming traffic
	fd_count++; //since we just added one...

	int new_fd; //for storing the fd of new clients

	while (1) {
		int poll_count = poll(pfds, fd_count, -1);
		if (poll_count == -1) {
			perror("polling");
			exit (1);
		}

		for(nfds_t i = 0; i < fd_count; i++) {
			if (pfds[i].revents & POLLIN) { // We got one!!
				//is it the listener or client?
				if (i == 0) {//listener!
					sin_size = sizeof their_addr;
					new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
					if (new_fd == -1) { //bad accept
						perror("accept");
						continue;
					} else {
						inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
						printf("server: got connection from %s\n", s);
						add_to_pfds(pfds, new_fd, &fd_count);
					}
				} else { //SAVE THE NEW FD
					//function to add the fd to array
					char buf[MAXDATASIZE];
					ssize_t numbytes;
					numbytes = recv(pfds[i].fd, buf, MAXDATASIZE-1, 0);
					if (numbytes <= 0) {
						if (numbytes == 0)
							std::cout << "connection closed" << std::endl;
						else
						{
							perror("recv");
							std::cout << numbytes << std::endl;
						}	
						close(pfds[i].fd);
						del_from_pfds(pfds, i, &fd_count);
						continue ;
					}
					buf[numbytes] = '\0'; //there is stuff to read wohhooo
					printf("server: received '%s'\n",buf);
					//sending msg back to client
					std::string message = "Sever received the message";
					char	*msg = strdup(message.c_str());
					size_t	msg_len = strlen(msg);
					std::cout << "Message length: " << msg_len << std::endl;
					ssize_t total = 0;
					ssize_t n_sent = 0;
					while (total < static_cast<ssize_t>(msg_len) ){
						if ( (n_sent = send( pfds[i].fd,  &(msg[total]), msg_len, 0 ) ) <= 0)
							perror("send");
						total += n_sent;
					}
					std::cout << "Sent: " << n_sent << "\tSent total:" << total << std::endl;
				}
			}
		}
	}

	for (int i = 0; i < fd_count; i++) {
		close(pfds[i].fd);
	}

	return (0);
}
