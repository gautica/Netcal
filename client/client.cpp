#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#define DEFAULT_PORT "5000"

int main(int argc, char const *argv[]){
	addrinfo hints;
	addrinfo* res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	printf("getaddrinfo: %i\n", getaddrinfo("localhost", argc > 1 ? argv[1] : DEFAULT_PORT, &hints, &res));
	int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	printf("socket: %i\n", s);
	printf("connect: %i\n", connect(s, res->ai_addr, res->ai_addrlen));
}
