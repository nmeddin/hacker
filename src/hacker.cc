// hacker.cc

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

//step one: create a server and client
void receive(Message &msg);

int main(){

	//Message msg;
	//while (true)
	// receive(&msg)
	// crack(&msg)
	// send(&msg)
	printf("HELLO WORLD\n");

	Message msg;

	while(true){
		printf("hello\n");
		receive(msg);
		//reciveces from multi
		//crack(msg);
		//send(msg);
		// sends to a tcp unicast

	}

	//close(sockfd);

}


void receive(Message &msg){
	//simple recieve string buffer
	//question: how just &msg, and, multicast addr vs remote_addr
	printf("receive\n"); 
	int sockfd;
	struct sockaddr_in server_addr;
	struct ip_mreq multicastRequest;

	socket_setup(sockfd, server_addr, multicastRequest);


	for(;;){

		int n = recvfrom(sockfd, (void *)&msg, sizeof(msg), 0,NULL,0);

		if (n < 0){
			printf("Read error\n");
			exit(-1);
		}
		
		printf("Received msg for: %s\n", "nmeddin");
	}
	
}

// create a class hacker and start threads for server and client

void socket_setup(int &sockfd, struct sockaddr_in &server_addr, struct ip_mreq &multicastRequest) {

	printf("socket setup\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

	//struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(get_multicast_port());

	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0){
		printf("bind error\n");
		exit(-1);
	}
	
	//struct ip_mreq multicastRequest;
	multicastRequest.imr_multiaddr.s_addr = get_multicast_address();
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest, sizeof(multicastRequest)) < 0){
		printf("setsockopt error\n");
		exit(-1);

	}

}