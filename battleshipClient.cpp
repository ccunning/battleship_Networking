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
using namespace std;


#define HOSTPORT	6683
#define NONHOSTPORT	6684


/* Displays the Battleship menu with basic command listing for startup */
void displayMenu();

void displayGrid();

/* Calls the appropriate command function that is part of the Player class */
void callCmd(vector<string>& cmd, Cmd_t& type, Player& p);

int main() {
	string in_str, uname;
	Cmd_t type;
	CmdParser parser;
	vector<string> cmd;
	char isHost;
	int sockid;
	sockaddr_in my_addr, server_addr;
	hostent *ptrh;

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
		 */
		memset((char *)&my_addr,0,sizeof(my_addr)); 
		my_addr.sin_family = AF_INET;
		my_addr.sin_addr.s_addr = INADDR_ANY;
		my_addr.sin_port = htons((u_short)HOSTPORT);
		
		memset((char *)&server_addr,0,sizeof(server_addr));
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons((u_short)0);
		
		/* Socket Creation */
		sockid = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(sockid < 0) {
			printf("ERROR: Socket creation\n");
			exit(1);
		}
		
		/* Bind local address to socket */
		if(bind(sockid, (sockaddr *)&my_addr, sizeof(my_addr)) < 0) {
			printf("ERROR: Bind\n");
			exit(1);
		}
		
		/* Make the socket a listening socket */
		if(listen(sockid,1) < 0) {
			printf("ERROR: Listen\n");
			exit(1);
		}
	}
	else {
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

void callCmd(vector<string>& cmd, Cmd_t& type, Player& p) {
	if(type == START)
		p.start();
	else if(type == CONNECT)
		p.connect(cmd.at(1),cmd.at(2));
	else if(type == HELP)
		p.help();
	else if(type == STATS)
		p.stats();
	else if(type == QUIT)
		p.quit();
	else if(type == FIRE)
		p.fire(cmd.at(1),cmd.at(2));
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
		p.comment(message);
	}
	else {/* empty */}
}
