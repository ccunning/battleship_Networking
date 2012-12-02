/**********************************************************************
 * 
 * PROJECT: BATTLESHIP
 * AUTHORS: KENNETH BOGNER
 * 			CURT CUNNING
 * CREATED: NOVEMBER 2012
 * 
 **********************************************************************/

#ifndef PLAYER_CPP
#define PLAYER_CPP

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


Player::Player():	coins(0),
					myTurn(false),
					shipsToPlace(5),
					shipsToSink(5),
					shipsRemaining(0),
					username("Captain"),
					wins(0),
					losses(0) {
	for(int i = 0; i < GRIDSIZE; i++) {
		for(int j = 0; j < GRIDSIZE; j++) {
			myGrid[i][j] = NULL;
			theirGrid[i][j] = NULL;
		}
	}

	GetPlayerInfo();				
}

Player::Player(string& uname) : coins(0),
								myTurn(false),
								shipsToPlace(5), 
								shipsToSink(5), 
								shipsRemaining(0),
								username(uname), 
								wins(0), 
								losses(0) {
	for(int i = 0; i < GRIDSIZE; i++) {
		for(int j = 0; j < GRIDSIZE; j++) {
			myGrid[i][j] = NULL;
			theirGrid[i][j] = NULL;
		}
	}

	GetPlayerInfo();
}

Player::~Player() {								
	/* File structure: WINS,LOSSES,NUM_COINS */
	fstream fsout;
	string filename = username + ".txt";

	fsout.open(filename.c_str(), fstream::out | fstream::trunc);
	if(fsout.fail()) {
		printf("ERROR: Cannot open %s\n",filename.c_str());
		exit(1);
	}

	fsout	<< wins << ","
			<< losses << ","
			<< coins << ",";
		
	fsout.close();
}

int Player::Coins() const {						
	return coins;
}

int Player::Wins() const {						
	return wins;
}

int Player::Losses() const {
	return losses;
}

string	Player::Username() const {
	return username;
}

int Player::IsItMyTurn() const {
	return myTurn;	
}

int Player::MyRemainingShips() const {
	if(shipsToPlace > 0) {	/* Returns the number of ships needed before starting */
		return shipsToPlace;
	}	
	else {					/* Returns the number of ships that are still not sunk */							
		return shipsRemaining;
	}
}

int Player::TheirRemainingShips() const {
	return shipsToSink;
}

Ship* Player::GetMyContentAtCoords(int& x, int& y) const {
	if(x < 1 || x > GRIDSIZE) {
		printf("ERROR: The x coordinate must be between 1 and %d, not %d\n", GRIDSIZE, x);
		return NULL;
	}
	if(y < 1 || y > GRIDSIZE) {
		printf("ERROR: The y coordinate must be between 1 and %d, not %d\n", GRIDSIZE, y);
		return NULL;
	}
	
	return myGrid[x-1][y-1];
}

Ship* Player::GetTheirContentAtCoords(int& x, int& y) const {
	if(x < 1 || x > GRIDSIZE) {
		printf("ERROR: The x coordinate must be between 1 and %d, not %d\n", GRIDSIZE, x);
		return NULL;
	}
	if(y < 1 || y > GRIDSIZE) {
		printf("ERROR: The y coordinate must be between 1 and %d, not %d\n", GRIDSIZE, y);
		return NULL;
	}
	
	return theirGrid[x-1][y-1];
}
	
void Player::start(int& sd) {							//KB (incomplete)
	if(shipsToPlace > 0) {
		printf("Game cannot start yet! You must place %d ships first!\n", shipsToPlace);
		return;
	}
	
	/* Send start packet */
}

void Player::connect(string& ip, string& port) {	//KB (incomplete)possibly unnecessary
	printf("CONNECT");
}

void Player::help() {									//KB (incomplete)
	printf("SHOW HELP\n");
	/* Display help pages */
}

void Player::stats() {									//KB
	printf("%s stats:\n- WINS:   %d\n- LOSSES: %d\n",username.c_str(),wins,losses);
	return;
}

void Player::quit() {									//KB
	printf("Disconnecting...\n");
	return;
}

void Player::fire(int& sd, string& x, string& y) {				//KB (incomplete)
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
	if(toShow.compare("mine")) {
		return;
	}
	if(toShow.compare("opp")) {
		return;
	}
	if(toShow.compare("store")) {
		return;
	}
	
	printf("You must type mine, opp, or store to display");
}

void Player::buy(string& sid) {							//KB (incomplete)
	printf("BUY SOMETHING\n");
}

void Player::comment(int& sd, string& message) {
	printf("%s\n",message.c_str());
}

void Player::GetPlayerInfo() {	
	/* File structure: WINS,LOSSES,NUM_COINS */
	fstream fsin;
	string filename = username + ".txt";
	string nwins, nlosses, ncoins;

	fsin.open(filename.c_str(), fstream::in);
	if(fsin.fail()) {
		fstream fsout;
		
		fsout.open(filename.c_str(), fstream::out | fstream::trunc);
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

int Player::SinkShip() {
	return shipsRemaining--;
}

#endif
