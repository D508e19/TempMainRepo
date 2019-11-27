#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

class Networking
{
private:
	int sockfd; //socket file descriptor 

public:
	Networking();
	~Networking();

	void Connect();
	void WriteMsg(std::string msg);
	void ReceiveMsg();
};

Networking::Networking(){};
Networking::~Networking(){}

void Networking::Connect()
{
	int portno; // port number
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char ipAddress[] = "127.0.0.1";
	int portNumber = 59090; // port number
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // generate file descriptor 
	if (sockfd < 0)
	{
		std::cout << "ERROR opening socket" << std::endl;
	}
	
	server = gethostbyname(ipAddress); //the ip address (or server name) of the listening server.
	if (server == NULL) {
		std::cout << "ERROR, no such host\n" << std::endl;
		exit(0);
	}
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portNumber);
	
	if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
	{
		std::cout << "ERROR connecting" << std::endl;
	}
}

void Networking::WriteMsg(std::string msg)
{
	int wbytes;
	char * wbuff; 
	char testMsg[] = "C++ msg\n";
	wbuff = (char *)msg.c_str(); // convert from string to c string, has to have \0 terminal 

	send(sockfd, testMsg , strlen(testMsg) , 0 );

	if(wbytes < 0)
	{
		std::cout << "Cannot write to socket" << std::endl;
	} 

	std::cout << "msg send" << std::endl;
}

void Networking::ReceiveMsg()
{
	msghdr *msg;
	char buffer[80];
	recv(sockfd, buffer, sizeof(buffer), 0);
	std::cout << "Received msg: " << buffer << std::endl;
}

#endif
