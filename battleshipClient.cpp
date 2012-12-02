/**********************************************************************
 * 
 * PROJECT: BATTLESHIP
 * AUTHORS: KENNETH BOGNER
 * 			CURT CUNNING
 * CREATED: NOVEMBER 2012
 * 
 **********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <netdb.h>
#include <iostream>
#include <string>
#include <vector>
#include "cmdparser.h"
#include "ship.h"
#include "player.h"
#include "battleshipprotocol.h"

#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

using namespace std;


#define HOSTPORT	6683
#define NONHOSTPORT	6684

#define PORTNUMBER	6683
#define MAXSIZE 128


/* Displays the Battleship menu with basic command listing for startup */
void displayMenu();

void displayGrid();

/* Calls the appropriate command function that is part of the Player class */
void callCmd(int& sd, vector<string>& cmd, Cmd_t& type, Player& p);

int main() {
	string in_str, uname, buf;
	Cmd_t type;
	CmdParser parser;
	vector<string> cmd;
	char isHost;
	int sockid;
	sockaddr_in my_addr, server_addr;
	hostent *ptrh;
	BaShPr commTemp;
	
	char buffer[MAXSIZE];

	displayMenu(); /* Display title screen and menu */
	
	/* Determine if client is host */
	cout << "ARE YOU GOING TO HOST THIS GAME? (Y/N)\n> ";
	cin.get(isHost);
	cin.ignore (80, '\n');
	isHost = toupper(isHost);
	
	/** HOST CONNECTION/NON-HOST CONNECTION SECTION */
	if(isHost == 'Y') {
		/* Host client address and port */
		/** 
		 *  I have commented out all that don't work 
		memset((char *)&my_addr,0,sizeof(my_addr)); 
		my_addr.sin_family = AF_INET;
		my_addr.sin_addr.s_addr = INADDR_ANY;
		my_addr.sin_port = htons((u_short)HOSTPORT);
		
		memset((char *)&server_addr,0,sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons((u_short)0); */
		
		/* Socket Creation */
		/* sockid = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(sockid < 0) {
			printf("ERROR: Socket creation\n");
			exit(1);
		}*/
		
		/* Bind local address to socket */
		/*if(bind(sockid, (sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
			printf("ERROR: Bind\n");
			exit(1);
		}*/
		
		/* Make the socket a listening socket */
		/*if(listen(sockid,1) < 0) {
			printf("ERROR: Listen\n");
			exit(1);
		}*/
		
		//CC
		pid_t pid, pid2;
		int Stat;
		socklen_t alen;
		
		int sockid2;
		
		pid = fork();
		
		if(pid < 0)
		{
			cerr <<"Fork Failed" <<endl;
			exit(EXIT_FAILURE);
		}
		if(pid == 0)
		{
			pid2 = fork();
			
			if(pid2 < 0)
			{
				cerr <<"2nd Fork failed" <<endl;
				exit(EXIT_FAILURE);
			}
			if(pid2 == 0)
			{
				execvp("./Server", NULL);
				cerr <<"Server didn't start" <<endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				exit(0);
			}
		}
		else
		{
			waitpid(pid, &Stat, 0);
		}
		
		/* initialize my_addr if host*/
		memset((char *)&my_addr,0,sizeof(my_addr));
		my_addr.sin_family = AF_INET;
		my_addr.sin_addr.s_addr = INADDR_ANY;
		my_addr.sin_port = htons((u_short)PORTNUMBER);
		
		sockid2 = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(sockid2 < 0)
		{
			cerr <<"socket creation" <<endl;
			exit(EXIT_FAILURE);
		}
		
		if(bind(sockid2, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
		{
			cerr <<"bind" <<endl;
			exit(EXIT_FAILURE);
		}
		
		cout <<"Waiting for server to connect..." <<endl;
		listen(sockid2, 1);
		
		alen = sizeof(server_addr);
		
		sockid = accept(sockid2, (struct sockaddr *) &server_addr, &alen);
		
		if(sockid < 0)
		{
			cerr <<"accept server conneciton" <<endl;
			exit(EXIT_FAILURE);
		}
		
		cout <<"Waiting for players..." <<endl;
		
		
		bzero(buffer, sizeof(buffer));
		if(read(sockid, buffer, MAXSIZE) < 0)
		{
			cerr <<"read error" <<endl;
			exit(EXIT_FAILURE);
		}
		buf = buffer;
		
		commTemp.inputComm(buf);
		
		cout <<"TESTING SERVER: " <<commTemp.outputComm() <<endl;
		
		commTemp.setCommand(8,0,0);
		
		buf = commTemp.outputComm();
		if(write(sockid, buf.c_str(), strlen(buf.c_str())) < 0)
		{
			cerr <<"write error" <<endl;
			exit(EXIT_FAILURE);
		}
		
		/****************************
		 *  CURT LISTEN FOR SERVER  * 
		 ****************************/
	}
	else {
		char *host;
		string ipAddress;
		
		cout <<"Please enter in the IP address: ";
		getline(cin, ipAddress, '\n');
		
		/* initialize my_addr if connecting*/
		memset((char *)&my_addr,0,sizeof(my_addr));
		my_addr.sin_family = AF_INET;
		my_addr.sin_addr.s_addr = INADDR_ANY;
		my_addr.sin_port = htons((u_short)0);
		
		/* initialize server_addr if connecting*/
		memset((char *)server_addr.sin_zero,0,sizeof(server_addr.sin_zero));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons((u_short)PORTNUMBER);
		
		if (!ipAddress.empty())
		{
			strcpy(host,ipAddress.c_str());
		}
		else
		{
			ipAddress = "localhost";
			strcpy(host,ipAddress.c_str());
		}
		
		if((ptrh=gethostbyname(host))==0){
			fprintf(stderr,"invalid host: %s\n", host);
			exit(1);
		}
		memcpy(&server_addr.sin_addr, ptrh->h_addr, ptrh->h_length);
		
		/*creating socket if connecting*/
		sockid = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockid < 0)
		{
			perror("socket creation");
			exit(EXIT_FAILURE);
		}
		 
		/* Bind to local address if connecting*/
		if (bind(sockid, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
		{
			perror("bind");
			exit(EXIT_FAILURE);
		}
	 
		/*Connect to the server if connecting*/
		if (connect(sockid, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
		{
			perror("connect");
			exit(EXIT_FAILURE);
		}
		
		bzero(buffer, sizeof(buffer));
		if(read(sockid, buffer, MAXSIZE) < 0)
		{
			cerr <<"read error" <<endl;
			exit(EXIT_FAILURE);
		}
		buf = buffer;
		
		commTemp.inputComm(buf);
		
		cout <<"TESTING SERVER: " <<commTemp.outputComm() <<endl;
		
		commTemp.setCommand(8,0,0);
		buf = commTemp.outputComm();
		if(write(sockid, buf.c_str(), strlen(buf.c_str())) < 0)
		{
			cerr <<"write error" <<endl;
			exit(EXIT_FAILURE);
		}
		
		/****************************
		 *  CURT CONNECT TO SERVER  *
		 ****************************/
	}
	
	/* Get username */
	uname = "";
	cout << "Enter your username(previous or new): ";
	getline(cin, uname);
	while(uname.length() < 1) {
		cout << "Enter your username(previous or new): ";
		getline(cin, uname);
	}
	
	Player player(uname); //Create player and initialize all components

	while(1) {
		cout << "> ";
		getline(cin,in_str);
		type = parser.parse(in_str,cmd);
		callCmd(cmd,type,player);
		
		if(type == QUIT) {
			break;
		}
	}
	
	close(sockid);
	return 0;
}

void displayMenu() {

	cout	<< "=================================================================\n"
			<< "=         ___  ____ ___ ___ _    ____ ____ _  _ _ ___           =\n"
			<< "=         |__] |__|  |   |  |    |___ [__  |__| | |__]          =\n"
			<< "=         |__] |  |  |   |  |___ |___ ___] |  | | |             =\n"
			<< "=================================================================\n\n";
	return;
}

void displayGrid() {
	cout << "   USERNAME\n" 
		 <<	"   _________________________________________\n"
		 <<	" /|__1_|_2_|_3_|_4_|_5_|_6_|_7_|_8_|_9_|_10_|\\    ______________\n"
		 << "|-|                                         |_| /|__REFERENCE___|\\\n"               
		 << "|A|  -   -   -   -   -   -   -   -   -   -  |_|| |              | |\n"
		 << "|-|                                         |_|| | # = SHIP     | |\n"
		 << "|B|  -   -   -   -   -   -   -   -   -   -  |_|| | X = HIT      | |\n"
		 << "|-|                                         |_|| | O = MISS     | |\n"
		 << "|C|  -   -   -   -   -   -   -   -   -   -  |_|| |              | |\n"
		 << "|-|                                         |_|| | - START      | |\n"
		 << "|D|  -   -   -   -   -   -   -   -   -   -  |_|| | - CONNECT    | |\n"
		 << "|-|                                         |_|| | - COMMENT    | |\n"
		 << "|E|  -   -   -   -   -   -   -   -   -   -  |_|| | - FIRE       | |\n"
		 << "|-|                                         |_|| | - USE        | |\n"
		 << "|F|  -   -   -   -   -   -   -   -   -   -  |_|| | - PLACE      | |\n"
		 << "|-|                                         |_|| | - SHOW       | |\n"
		 << "|G|  -   -   -   -   -   -   -   -   -   -  |_|| | - BUY        | |\n"
		 << "|-|                                         |_|| | - HELP       | |\n"
		 << "|H|  -   -   -   -   -   -   -   -   -   -  |_|| | - QUIT       | |\n"
		 << "|-|                                         |_|| | - STATS      | |\n"
		 << "|I|  -   -   -   -   -   -   -   -   -   -  |_|| |              | |\n"
		 << "|-|                                         |_|| |              | |\n"
		 << "|J|  -   -   -   -   -   -   -   -   -   -  |_|| |______________| |\n"
		 << " \\|_________________________________________|/  \\|______________|/\n"
		 << "   \\_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_/\n";
}

void callCmd(int& sd, vector<string>& cmd, Cmd_t& type, Player& p) {
	if(type == START)
		p.start(sd);
	else if(type == CONNECT)
		p.connect(cmd.at(1),cmd.at(2));
	else if(type == HELP)
		p.help();
	else if(type == STATS)
		p.stats();
	else if(type == QUIT)
		p.quit();
	else if(type == FIRE)
		p.fire(sd,cmd.at(1),cmd.at(2));
	else if(type == USE)
		p.use(cmd.at(1));
	else if(type == UNLOCK)
		p.unlock(cmd.at(1));
	else if(type == PLACE)
		p.place(cmd.at(1),cmd.at(2),cmd.at(3),cmd.at(4));
	else if(type == SHOW)
		p.show(cmd.at(1));
	else if(type == BUY)
		p.buy(cmd.at(1));
	else if(type == COMMENT) {
		string message = "";
		for(unsigned int i = 1; i < cmd.size(); i++) {
			message += cmd.at(i) + " ";
		}
		p.comment(sd,message);
	}
	else {/* empty */}
}
