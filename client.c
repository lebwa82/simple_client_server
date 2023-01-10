#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <time.h>


int main() {
    srand(time(NULL));
    int random, sleep_sleep, nomer = rand()%10+1;
    char server_message[256];

    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (network_socket < 0) {
        perror("error in calling socket()");
        return 1;
    };

    // specify an address for the socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    // check for error with the connection
    if (connection_status < 0) {
        printf("connect error\n");
        return 1;
    }

    while(1)
    {
        sleep_sleep = rand()%5;
        sleep(sleep_sleep);
        random = rand()%100;
        // send data
        sprintf(server_message, "client %d sleep %d number %d", nomer, sleep_sleep, random);
        int rc = send(network_socket, server_message, sizeof(server_message), 0);
        if (rc < -1) {
            perror("send error");
            return 1;
        }
    }

    //close the socket
    close(network_socket);
    return 0;
}