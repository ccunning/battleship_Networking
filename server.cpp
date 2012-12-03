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
#include <time.h>
#include <queue>

#include "battleshipprotocol.h"

#define PORTNUMBER	6683
#define PORTNUMBER2	6684
#define TIMEOUT 30
#define MAXSIZE 128

char localhost[] = "localhost";    /* default host name*/

using namespace std;

int sendWithAck(int & socket, BaShPr & command);

int getWithAck(int & socket, BaShPr & command);

int main()
{
	struct sockaddr_in S1Addr;
	struct sockaddr_in S2Addr;
	struct sockaddr_in C1Addr;
	struct sockaddr_in C2Addr;
	
	BaShPr command;
	
	int c1socket, c2socket, tempSock;
	socklen_t alen;
	int i, j, k, n;
	
	int com, op1, op2;
	
	int commTemp, op1Temp, op2Temp;
	
	bool turn;
	bool pTimeout=false;
	int tempStatus;
	
	string buf;
	char buffer[MAXSIZE];
	
	pid_t pid, pid2, wpid;
	
	char *host;
	
	struct hostent *ptrh;
	
	int randomTemp;
	srand(time(NULL));
	
	/*** Initial Connections ***/
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
	
	/*** Send ready commands and receive ACKs ***/
	command.setCommand(8,0,0);
	
	buf = command.outputComm();
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
			do
			{
				bzero(buffer, sizeof(buffer));
				read(c1socket, buffer, sizeof(buffer));
				buf = buffer;
				
				command.inputComm(buf);
				
				command.getCommand(com, op1, op2);
			}while(com != 7);
			
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
		if(pTimeout)
		{
			exit(777);
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
			do
			{
				bzero(buffer, sizeof(buffer));
				read(c2socket, buffer, sizeof(buffer));
				buf = buffer;
				
				command.inputComm(buf);
				
				command.getCommand(com, op1, op2);
			}while(com != 7);
			
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
		if(tempStatus == 777 || pTimeout)
		{
			cerr <<"-----Timeout occured. Closing Server-----" <<endl;
			return 1;
		}
	}
	
	/*** Waiting for the clients to be done placing their pieces ***/
	pid = fork();

	if(pid < 0)
	{
		perror("fork failure");
		exit(EXIT_FAILURE);
	}
	
	if(pid == 0)
	{
		do
		{
			bzero(buffer, sizeof(buffer));
			if(read(c1socket, buffer, sizeof(buffer)) == 0)
			{
				pTimeout=true;
				break;
			}
			buf = buffer;
			
			command.inputComm(buf);
			
			command.getCommand(com, op1, op2);
		}while(com != 8);
		
		command.setCommand(7,0,0);
		buf = command.outputComm();
		write(c1socket, buf.c_str(), strlen(buf.c_str()));
		
		if(pTimeout)
		{
			exit(777);
		}
		exit(0);
	}
	
	else
	{
		do
		{
			bzero(buffer, sizeof(buffer));
			if(read(c2socket, buffer, sizeof(buffer)) == 0)
			{
				pTimeout=true;
				break;
			}
			buf = buffer;
			
			command.inputComm(buf);
			
			command.getCommand(com, op1, op2);
		}while(com != 8);
		
		command.setCommand(7,0,0);
		buf = command.outputComm();
		write(c2socket, buf.c_str(), strlen(buf.c_str()));
		
		waitpid(pid, &tempStatus, 0);
		if(tempStatus == 777 || pTimeout)
		{
			cerr <<"-----Timeout occured. Closing Server-----" <<endl;
			return 1;
		}
		
	}
	
	/*** Decide who goes first ***/
	randomTemp = rand() % 2;
	turn = !!randomTemp;
	
	bool exitFlag = false;
	queue<BaShPr> commQueue;
	
	/*** Run Game loop ***/
	do
	{
		if(turn)
		{
			//Player 1 goes
			command.setCommand(6,0,0); //tell C2 it is not it's turn
			if(!(sendWithAck(c2socket, command)))
			{
				cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
				exitFlag = true;
				break;
			}
			command.setCommand(8,0,0); //tell C1 it is it's turn
			if(!(sendWithAck(c1socket, command)))
			{
				cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
				exitFlag = true;
				break;
			}
			
			do 
			{
				if(!(getWithAck(c1socket, command)))//wait for C1 to send commands
				{
					cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
					exitFlag = true;
					break;
				}
				command.getCommand(com,op1,op2);
				if(com == 1 || com == 2) //only queue Fire and EoT
				{
					commQueue.push(command);
				}
				else if(com == 9)
				{
					exitFlag = true;
					break;
				}
				
			}while(com != 2); //exit loop when gets EoT
			
			while(!commQueue.empty() && !exitFlag)
			{
				command = commQueue.front();
				commQueue.pop();
				command.getCommand(com,op1,op2);
				
				if(com == 1)
				{
					if(!(sendWithAck(c2socket, command)))
					{
						cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
					if(!(sendWithAck(c1socket, command)))
					{
						cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
				}
				if(com == 2)
				{
					if(!(sendWithAck(c2socket, command)))
					{
						cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
					command.setCommand(2,0,0);
					if(!(sendWithAck(c1socket, command)))
					{
						cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
				}
				
			}
			
			!turn; //switch turns
		}
		else
		{
			//Player 2 goes
			command.setCommand(6,0,0); //tell C1 it is not it's turn
			if(!(sendWithAck(c1socket, command)))
			{
				cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
				exitFlag = true;
				break;
			}
			command.setCommand(8,0,0); //tell C2 it is it's turn
			if(!(sendWithAck(c2socket, command)))
			{
				cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
				exitFlag = true;
				break;
			}
			
			do 
			{
				if(!(getWithAck(c2socket, command)))//wait for C2 to send commands
				{
					cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
					exitFlag = true;
					break;
				}
				command.getCommand(com,op1,op2);
				if(com == 1 || com == 2) //only queue Fire and EoT
				{
					commQueue.push(command);
				}
				else if(com == 9)
				{
					exitFlag = true;
					break;
				}
				
			}while(com != 2); //exit loop when gets EoT
			
			while(!commQueue.empty() && !exitFlag)
			{
				command = commQueue.front();
				commQueue.pop();
				command.getCommand(com,op1,op2);
				
				if(com == 1)
				{
					if(!(sendWithAck(c1socket, command)))
					{
						cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
					if(!(sendWithAck(c2socket, command)))
					{
						cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
				}
				if(com == 2)
				{
					if(!(sendWithAck(c1socket, command)))
					{
						cerr <<"-----Connection to C2 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
					command.setCommand(2,0,0);
					if(!(sendWithAck(c2socket, command)))
					{
						cerr <<"-----Connection to C1 interupted. Closing Server.-----" <<endl;
						exitFlag = true;
						break;
					}
				}
				
			}
			
			!turn; //switch turns
		}
		
	}while(!exitFlag);
	
	command.setCommand(9,9,9);
	buf = command.outputComm();
	
	write(c1socket, buf.c_str(), strlen(buf.c_str()));
	write(c1socket, buf.c_str(), strlen(buf.c_str()));
	
	close(c1socket);
	close(c2socket);
	
	cerr <<"--------SERVER HAS SHUT DOWN!!!----------" <<endl;
	return 0;
}
	
	
int sendWithAck(int & socket, BaShPr & command)
{
	char buffer[MAXSIZE];
	string buf;
	int waittime=0;
	int Stat;
	
	int com, op1, op2;
	
	bool pTimeout=false;
	
	pid_t pid, wpid;
	
	buf = command.outputComm();
	write(socket, buf.c_str(), strlen(buf.c_str()));
	
	pid = fork();
		
	if(pid < 0)
	{
		perror("fork failure");
		return 0;
	}
	if(pid == 0)
	{
		do
		{
			bzero(buffer, sizeof(buffer));
			read(socket, buffer, sizeof(buffer));
			buf = buffer;
			
			command.inputComm(buf);
			
			command.getCommand(com, op1, op2);
		}while(com != 7);
		
		exit(0);
	}
	else
	{
		do
		{
			wpid = waitpid(pid, &Stat, WNOHANG);
			if(wpid == 0)
			{
				if (waittime < TIMEOUT+1)
				{
					waittime++;
					sleep(1);
				}
				else
				{
					kill(pid, SIGKILL);
					pTimeout = true;
					wpid = waitpid(pid, &Stat, 0);
				}
			}
		}while(wpid == 0 && waittime <= TIMEOUT);
	}
	
	if(pTimeout)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int getWithAck(int & socket, BaShPr & command)
{
	int com, op1, op2;
	char buffer[MAXSIZE];
	string buf;
	
	BaShPr temp(7,0,0);
	
	bzero(buffer, sizeof(buffer));
	if(read(socket, buffer, sizeof(buffer)) == 0)
	{
		return 0;
	}
	buf = buffer;

	command.inputComm(buf);
	
	buf = temp.outputComm();
	write(socket, buf.c_str(), strlen(buf.c_str()));
	
	return 1;
}
