#ifndef PLAYER_H
#define PLAYER_H

#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <unistd.h>
#include <ctime>
#include <cerrno>
#include <string>
#include <cctype>
#include <cmath>
#include <stddef.h>
//#include <netdb.h>
#include <stack>
#include <algorithm>
#include <queue>
#include <list>
#include "ship.h"
#include "cmdparser.h"
using namespace std;


#define GRIDSIZE 			10


class Player {			//KB
	Ship *	grid[GRIDSIZE][GRIDSIZE];
	int		coins;
	bool	myTurn;
	bool	connected;
	bool	isHost;
	int		shipsToPlace;
	int		shipsToSink;
	int		wins;
	int		losses;
	string	username;

	void	WritePlayerInfo();
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
	void	behost(string& port);
	void	options();
	void	help();
	void	stats();
	void	quit();
	void	fire(string& x, string& y);
	void	use(string& sid);
	void	unlock(string& sid);
	void	place(string& id, string& x, string& y, string& pos);
	void	show(string& toShow);
	void	buy(string& sid);
};

#endif