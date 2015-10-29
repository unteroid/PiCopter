
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "udpServer.h"

char client_ip[] = "192.168.43.83";
struct sockaddr_in servaddr,cliaddr;
int client_port = 1366;

void* udpServer(void* param) 
{
  	int sockfd,n;
  	socklen_t len;
	uint8_t buff[1024];
	char msg[1024];
	int server_port = 1377;

  	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	if (sockfd < 0)
    	fprintf(stderr, "UDP SERVER ERROR: can't open socket \n");

  	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	servaddr.sin_port=htons(server_port);


	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr=inet_addr(client_ip);
	cliaddr.sin_port=htons(client_port);


	if (bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	fprintf(stderr, "UDP SERVER ERROR: binding error");

	fprintf(stderr, "UDP server created, now sending data \n");

	for (;;) 
	{
		sprintf (msg, "%f;%f;%f;%f;%f;%f", AHRS.operableData.gyr_y_f, AHRS.operableData.gyr_x_f, ArduinoUSB.receiverData.RCRoll, ArduinoUSB.receiverData.RCPitch, Control.yawPID.integral_, Control.yawPID.output);

		n = sendto(sockfd,msg,sizeof(msg),0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
		usleep(100000);
	}
}

void setIP(char *ip) 
{
	strcpy(client_ip,  ip);
	cliaddr.sin_family = AF_INET;
	cliaddr.sin_addr.s_addr=inet_addr(client_ip);
	cliaddr.sin_port=htons(client_port);

}

void getIP() 
{
	printf(" %s \n", client_ip);
}
