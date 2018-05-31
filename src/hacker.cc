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


// create a class hacker and start threads for server and client

void receive(Message &msg);
void crack_(Message &msg);
void send(Message &msg);

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
		crack_(msg);
		send(msg);
		// sends to a tcp unicast

	}


}


void receive(Message &msg){
	//simple recieve string buffer
	//question: how just &msg, and, multicast addr vs remote_addr
	printf("RECEIVE\n"); 
	int sockfd;
	struct sockaddr_in server_addr;
	struct ip_mreq multicastRequest;

	socket_setup(sockfd, server_addr, multicastRequest);


	//for(;;){

		int n = recvfrom(sockfd, (void *)&msg, sizeof(msg), 0,NULL,0);

		if (n < 0){
			printf("Read error\n");
			exit(-1);
		}
		

	printf("cruzid: %s\n", msg.cruzid);
	printf("hostname: %s\n", msg.hostname);
	printf("port: %d\n", msg.port);

	//}
	
	close(sockfd);

}

void crack_(Message &msg){
	//printf("Num Passwords: %d\n", ntohs(msg.num_passwds));
	printf("CRACK\n");
	printf("Hash: %s\n", (msg.passwds[0]));
	//printf("Copy pasted hash: xxo0q4QVK0mOg\n");
	char plain[8];
	crack(msg.passwds[0], plain);
	strcpy(msg.passwds[0], plain);
	printf("Plaintext: %s\n", msg.passwds[0]);
}

void send(Message &msg){

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) exit(-1);

    struct hostent *server = gethostbyname(msg.hostname);
    if(server == NULL) exit(-1);

    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = (msg.port);
    printf("Sending to host: %d\n", msg.port);

	if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) exit(-1);



	write(sockfd, (void*)&msg, sizeof(msg));


}

void socket_setup(int &sockfd, struct sockaddr_in &server_addr, struct ip_mreq &multicastRequest) {

	//printf("socket setup\n");
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	//struct sockaddr_in server_addr;
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
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