/**
 * A simple TCP client.
 * Kien @ 4/2023
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void communication(int sock, const char* command) {
	char buff[128];
	strcpy(buff, command);
	write(sock, buff, sizeof(buff));

	bzero(buff, sizeof(buff));
	read(sock, buff, sizeof(buff));

	printf("response: %s\n", buff);
}


int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf("Usage: tcp-client SERVER PORT COMMAND\n");
		printf("Commands: time, ping, close");
		return 0;
	}

	struct addrinfo hints;
	bzero(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

	struct addrinfo* addrs;
    if (getaddrinfo(argv[1], argv[2], &hints, &addrs) != 0) {
        fprintf(stderr, "address resolution error\n");
        return 1;
    }

	for (struct addrinfo *addr = addrs; addr != NULL; addr = addr->ai_next) {
        int sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
        if (sockfd == -1) {
			fprintf(stderr, "socket creation failed\n");
            return -1;
        }

        if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) == 0) {
			printf("connected to server\n");
			communication(sockfd, argv[3]);
			close(sockfd);
			break;
		}

        close(sockfd);
    }

    freeaddrinfo(addrs);
	return 0;
}
