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

#include "battleshipprotocol.h"

#define PORTNUMBER	6683
//#define PORTNUMBER2	6684
#define TIMEOUT 15

using namespace std;

int main()
{
	struct sockaddr_in S1Addr;
	struct sockaddr_in S2Addr;
	struct sockaddr_in C1Addr;
	struct sockaddr_in C2Addr;
	
	BaShPr temp, protoRead;
	
	int c1socket, c2socket, tempSock;
	int alen;
	int i, j, k, n;
	
	int commTemp, op1Temp, op2Temp;
	
	bool turn=false;
	bool pTimeout=false;
	int tempStatus;
	
	string buf;
	
	pid_t pid, pid2, wpid;
	
	
	
	memset((char *)&S1Addr,0,sizeof(S1Addr));
	S1Addr.sin_family = AF_INET;
	S1Addr.sin_addr.s_addr = INADDR_ANY;
	S1Addr.sin_port = htons((u_short)0);
	
	memset((char *)C1Addr.sin_zero,0,sizeof(C1Addr.sin_zero));
    C1Addr.sin_family = AF_INET;
    C1Addr.sin_port = htons((u_short)PORTNUMBER);
    
    memset((char *)&S2Addr,0,sizeof(S2Addr));
	S2Addr.sin_family = AF_INET;
	S2Addr.sin_addr.s_addr = INADDR_ANY;
	S2Addr.sin_port = htons((u_short)PORTNUMBER);
	
	c1socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(c1socket < 0)
	{
		perror("Socket C1 creation");
		exit(1);
	}
	
	if(bind(c1socket, (struct sockaddr *)&S1Addr, sizeof(S1Addr)) < 0)
	{
		perror("C1 bind");
		exit(1);
	}
	
	if(connect(c1socket, (struct sockaddr *)&C1Addr, sizeof(C1Addr)) < 0)
	{
		perror("connect C1")
		exit(1);
	}
	
	
	
	tempSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(c2socket < 0)
	{
		perror("Socket C2 temp creation");
		exit(1);
	}
	
	if(bind(tempSock, (struct sockaddr *)&S2Addr, sizeof(S2Addr)) < 0)
	{
		perror("C2 bind");
		exit(1);
	}
	
	listen(tempSock, 1);
	
	alen = sizeof(C2Addr);
	
	c2socket = accept(tempSock, (struct sockaddr *) &C2Addr, &alen);
	if(c2socket < 0)
	{
		perror("accept C2");
		exit(1);
	}
	
	temp.setCommand(8,0,0);
	
	buf = temp.outputComm();
	write(c1socket, buf.c_str(), strlen(buf.c_str()));
	write(c2socket, buf.c_str(), strlen(buf.c_str()));
	
	pid = fork();
	
	if(pid < 0)
	{
		perror("fork failure");
		exit(1);
	}
	
	if(pid == 0) //client 1 check for ack
	{
		pid2 = fork();
		
		if(pid2 < 0)
		{
			perror("fork failure");
			exit(1);
		}
		if(pid2 == 0)
		{
			read(c1socket, buf, sizeof(buf));
			protoRead.inputComm(buf);
			if(proto
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
			read(c2socket, buf, sizeof(buf));
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
				}
			}while(wpid == 0 && waittime <= TIMEOUT);
		}
			
		waitpid(pid, &tempStatus, 0);		
	}
	
	if(
	
	
	return 0;
}
	
	
	
