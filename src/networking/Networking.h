#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>

class Networking
{
private:
	static const int msgArraySize = 80;
	int sockfd; //socket file descriptor 

	std::queue<char[msgArraySize]> ReceivedQueue;
	std::queue<char[msgArraySize]> OutgoingQueue;

	void SendMsg();
	void ReceiveMsg();

public:
	Networking();
	~Networking();

	void Connect();
	void QueueMsg(char msg[], int sizeOfArray);
	char* GetMsg();
	void Tick();
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

void Networking::QueueMsg(char msg[], int sizeOfArray)
{
	char msgConverted[msgArraySize];
	for(int i = 0; i < sizeOfArray; i++)
	{
		msgConverted[i] = msg[i];
	}

	OutgoingQueue.push(msgConverted);
}

char* Networking::GetMsg()
{
	char* receivedMsg = ReceivedQueue.front();
	ReceivedQueue.pop();
	return receivedMsg;
}

void Networking::Tick()
{
	SendMsg();
	ReceiveMsg();
}

void Networking::SendMsg()
{
	if(OutgoingQueue.size() == 0)
	{
		return;
	}

	int wbytes;
	char * wbuff;

	std::string msgToSendString = OutgoingQueue.front(); //Get msg to send
	OutgoingQueue.pop();
	msgToSendString = msgToSendString + "\n"; //append newline

	char cstr[msgToSendString.size() + 1];
	strcpy(cstr, msgToSendString.c_str());
	
	//wbuff = (char *)msg.c_str(); // convert from string to c string, has to have \n terminal 

	send(sockfd, cstr , strlen(cstr) , 0 );

	if(wbytes < 0)
	{
		std::cout << "Cannot write to socket" << std::endl;
	}

	std::cout << "msg send" << std::endl;
}

void Networking::ReceiveMsg()
{
	msghdr *msg;
	char buffer[msgArraySize];
	recv(sockfd, buffer, sizeof(buffer), 0);
	std::cout << "Received msg: " << buffer << std::endl;
	ReceivedQueue.push(buffer);
}

#endif
