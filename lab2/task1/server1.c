#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main()
{

	int Score = 3;
	char server_message[256] = "Answer only option Number\n\n\nWhats capital of Pakistan? \n1. Islamabad\n2. Karachi\n3. Lahore\n\nWhats the color of sky?\n1. Red\n2. Blue\n3. Green\n\nHow many color does rainbow have?\n1. 5\n2. 6\n3. 7\n\n";
	char buf[256];
	// create the server socket
	int server_socket;
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define the server address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(3001);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// bind the socket to our specified IP and port
	bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(server_socket, 5);
	int client_socket;
	client_socket = accept(server_socket, NULL, NULL);

	// send the message

	send(client_socket, server_message, sizeof(server_message), 0);
	recv(client_socket, &buf, 256, 0); // Adjust size to leave space for null terminator
	printf("\n %s \n", buf);

	if (buf[0] == '1')
	{
		Score += 1;
	}

	if (buf[1] == '2')
	{
		Score += 1;
	}

	if (buf[2] == '3')
	{
		Score += 1;
	}

	printf("\nTotal Score : %d", &Score);

	// close the socket
	close(server_socket);

	return 0;
}