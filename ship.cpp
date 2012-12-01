#ifndef SHIP_CPP
#define SHIP_CPP

#include "ship.h"


int AircraftCarrier::maxInstances = AIRCRAFTCARRIER;
int Battleship::maxInstances = BATTLESHIP;
int Cruiser::maxInstances = CRUISER;
int Submarine::maxInstances = SUBMARINE;
int PatrolBoat::maxInstances = PATROLBOAT;

/* SHIP CLASS--------------------------------------- */
Ship::Ship() : isHit(false) {
	/* Intentionally empty */
}

Ship::~Ship() {
	/* Intentionally empty */
}

bool Ship::IsHit() const {
	return isHit;
}

void Ship::HitShip() {
	isHit = true;
}
/* ------------------------------------------------- */

/* AIRCRAFT CARRIER CLASS--------------------------- */
AircraftCarrier::AircraftCarrier() : Ship() {
	if(maxInstances > 0) {
		DecreaseInstance();
	} 
	else {
		HitShip();
	}
}

AircraftCarrier::~AircraftCarrier() {
	maxInstances++;
}
	
bool AircraftCarrier::IsHit() const {
	return Ship::IsHit();
}

void AircraftCarrier::HitShip() {
	Ship::HitShip();
}

int AircraftCarrier::AvailableShips() const {
	return maxInstances;
}

void AircraftCarrier::DecreaseInstance() {
	if(maxInstances > 0)
		maxInstances--;
}
/* ------------------------------------------------- */

/* BATTLESHIP CLASS--------------------------------- */
Battleship::Battleship() : Ship() {
	if(maxInstances > 0) {
		DecreaseInstance();
	} 
	else {
		HitShip();
	}
}

Battleship::~Battleship() {
	maxInstances++;
}
	
bool Battleship::IsHit() const {
	return Ship::IsHit();
}

void Battleship::HitShip() {
	Ship::HitShip();
}

int Battleship::AvailableShips() const {
	return maxInstances;
}

void Battleship::DecreaseInstance() {
	if(maxInstances > 0)
		maxInstances--;
}
/* ------------------------------------------------- */

/* CRUISER CLASS------------------------------------ */
Cruiser::Cruiser() : Ship() {
	if(maxInstances > 0) {
		DecreaseInstance();
	} 
	else {
		HitShip();
	}
}

Cruiser::~Cruiser() {
	maxInstances++;
}
	
bool Cruiser::IsHit() const {
	return Ship::IsHit();
}

void Cruiser::HitShip() {
	Ship::HitShip();
}

int Cruiser::AvailableShips() const {
	return maxInstances;
}

void Cruiser::DecreaseInstance() {
	if(maxInstances > 0)
		maxInstances--;
}
/* ------------------------------------------------- */

/* SUBMARINE CLASS---------------------------------- */
Submarine::Submarine() : Ship() {
	if(maxInstances > 0) {
		DecreaseInstance();
	} 
	else {
		HitShip();
	}
}

Submarine::~Submarine() {
	maxInstances++;
}
	
bool Submarine::IsHit() const {
	return Ship::IsHit();
}

void Submarine::HitShip() {
	Ship::HitShip();
}

int Submarine::AvailableShips() const {
	return maxInstances;
}

void Submarine::DecreaseInstance() {
	if(maxInstances > 0)
		maxInstances--;
}
/* ------------------------------------------------- */

/* PATROL BOAT CLASS-------------------------------- */
PatrolBoat::PatrolBoat() : Ship() {
	if(maxInstances > 0) {
		DecreaseInstance();
	} 
	else {
		HitShip();
	}
}

PatrolBoat::~PatrolBoat() {
	maxInstances++;
}
	
bool PatrolBoat::IsHit() const {
	return Ship::IsHit();
}

void PatrolBoat::HitShip() {
	Ship::HitShip();
}

int PatrolBoat::AvailableShips() const {
	return maxInstances;
}

void PatrolBoat::DecreaseInstance() {
	if(maxInstances > 0)
		maxInstances--;
}
/* ------------------------------------------------- */

#endif