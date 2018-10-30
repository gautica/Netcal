#include "server.h"
#include "Caculator.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>
#include "param.h"

struct addrinfo hints;
addrinfo* addr_info;
#define BUFFER_SIZE 1024

int initalize_server()
{
    int server_fd;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    getaddrinfo("localhost", port, &hints, &addr_info);
    // Creating socket file descriptor
    if ((server_fd = socket(addr_info->ai_family, addr_info->ai_socktype, addr_info->ai_protocol)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (bind(server_fd, addr_info->ai_addr, addr_info->ai_addrlen)<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void* handle_connections(void* socket)
{

    int new_client = *(int*) socket;
    free(socket);
    /**
    char* hello = "hello from server";



    printf("%s\n",buffer );
    send(new_client , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    */
    char buffer[BUFFER_SIZE];
    int valread = read( new_client , buffer, BUFFER_SIZE);
    Caculator calc;
    std::string res_str = calc.caculate(buffer);
    char res[res_str.length()+1];
    strcpy(res, res_str.c_str());

    printf("#######: %s\n", res);
    send(new_client , res, strlen(res) , 0);
    printf("Hello message sent\n");

}

void accept_connections(int socket_number) {
    pthread_t new_thread;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setstacksize(&attr, 1024);

    while(1) {
        int* new_client = (int*) malloc(sizeof(int));
        //int addrlen = sizeof(addr);
        if ((*new_client = accept(socket_number, addr_info->ai_addr, &addr_info->ai_addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Create new thread to handle new_client
        if (pthread_create(&new_thread, &attr, handle_connections, new_client) != 0) {
            perror("Failed to create new thread!\n");
            exit(EXIT_FAILURE);
        }
    }
}




