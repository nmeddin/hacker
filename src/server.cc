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

	//TODO: Refactor this
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

//i can convert vector to char[]
	//once i have a vector copyinf the characters is easy to code

	//make it parallere
	// each threads solves a password
	// each threads works on a subspace
	// one threads finds, multicasst DONE signal, al lmachines move on to next password

	char cruzid[] = "nmeddin";
	strcpy (msg.cruzid, cruzid);
	char cmpsHash[] = "xxo0q4QVK0mOg";
	for(unsigned int i = 0; i < 12; i++){

		printf("Putting hash into msg.passwds[%d]\n", i);
		strcpy(msg.passwds[i], cmpsHash);

	}
	msg.num_passwds = htons(12);
	char hostname[] = "localhost";
	strcpy(msg.hostname, hostname);
	msg.port = 1200;

	//once i get the \0 i go to the next

	//to get the udp packet i dont need the hostnome
	// i recieve it and send it back with TCP protocol where i need a hostname

	//for (;;) {
		printf("Sending msg for: %s\n", "nmeddin");
		int n = sendto(sockfd,(void *)&msg, sizeof(msg), 0, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr));
		if (n < 0){
			printf("Write error\n");
			exit(-1);
		}
		sleep(1);
	//}

	close(sockfd);


	//TCP Receive

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) exit(-1);

    struct sockaddr_in server_addr;
    bzero((char *) &server_addr, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = msg.port;

	if (bind(sockfd, (struct sockaddr *) 
		&server_addr, sizeof(server_addr)) < 0){
	printf("BIND ERROR\n");
	exit(-1);
	}

	listen(sockfd, 128);

	//char buffer[BUFF_SIZE];
	// start reading numbers. Push each received number into a vector
	struct sockaddr_in client_addr;
	socklen_t len = sizeof(client_addr);

	int newsockfd = accept(sockfd, (struct sockaddr*) &client_addr, &len);
	if(newsockfd < 0) exit(-1);

	int tcp_n = recv(newsockfd, (void*)&msg, sizeof(msg), 0);
	printf("Bytes read: %d\n", tcp_n);

	printf("Received plaintext: %s\n", msg.passwds[0]);


	close(sockfd);
}