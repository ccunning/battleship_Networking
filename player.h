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


#define GRIDSIZE 			10


class Player {			
	Ship *	grid[GRIDSIZE][GRIDSIZE];
	int		coins;
	bool	myTurn;
	bool	connected;
	int		shipsToPlace;
	int		shipsToSink;
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
	int		RemainingShips() const;
	
	/* Functions to handle the commands
			Returns 0 for no error
			Returns -1 for error, function determines specific error */
	void	start();
	void	connect(string& ip, string& port);
	void	help();
	void	stats();
	void	quit();
	void	fire(string& x, string& y);
	void	use(string& sid);
	void	unlock(string& sid);
	void	place(string& id, string& x, string& y, string& pos);
	void	show(string& toShow);
	void	buy(string& sid);
	void	comment(string& message);
};

#endif
