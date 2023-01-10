#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <pthread.h>

void* read_cb(void* _fd)
{
    char buffer[1024];
    int fd = *(int*)_fd;
    ssize_t r = recv(fd, buffer, sizeof(buffer), 0);
    //printf("get\n");
    while(r>0)
    {
        printf("%s\n", buffer);
        r = recv(fd, buffer, sizeof(buffer), MSG_NOSIGNAL);
    }
}


int main() {
    pthread_t thread;

    // create the server socket
    int server_socket, rc;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("error in calling socket()");
        return 1;
    };

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // bind the socket to our specified IP and port
    rc = bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
    if (rc < 0)
    {
        perror("bind error");
        return 1;
    }

    // create a queue
    rc = listen(server_socket, 5);
    if (rc < 0)
    {
        perror("listen error");
        return 1;
    }

    int client_socket;
    while(1)
    {
        //create a connection with the client
        client_socket = accept(server_socket, NULL, NULL);
        int status = pthread_create(&thread, NULL, read_cb, &client_socket);
        if(status!=0)
        {
            printf("error in pthread_create");
            return 1;
        }

    }
    
    // close the socket
    close(server_socket);

    return 0;
}