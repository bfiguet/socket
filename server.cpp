#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>

//man socket
//int socket(int domain, int type, int protocol);

// Client needs to the servers port number

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
	int port = 1500;
	bool isExit = false;
	int bufsize = 1024;
	char buffer[bufsize];

	struct sockaddr_in server_addr;
	socklen_t	size;

	//init socket
	client = socket(AF_INET, SOCK_STREAM, 0);

	if (client < 0)
	{
		std::cout <<"Error establishing connection." << std::endl;
		exit (1);
	}
	std::cout << "Server Socket connection created..." << std::endl;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	server_addr.sin_port = htons(port);

	//binding socket
	if (bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		std::cout << "Error binding socket..." << std::endl;
		exit (1);
	}
	size = sizeof(server_addr);
	std::cout << "Looking for clients..." <<std::endl;

	//Listening socket
	listen(client, 1);

	//accept client
	server = accept(client, (struct sockaddr*)&server_addr, &size);

	if (server < 0)
	{
		std::cout << "Error on accepting..." << std::endl;
		exit(1);
	}

	while (server > 0)
	{
		strcpy(buffer, "Server connected...\n");
		send(server, buffer, bufsize, 0);

		std::cout << "Connected whith client..." << std::endl;
		std::cout <<"Enter # to end the connection" << std::endl;

		std::cout << "Client: " << std::endl;
		do {
			recv(server, buffer, bufsize, 0);
			std::cout << buffer << " ";
			if (*buffer == '#')
			{
				*buffer = '*';
				isExit = true;
			}
		} while (*buffer != '*');

		do {
			std::cout <<"\nServer: ";
			do {
				std::cin >> buffer;
				send(server, buffer, bufsize, 0);
				if (*buffer =='#')
				{
					send(server, buffer, bufsize, 0);
					*buffer = '*';
					isExit = true;
				}
			} while (*buffer != '*');

			std::cout << "Client: ";
			do {
				recv(server, buffer, bufsize, 0);
				std::cout << buffer << " ";
				if (*buffer == '#')
				{
					*buffer == '*';
					isExit = true;
				}
			} while (*buffer != '*');
		} while (!isExit);

		std::cout << "connection terminated..." <<std::endl;
		std::cout << "Goodbye..." <<std::endl;
		isExit = false;
		exit(1);
	}
	close(client);
	return 0;
}

