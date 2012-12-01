#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include "cmdparser.h"
#include "ship.h"
#include "player.h"
using namespace std;


#define GRID_TOP		"    _______________________________________\n  /|_1_|_2_|_3_|_4_|_5_|_6_|_7_|_8_|_9_|_10|\\\n"
#define A_ROW			" |_|                                       |\\\n |A|"
#define B_ROW			" |_|                                       |\\\n |B|"
#define C_ROW			" |_|                                       |\\\n |C|"
#define D_ROW			" |_|                                       |\\\n |D|"
#define E_ROW			" |_|                                       |\\\n |E|"
#define F_ROW			" |_|                                       |\\\n |F|"
#define G_ROW			" |_|                                       |\\\n |G|"
#define H_ROW			" |_|                                       |\\\n |H|"
#define I_ROW			" |_|                                       |\\\n |I|"
#define J_ROW			" |_|                                       |\\\n |J|"
#define GRID_BOTTOM		"  \\|_______________________________________|\\\n    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n\n"
#define NOSHIP			" - "
#define END_ROW			"|\\\n"
#define HIT				" X "
#define SHIP			" # "
#define MISS			" O "


/** Displays the Battleship menu with basic command listing for startup */
void displayMenu();

void displayGrid();

void callCmd(vector<string>& cmd, Cmd_t& type, Player& p);

int main() {			//KB
	string in_str;
	Cmd_t type;
	CmdParser parser;
	vector<string> cmd;
	Player player;

	displayMenu(); //Display title screen and menu
	cout << "> ";

	getline(cin,in_str);
	type = parser.parse(in_str,cmd);
	callCmd(cmd,type,player);

	/* NEED TO PARSE OUT INPUT use str.find()*/
	/* CONNECT */
	/* HOST*/
	/* DISPLAY HELP INFO */

	return 0;
}

void displayMenu() { //KB

	cout	<< "=================================================================\n"
			<< "=         ___  ____ ___ ___ _    ____ ____ _  _ _ ___           =\n"
			<< "=         |__] |__|  |   |  |    |___ [__  |__| | |__]          =\n"
			<< "=         |__] |  |  |   |  |___ |___ ___] |  | | |             =\n"
			<< "=================================================================\n"
			<< "=================================================================\n"
			<< "=  ARE YOU HOSTING THE GAME?                                    =\n"
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
		 << "|-|                                         |_|| | - BEHOST     | |\n"
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
	switch(type) {
		case START:
			p.start();
			break;
		case CONNECT:
			p.connect(cmd.at(1),cmd.at(2));
			break;
		case BEHOST:
			p.behost(cmd.at(1));
			break;
		case OPTIONS:
			p.options();
			break;
		case HELP:
			p.help();
			break;
		case STATS:
			p.stats();
			break;
		case QUIT:
			p.quit();
			break;
		case FIRE:
			p.fire(cmd.at(1),cmd.at(2));
			break;
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
		default:
			break;
	};
}