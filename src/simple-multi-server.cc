#include "hacker.h"
#include "crack.h"
#include <sstream>
#include <thread>

#include <istream> 
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

//https://classes.soe.ucsc.edu/cmps109/Spring18/SECURE/15.Distributed5.pdf

int main(int argc, char *argv[])
{
	int port = atoi(argv[1]);
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) exit(-1);
	struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		exit(-1);
	struct ip_mreq multicastRequest;
	multicastRequest.imr_multiaddr.s_addr = get_multicast_address(); 
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		(void *) &multicastRequest, sizeof(multicastRequest)) < 0)
		exit(-1);
	char buffer[256];
	for (;;) {
		bzero(buffer,256);
		int n = recvfrom(sockfd,buffer,255,0,NULL,0);
		if (n < 0) exit(-1);
		printf("Received: %s\n", buffer);
	}
	close(sockfd);
}