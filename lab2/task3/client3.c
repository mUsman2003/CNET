#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include <netinet/in.h>
int main()
{

	char request[256];
	char buf[3];

	int check = 1;
	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

	do
	{
		printf("Guess a number");
		scanf("%s", request);

		request[4] = '\0'; // Assuming you're truncating the string intentionally
		send(sock, request, strlen(request) + 1, 0);

		recv(sock, &buf, sizeof(buf), 0);
		if(strcmp(buf,"END"))
		{
			check==0;
			printf("END Game");
		}


	} while (check == 1);

	close(sock);

	return 0;
}