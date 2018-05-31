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

int main(int argc, char *argv[])
{

	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		printf("open error\n");
		exit(-1);
	}
	int ttl = 1;
	if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &ttl, sizeof(ttl)) < 0){
		printf("setsockopt error\n");
		exit(-1);
	}
	struct sockaddr_in multicastAddr;
	memset(&multicastAddr, 0, sizeof(multicastAddr));
	multicastAddr.sin_family = AF_INET;
	multicastAddr.sin_addr.s_addr = get_multicast_address();
	multicastAddr.sin_port = htons(get_multicast_port());

	Message msg;

	msg.passwds[0][0] = htons('c');
	msg.passwds[0][1] = htons('m');
	msg.passwds[0][2] = htons('p');
	msg.passwds[0][3] = htons('s');
	msg.passwds[0][4] = htons('\0');
	//msg.num_passwd = htons(1);
	//once i get the \0 i go to the next

	//to get the udp packet i dont need the hostnome
	// i recieve it and send it back with TCP protocol where i need a hostname

	for (;;) {
		printf("Sending msg for: %s\n", "nmeddin");
		int n = sendto(sockfd,(void *)&msg, sizeof(msg), 0,
		(struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
		if (n < 0){
			printf("Write error\n");
			exit(-1);
		}
		sleep(1);
	}
	close(sockfd);
}