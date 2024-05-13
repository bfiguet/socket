
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

// Server doesn't need to know the clients port number 

//man getnameinfo
//int getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
//                 char *host, socklen_t hostlen,
//                      char *serv, socklen_t servlen, int flags);


	//create a socket
	//Bind the socket to a IP/port
	//Mark the socket for listening in
	//Accept a call
	//Close the  kistening socket
	//While receving display message, print message
	//Close socket

int main()
{
	int client;
	int server;
	int port = 1500; //note the server ans client IP are the same
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];
	char *ip = "127.0.0.1";

	struct sockaddr_in server_addr;

	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);

	if (client < 0)
	{
		std::cout <<"Error creating socket..." << std::endl;
		exit (1);
	}
	std::cout << "Client Socket created" << std::endl;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	//connecting socket server
	if (connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0)
	{
		std::cout <<"Connecting to server..." <<std::endl;
	}
	recv(client, buffer, bufsize, 0);
	std::cout<<"Connection confirmed" <<std::endl;
	std::cout<<"Enter # to end the connection" <<std::endl;
	do {
		std::cout <<"Client: ";
		do {
			std::cin >> buffer;
			send(client, buffer, bufsize, 0);
			if (*buffer == '#')
			{
				send(client, buffer, bufsize, 0);
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != 42);

		std::cout << "Server: ";
		do {
			recv(client, buffer, bufsize, 0);
			std::cout << buffer << " ";
			if (*buffer == '#')
			{
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != 42);

		std::cout << std::endl;
	} while (!isExit);

	std::cout << "Connection terminated..." <<std::endl;
	std::cout <<"Goodbye" << std::endl;

	close(client);
	return 0;
}
