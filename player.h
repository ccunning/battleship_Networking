/**********************************************************************
 * 
 * PROJECT: BATTLESHIP
 * AUTHORS: KENNETH BOGNER
 * 			CURT CUNNING
 * CREATED: NOVEMBER 2012
 * 
 **********************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <stddef.h>
#include <netdb.h>
#include <stack>
#include <string>
#include <algorithm>
#include <queue>
#include <list>
#include "ship.h"
#include "cmdparser.h"
using namespace std;


#define GRIDSIZE 	10


class Player {			
	Ship *	myGrid[GRIDSIZE][GRIDSIZE];
	Ship *	theirGrid
	int		coins;
	bool	myTurn;
	int		shipsToPlace;
	int		shipsToSink;
	int		shipsRemaining;
	string	username;
	int		wins;
	int		losses;

	void	GetPlayerInfo();
	int		SinkShip();

public:
	Player();
	Player(string& uname);
	~Player();

	int		Coins() const;
	int		Wins() const;
	int		Losses() const;
	string	Username() const;
	int		IsItMyTurn() const;
	int		MyRemainingShips() const;
	int		TheirRemainingShips() const;
	Ship*	GetMyContentAtCoords(int& x, int& y) const;
	Ship*	GetTheirContentAtCoords(int& x, int& y) const;
	
	/* Functions to handle the commands
			Returns 0 for no error
			Returns -1 for error, function determines specific error */
	void	start(int& sd);
	void	connect(string& ip, string& port);
	void	help();
	void	stats();
	void	quit();
	void	fire(int& sd, string& x, string& y);
	void	use(string& sid);
	void	unlock(string& sid);
	void	place(string& id, string& x, string& y, string& pos);
	void	show(string& toShow);
	void	buy(string& sid);
	void	comment(int& sd, string& message);
};

#endif
