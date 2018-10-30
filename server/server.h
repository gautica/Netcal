#ifndef SERVER_H
#define SERVER_H

#define PORT 5000

int initalize_server();

void handle_connections(int socket);

void accept_connections(int socket_number);

#endif
