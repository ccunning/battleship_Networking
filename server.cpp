#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <iostream>
#include <string>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

#include "battleshipprotocol.h"

#define PORTNUMBER	6683
#define PORTNUMBER2	6684
#define TIMEOUT 30
#define MAXSIZE 128

char localhost[] = "localhost";    /* default host name*/

using namespace std;

int main()
{
	struct sockaddr_in S1Addr;
	struct sockaddr_in S2Addr;
	struct sockaddr_in C1Addr;
	struct sockaddr_in C2Addr;
	
	BaShPr temp, protoRead;
	
	int c1socket, c2socket, tempSock;
	socklen_t alen;
	int i, j, k, n;
	
	int commTemp, op1Temp, op2Temp;
	
	bool turn=false;
	bool pTimeout=false;
	int tempStatus;
	
	string buf;
	char buffer[MAXSIZE];
	
	pid_t pid, pid2, wpid;
	
	char *host;
	
	struct hostent *ptrh;
	
	
	
	memset((char *)&S1Addr,0,sizeof(S1Addr));
	S1Addr.sin_family = AF_INET;
	S1Addr.sin_addr.s_addr = INADDR_ANY;
	S1Addr.sin_port = htons((u_short)0);
	
	memset((char *)C1Addr.sin_zero,0,sizeof(C1Addr.sin_zero));
    C1Addr.sin_family = AF_INET;
    host = localhost;
    if((ptrh=gethostbyname(host))==0){
        fprintf(stderr,"invalid host: %s\n", host);
        exit(1);
	}
    memcpy(&C1Addr.sin_addr, ptrh->h_addr, ptrh->h_length);
    C1Addr.sin_port = htons((u_short)PORTNUMBER);
    
    memset((char *)&S2Addr,0,sizeof(S2Addr));
	S2Addr.sin_family = AF_INET;
	S2Addr.sin_addr.s_addr = INADDR_ANY;
	S2Addr.sin_port = htons((u_short)PORTNUMBER2);
	
	//connect to host client
	c1socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(c1socket < 0)
	{
		perror("Socket C1 creation");
		exit(EXIT_FAILURE);
	}
	
	if(bind(c1socket, (struct sockaddr *)&S1Addr, sizeof(S1Addr)) < 0)
	{
		perror("C1 bind");
		exit(EXIT_FAILURE);
	}
	
	if(connect(c1socket, (struct sockaddr *)&C1Addr, sizeof(C1Addr)) < 0)
	{
		perror("connect C1");
		exit(EXIT_FAILURE);
	}
	cout <<"Connected and Server Started." <<endl;
	
	//listen and connect to nonhost client 
	tempSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(c2socket < 0)
	{
		perror("Socket C2 temp creation");
		exit(EXIT_FAILURE);
	}
	
	if(bind(tempSock, (struct sockaddr *)&S2Addr, sizeof(S2Addr)) < 0)
	{
		perror("C2 bind");
		exit(EXIT_FAILURE);
	}
	
	listen(tempSock, 1);
	
	alen = sizeof(C2Addr);
	
	c2socket = accept(tempSock, (struct sockaddr *) &C2Addr, &alen);
	if(c2socket < 0)
	{
		perror("accept C2");
		exit(EXIT_FAILURE);
	}
	
	//send ready commands
	temp.setCommand(8,0,0);
	
	buf = temp.outputComm();
	write(c1socket, buf.c_str(), strlen(buf.c_str()));
	write(c2socket, buf.c_str(), strlen(buf.c_str()));
	
	pid = fork();
	
	if(pid < 0)
	{
		perror("fork failure");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0) //client 1 check for ack
	{
		pid2 = fork();
		
		if(pid2 < 0)
		{
			perror("fork failure");
			exit(EXIT_FAILURE);
		}
		if(pid2 == 0)
		{
			bzero(buffer, sizeof(buffer));
			read(c1socket, buffer, sizeof(buffer));
			buf = buffer;
			//cerr <<"C1: " <<buf <<endl;
			//protoRead.inputComm(buf);
			//if(protoRead.
			exit(0);
		}
		else
		{
			int waittime = 0;
			int Stat;
			do
			{
				wpid = waitpid(pid2, &Stat, WNOHANG);
				if(wpid == 0)
				{
					if (waittime < TIMEOUT)
					{
						waittime++;
						sleep(1);
					}
					else
					{
						kill(pid2, SIGKILL);
						pTimeout = true;
						wpid = waitpid(pid2, &Stat, 0);
					}
				}
			}while(wpid == 0 && waittime <= TIMEOUT);
		}
		
		exit(0);
	}
	else //client 2 check for ack
	{
		pid2 = fork();
		
		if(pid2 < 0)
		{
			perror("fork failure");
			exit(1);
		}
		if(pid2 == 0)
		{
			bzero(buffer, sizeof(buffer));
			read(c2socket, buffer, sizeof(buffer));
			buf = buffer;
			//cerr <<"C2: " <<buf <<endl;
			exit(0);
		}
		else
		{
			int waittime = 0;
			int Stat;
			do
			{
				wpid = waitpid(pid2, &Stat, WNOHANG);
				if(wpid == 0)
				{
					if (waittime < TIMEOUT)
					{
						waittime++;
						sleep(1);
					}
					else
					{
						kill(pid2, SIGKILL);
						pTimeout = true;
						waitpid(pid2, &Stat, 0);
					}
				}
			}while(wpid == 0 && waittime <= TIMEOUT);
		}
			
		waitpid(pid, &tempStatus, 0);		
	}
	
	
	
	close(c1socket);
	close(c2socket);
	
	cerr <<"--------SERVER HAS SHUT DOWN!!!----------" <<endl;
	return 0;
}
	
	
	
