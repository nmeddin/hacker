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
	int ttl = 1;
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl)) < 0)
		exit(-1);
	struct sockaddr_in multicastAddr;
	memset(&multicastAddr, 0, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = get_multicast_address();
	multicastAddr.sin_port = htons(port);
	for (;;) {
		printf("Sending: %s\n", argv[2]);
		int n = sendto(sockfd,argv[2], strlen(argv[2]), 0,
			(struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
		if (n < 0) exit(-1);
		sleep(1);
	}
	close(sockfd);
}