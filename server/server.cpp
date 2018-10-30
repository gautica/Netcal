#include "server.h"
#include "Caculator.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include "param.h"
#include <thread>
#include <vector>

struct addrinfo hints;
addrinfo* addr_info;
#define BUFFER_SIZE 1024
std::vector<std::thread> vec;

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

void handle_connections(int socket)
{
    Caculator calc;
    while(1) {
        char buffer[BUFFER_SIZE];
        if (recv(socket,buffer, BUFFER_SIZE, 0) != 0) {
            std::string res_str = calc.caculate(buffer);
            char res[res_str.length()+1];
            strcpy(res, res_str.c_str());
            send(socket, res, strlen(res), 0);
        }
    }
}

void accept_connections(int socket_number) {

    while(1) {
        int new_client = 0;
        //int addrlen = sizeof(addr);
        if ((new_client = accept(socket_number, addr_info->ai_addr, &addr_info->ai_addrlen))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        vec.push_back(std::thread(handle_connections, new_client));
    }
}




