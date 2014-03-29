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

int main(int argc,char*argv[]){

// create a socket
int mysock,acceptsock,portNo,acceptsklen;
char buffer[256];
struct sockaddr_in serv_addr,cli_addr;
int messageNo;

if(argc<2){
	perror("ERROR: no port number provided\n");
	exit(1);
}

mysock = socket(AF_INET,SOCK_STREAM,0);

if(mysock<0){
	perror("ERROR: can't open socket\n");
}

portNo = atoi(argv[1]);
bzero((char*) &serv_addr,sizeof(serv_addr));

serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portNo);

//bind a socket
if(bind(mysock,(struct sockaddr*) &serv_addr, sizeof(serv_addr))<0){
	perror("ERROR: can not bind socket");
}

// listen
listen(mysock,5);
acceptsklen = sizeof(cli_addr);
// accept the socket
acceptsock = accept(mysock, (struct sockaddr *) &cli_addr, (socklen_t*) &acceptsklen);

if(acceptsock<0){
	perror("ERROR: can not accept socket");
}

// read and write
while(true){
	bzero(buffer,256);
	messageNo = read(acceptsock,buffer,255);
	if(messageNo < 0){
		perror("ERROR: can not read");
	}
	printf("client: %s\n", buffer);
	printf(">: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	messageNo = write(acceptsock,buffer,strlen(buffer));

	if(messageNo < 0){
        	 perror("ERROR: can not read");
	}
}
return 0;




}
