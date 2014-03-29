#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <netdb.h>

int main(int argc, char* argv[]){
// create a soket
int mysock, portNo, messageNo;
struct sockaddr_in serv_addr;
struct hostent *server;

char buffer[256];

if(argc<3){
	perror("ERROR: no portnumber provided\n");
	exit(1);
}
portNo = atoi(argv[2]);
mysock = socket(AF_INET,SOCK_STREAM,0);

if(mysock<0){
	perror("ERROR: socket not created");
}
// connect
server = gethostbyname(argv[1]);
if(server==NULL){
	perror("ERROR: cant get the host name");
	exit(0);
}

bzero((char *) &serv_addr,sizeof(serv_addr));
serv_addr.sin_family = AF_INET;
memcpy(&serv_addr.sin_addr, server->h_addr, server->h_length);
serv_addr.sin_port = htons(portNo); 

if(connect(mysock, (sockaddr *)&serv_addr, sizeof(serv_addr))<0){
	perror("ERROR: sever not connected");
}
// read and write
	while(true){
	printf("> ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);

	messageNo = write(mysock,buffer,strlen(buffer));
	if(messageNo<0){
		perror("ERROR: connect problem");
	}
	bzero(buffer,256);
	messageNo= read(mysock,buffer,255);
	if(messageNo<0){
		perror("ERROR: reading problem");
	}
	printf("server: %s\n", buffer);
}
return 0;
}
