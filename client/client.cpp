#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <regex>

#define DEFAULT_PORT "5000"
#define BUF_LEN 1024

int getInput(char* buf, int size){
	int c = 0;
	while(c < size-1){
		buf[c] = getchar();
		if(buf[c++] == '\n')
			break;
	}
	buf[c] = 0;
	return c;
}

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
	char buf[BUF_LEN];
	int len;
	
	std::regex e("(0x)?[a-fA-F0-9]+[-+*/](0x)?[a-fA-F0-9]+\n?");
	printf("test2\n");
	

	while(0==0){
		len = getInput(buf, BUF_LEN);
		if(len == 1)
			break;
		if(!std::regex_match(buf, e)){
			printf("Wrong format!\n");
			continue;
		}
		printf("%s", buf);
		send(s, buf, len, 0);
		len = recv(s, buf, BUF_LEN-1, 0);
		buf[len] = 0;
		printf("%s\n", buf);
	}
}
