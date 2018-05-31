// hacker.h

class Hacker
{
   public:
   void foo();
   int bar;
   void hacker_server();
   void hacker_client();


};

void socket_setup(int &sockfd, struct sockaddr_in &server_addr, struct ip_mreq &multicastRequest);
