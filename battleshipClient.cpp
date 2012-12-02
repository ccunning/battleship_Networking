#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "cmdparser.h"
#include "ship.h"
#include "player.h"
using namespace std;

#define NONHOSTPORT	6683
#define HIT				" X "
#define SHIP			" # "
#define MISS			" O "


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
	sockaddr_in * my_addr, server_addr;
	hostent *ptrh;

	displayMenu(); /* Display title screen and menu */
	
	/* Determine if client is host */
	cout << "ARE YOU GOING TO HOST THIS GAME? (Y/N)\n> ";
	cin.get(isHost);
	isHost = toupper(isHost);
	if(isHost == 'Y') {
		/****************************
		 *  CURT LISTEN FOR SERVER  * 
		 ****************************/
	}
	else {
		/****************************
		 *  CURT CONNECT TO SERVER  *
		 ****************************/
	}
	
	/* Get username */
	uname = "";
	cout << "Enter your username(previous or new): ";
	cin >> uname;
	while(uname.length() < 1) {
		cout << "Enter your username(previous or new): ";
		cin >> uname;
	}
	
	Player player(uname);

	getline(cin,in_str);
	type = parser.parse(in_str,cmd);
	callCmd(cmd,type,player);

	/* NEED TO PARSE OUT INPUT use str.find()*/
	/* CONNECT */
	/* HOST */
	/* DISPLAY HELP INFO */

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
		/*


		case USE:
			p.use(cmd.at(1));
			break;
		case UNLOCK:
			p.unlock(cmd.at(1));
			break;
		case PLACE:
			p.place(cmd.at(1),cmd.at(2),cmd.at(3),cmd.at(4));
			break;
		case SHOW:
			p.show(cmd.at(1));
			break;
		case BUY:
			p.buy(cmd.at(1));
			break;
		case COMMENT:
			string message = "";
			for(int i = 1; i < cmd.size(); i++) {
				message += cmd.at(i) + " ";
			}
			p.comment(message);
			break;
		case CMDERR
		default:
			break;
	};*/
}
