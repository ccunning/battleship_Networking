/**********************************************************************
 * 
 * PROJECT: BATTLESHIP
 * AUTHORS: KENNETH BOGNER
 * 			CURT CUNNING
 * CREATED: NOVEMBER 2012
 * 
 **********************************************************************/

#ifndef CMDPARSER_H
#define CMDPARSER_H

/*
	COMMANDS AND ARGUMENTS 
	<Req> = Argument
	(...) = Note About Argument
		> start
		> connect <IP> <port#>
		> help
		> stats
		> quit
		> fire <x coord (e.g A B C...J)> <y coord (e.g 1 2 3...10)>
		> use <special ID# (e.g. Normal Fire = 0)>
		> unlock <special ID#> (Use only for testing, else it constitutes cheating :P)
		> place <ship ID#> <x coord (starting x coord)> <y coord (starting y coord)> <V OR H (V for vertical, H for horizontal)>
		> show <mine OR opp OR store> (either type mine for your grid or opp for opponents grid or store for the items available to purchase)
		> buy <special ID#>
		> comment <message>
*/

#include <string>
#include <vector>
using namespace std;

#define NCMDS	14

enum Cmd_t { //Enumeration to allow easier access to commands from string array
	CMDERR = -1,
	START = 0,
	CONNECT,
	HELP,
	STATS,
	QUIT,
	FIRE,
	USE,
	UNLOCK,
	PLACE,
	SHOW,
	BUY,
	COMMENT,
	UNKNOWN
};

struct Commands {
	string const cmds[NCMDS]; 	//string commands
	int const nargs[NCMDS]; 	//number of arguments for each command (separated by location in cmds)
};

class CmdParser {
	static struct Commands commands;

public:
	CmdParser() {}
	~CmdParser() {}
	
	Cmd_t parse(string& input, vector<string>& args); /* Parses out the input, but no validation of content */
};
	
#endif
