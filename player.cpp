#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <string>
#include "ship.h"
#include "cmdparser.h"
#include "player.h"
using namespace std;


Player::Player(string& uname) : 	coins(0),		//KB
											myTurn(false),
											connected(false),
											shipsToPlace(5), 
											shipsToSink(0), 
											username(uname), 
											wins(0), 
											losses(0) {
	for(int i = 0; i < GRIDSIZE; i++) {
		for(int j = 0; j < GRIDSIZE; j++) {
			grid[i][j] = NULL;
		}
	}

	GetPlayerInfo();
}

Player::~Player() {								//KB
	/* File structure: WINS,LOSSES,NUM_COINS */
	fstream fsout;
	string filename = username + ".txt";

	fsout.open(filename.c_str(), fstream::out, fstream::trunc);
	if(fsout.fail()) {
		printf("ERROR: Cannot open %s\n",filename.c_str());
		exit(1);
	}

	fsout	<< wins << ","
			<< losses << ","
			<< coins << ",";
		
	fsout.close();
}

int Player::Coins() const {						//KB
	return coins;
}

int Player::Wins() const {						//KB
	return wins;
}

int Player::Losses() const {					//KB
	return losses;
}

string	Player::Username() const {				//KB
	return username;
}

int Player::IsItMyTurn() const {				//KB
	return myTurn;	
}

int Player::RemainingShips() const {			//KB
	if(shipsToPlace > 0) {	/* Returns the number of ships needed before starting */
		return shipsToPlace;
	}	
	else {					/* Returns the number of ships that are still not sunk */							
		return shipsToSink;
	}
}
	
void Player::start() {							//KB (incomplete)
	if(!connected) {
		printf("You're not connected! You must connect to a host to play!\n");
		return;
	}
	
	if(shipsToPlace > 0) {
		printf("Game cannot start yet! You must place %d ships first!\n", shipsToPlace);
		return;
	}
	
	/* Send start packet */
}

void Player::connect(string& ip, string& port) {//KB (incomplete)
	if(connected) {
		printf("You're already connected! Cannot connect again!\n");
		return;
	}
	else {
		/* Need to connect */
	}
}

void Player::behost(string& port) {				//KB (incomplete)
	if(isHost) {
		printf("You're already the host!\n");
		return;
	}

	if(connected && !isHost) {
		printf("You're already connected to a host! You cannot both be hosts!\n");
		return;
	}

	/* Need to set up IP and connect to server and host server */
}

void Player::options() {								//KB (incomplete)
	printf("Options are under construction\n");
	return;
}

void Player::help() {									//KB (incomplete)
	printf("SHOW HELP\n");
	/* Display help pages */
}

void Player::stats() {									//KB
	printf("%s STATS:\n- WINS:   %d\n- LOSSES: %d\n",username.c_str(),wins,losses);
	return;
}

void Player::quit() {									//KB (incomplete)
	printf("Disconnecting...\n");
	/* Disconnect from server if not host
	   Send close packet to clients and then disconnect host */
	return;
}

void Player::fire(string& x, string& y) {				//KB (incomplete)
	printf("ATTACK!\n");
	/* BEGIN 
		FIRE 
		FIRE
		FIRE
	   END */
}

void Player::use(string& sid) {							//KB (incomplete)
	printf("USE SPECIAL\n");
}

void Player::unlock(string& sid) {						//KB (incomplete)
	printf("UNLOCK SPECIAL\n");
}

void Player::place(string& id, string& x, string&y, string& pos) {		//KB (incomplete)
	printf("PLACE SHIP\n");
}

void Player::show(string& toShow) {						//KB (incomplete)
	printf("SHOW SOMETHING\n");
}

void Player::buy(string& sid) {							//KB (incomplete)
	printf("BUY SOMETHING\n");
}

void Player::WritePlayerInfo() {				//KB
	/* File structure: WINS,LOSSES,NUM_COINS */
	fstream fsin;
	string filename = username + ".txt";
	string nwins, nlosses, ncoins;

	fsin.open(filename.c_str(), fstream::in);
	if(fsin.fail()) {
		fstream fsout;
		
		fsout.open(filename.c_str(), fstream::out, fstream::trunc);
		if(fsout.fail()) {
			printf("ERROR: Cannot open %s\n",filename.c_str());
			exit(1);
		}

		fsout << "0,0,0,";
		
		fsout.close();
	}
	else {
		getline(fsin,nwins,',');
		getline(fsin,nlosses,',');
		getline(fsin,ncoins,',');

		wins = atoi(nwins.c_str());
		losses = atoi(nlosses.c_str());
		coins = atoi(ncoins.c_str());
	}

	fsin.close();
}

int Player::SinkShip() {						//KB
	return shipsToSink--;
}
