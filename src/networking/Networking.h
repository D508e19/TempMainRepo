#ifndef NETWORK_H
#define NETWORK_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <queue>

#include "src/datatypes/message.h"

class Networking
{
private:
	static const int msgArraySize = 80;
	int sockfd; //socket file descriptor 

	std::queue<Message> ReceivedQueue;
	std::queue<Message> OutgoingQueue;

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

	//std::cout << "1 Socket id: " << sockfd << std::endl;

	char testMsg[] = "C++ msg\n";
	//wbuff = (char *)msg.c_str(); // convert from string to c string, has to have \0 terminal 

	//std::cout << "2 Socket id: " << sockfd << std::endl;
}

void Networking::QueueMsg(char msg[], int sizeOfArray)
{
	/*
	char msgConverted[msgArraySize];
	for(int i = 0; i < sizeOfArray; i++)
	{
		msgConverted[i] = msg[i];
	}*/

	Message message = Message(msg, sizeOfArray);

	OutgoingQueue.push(message);
}

char* Networking::GetMsg()
{
	Message receivedMsg = ReceivedQueue.front();
	ReceivedQueue.pop();
	return receivedMsg.GetTextCharArray();
}

void Networking::Tick()
{
	//std::cout << "3 Socket id: " << sockfd << std::endl;
	std::cout << "Networking tick" << std::endl;
	//SendMsg();
	ReceiveMsg();
}

void Networking::SendMsg()
{
	if(OutgoingQueue.size() == 0)
	{
		return;
	}

	//std::cout << "Size of outgoingQueue: " << 

	int wbytes;
	char * wbuff;

	std::cout << "Test 1" << std::endl;

	/*
	char* msgToSendPtr = OutgoingQueue.front(); //Get msg to send
	OutgoingQueue.pop();
	char msgToSendArray[] = {&msgToSendPtr};

	char cstr[]

	msgToSendString = msgToSendString + "\n"; //append newline

	char cstr[msgToSendString.size() + 1];
	strcpy(cstr, msgToSendString.c_str());
	*/
	//wbuff = (char *)msg.c_str(); // convert from string to c string, has to have \n terminal 

	Message msgToSend = OutgoingQueue.front();
	OutgoingQueue.pop();
	
	std::cout << "Test 2" << std::endl;

	char* formattet = msgToSend.GetTextSendFormattet();

	std::cout << "Test 3" << std::endl;

	send(sockfd, formattet , strlen(formattet) , 0 );
	send(sockfd, "\n" , strlen("\n") , 0 );
	//send(sockfd, "mikkel\n" , strlen("mikkel\n") , 0 );

	//std::string msg = "Test";
	//char testMsg[] = "C++ msg\n";
	//wbuff = (char *)msg.c_str(); // convert from string to c string, has to have \0 terminal 

	//send(sockfd, testMsg , strlen(testMsg) , 0 );

	std::cout << "Test 4" << std::endl;

	if(wbytes < 0)
	{
		std::cout << "Cannot write to socket" << std::endl;
	}

	std::cout << "msg send: " << formattet << std::endl;
}

void Networking::ReceiveMsg()
{
	fd_set readset;
	FD_ZERO(&readset);
	FD_SET(sockfd, &readset);
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1;

	int selectAnswer = select(sockfd +1, &readset, NULL, NULL, &tv);
	std::cout << "Select answer: " << selectAnswer << std::endl;

	if(selectAnswer == -1)
	{
		std::cout << "Select failed!!" << std::endl;
		return;
	}
	else if(selectAnswer)
	{
		std::cout << "Select says that data is available" << std::endl;
	}
	else
	{
		std::cout << "Select waited all allowed time, and did not receive anything" << std::endl;
		return;
	}
		
	msghdr *msg;
	char buffer[msgArraySize];
	std::cout << "Before recv" << std::endl;
	int sizeOfMsg = recv(sockfd, buffer, sizeof(buffer), 0);
	std::cout << "AFter recv" << std::endl;
	std::cout << "Size: " << sizeOfMsg << " Received msg: " << buffer << std::endl;
	Message receivedMsg = Message(buffer, msgArraySize);
	//TODO THE RECEIVED MSG MIGHT CONTAIN MORE THAN ONE MSG!!
	ReceivedQueue.push(receivedMsg);
}

#endif
