#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
int main()
{

	char request[256];
	char buf[256];

	// create the socket
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);

	// setup an address
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(3001);

	connect(sock, (struct sockaddr *)&server_address, sizeof(server_address));

	recv(sock, &buf, sizeof(buf), 0);
	printf("\n %s \n", buf);

	scanf("%s", request);
	request[4] = '\0'; // Assuming you're truncating the string intentionally
	printf("\n %s \n", request);
	send(sock, &request, sizeof(request) , 0);

	close(sock);

	return 0;
}