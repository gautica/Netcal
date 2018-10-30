#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <regex>
#include <unistd.h>

#define DEFAULT_PORT "5000"
#define BUF_LEN 1024

int getInput(char* buf, int size){
	int c = 0;
	while(c < size-1){
		buf[c] = getchar();
		if(buf[c++] == '\n')
			break;
	}
	buf[--c] = 0;
	return c;
}

int main(int argc, char const *argv[]){

	addrinfo hints;
	addrinfo* res;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	getaddrinfo("localhost", argc > 1 ? argv[1] : DEFAULT_PORT, &hints, &res);
	int s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	connect(s, res->ai_addr, res->ai_addrlen);
	char buf[BUF_LEN];
	int len;
	
	std::regex e("(0x[A-F0-9]+|[0-9]+|[01]b)[-+*/](0x[A-F0-9]+|[0-9]+|[01]b)");
	std::regex e2("0x[A-F0-9]+|[0-9]+|[01]b");
	

	while(0==0){
		len = getInput(buf, BUF_LEN);
		if(!len)
			break;
		if(std::regex_match(buf, e2)){
			buf[len++] = '+';
			buf[len++] = '0';
			buf[len] = 0;
		}
		if(!std::regex_match(buf, e)){
			printf("Wrong format!\n");
			continue;
		}
		send(s, buf, len, 0);
		len = recv(s, buf, BUF_LEN-1, 0);
		buf[len] = 0;
		printf("%s\n", buf);
	}
	close(s);
}
