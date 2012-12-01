#ifndef CMDPARSER_CPP
#define CMDPARSER_CPP

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <cstdio>
#include "cmdparser.h"
using namespace std;

Commands CmdParser::commands = {
	{"start","connect","help","stats","quit","fire","use","unlock","place","show","buy","comment","unknown"},
	{0,2,0,0,0,2,1,1,4,1,1,1,0}};

Cmd_t CmdParser::parse(string& input, vector<string>& args) {
	unsigned int i,j,front,end;
	
	args.clear(); /* Clear the vector to eliminate possible leftover arguments */

	front = end = 0;
	for(i=0; i < input.length(); i++) {
		input.at(i) = tolower(input.at(i));	/* Allow for case-insensitivity */
		if(isspace(input.at(i))) {	
			end = i;
			args.push_back(input.substr(front,(end-front))); /* Push the 'token' into the vector */
			while(isspace(input.at(i+1))) {
				i++;
			}
			front = i + 1;
		}
	}
	args.push_back(input.substr(front,(input.length()-front)));	/* Get the last 'token' */
	
	j = 0;
	while(j < NCMDS) {	/* Compare first element in the vector to possible commands */
		if(args.at(0).compare(commands.cmds[j]) == 0) {
			break;
		}
		j++;
	}

	// NEED TO DISPLAY ERRORS AND HANDLE ARGUMENTS

	switch(j) {
		case 0:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: start: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return START;
		case 1:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: connect: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return CONNECT;
		case 2:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: help: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return HELP;
		case 3:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: stats: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return STATS;
		case 4:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: quit: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return QUIT;
		case 5:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: fire: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return FIRE;
		case 6:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: use: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return USE;
		case 7:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: unlock: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return UNLOCK;
		case 8:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: place: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return PLACE;
		case 9:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: show: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return SHOW;
		case 10:
			if( args.size() != (commands.nargs[j]+1) ) {
				printf("ERROR: buy: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return BUY;
		case 11:
		`	if( args.size() == 0) {
				printf("ERROR: comment: arguments given (%d) arguments needed (%d)\n", args.size()-1, commands.nargs[j]);
				return CMDERR;
			}
			return COMMENT;
		default:
			printf("ERROR: Unknown command\n");
			return UNKNOWN;
	}
}
	
#endif
