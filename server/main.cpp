#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include "param.h"

// initalize port
char* port = "5000";


int main(int argc, char *argv[])
{
    switch (argc) {
    case 1:
        // use default port;
        break;
    case 2:
        port = argv[1];
        break;
    default:
        printf("Usage exe. [port] [IP type(0->IPv4; 1->IPv6)]");
        exit(EXIT_FAILURE);
        break;
    }
    printf("Port: %s\n", port);

    int server_fd = initalize_server();;

    accept_connections(server_fd);

    return 0;
}
