#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include <netinet/in.h>

int main()
{

    int randomnumber;
    randomnumber = rand() % 100;
    printf("%d\n", randomnumber);
    char stringRNumber[5];
    itoa(randomnumber, stringRNumber, 10);
    int gameend = 1;

    char Up[256] = "\nGo Up\n";
    char Down[256] = "\nGo Down\n";
    char End[256]="END";

    char buf[3];

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

    do
    {
        recv(client_socket, &buf, sizeof(buf) - 1, 0); // Adjust size to leave space for null terminator
        buf[strlen(buf)] = '\0';                       // Manually null-terminate
        printf("\n %s \n", buf);

        int newnum=atoi(buf);

        if(newnum==randomnumber)
        {
            gameend = 0;
            send(client_socket, End, sizeof(End), 0);
        }
        if(newnum<randomnumber)
        {
            send(client_socket, Up, sizeof(Up), 0);
        }
        if(newnum>randomnumber)
        {
            send(client_socket, Down, sizeof(Down), 0);
        }
        
    } while (gameend == 1);

    // close the socket
    close(server_socket);

    return 0;
}