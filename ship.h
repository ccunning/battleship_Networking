#ifndef SHIP_H
#define SHIP_H

#define AIRCRAFTCARRIER		5
#define BATTLESHIP			4
#define CRUISER				3
#define SUBMARINE			3
#define PATROLBOAT			2


class Ship {	//KB
	bool isHit;

public:
	Ship();
	~Ship();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const = 0;

protected:
	virtual void DecreaseInstance() = 0;
};

class AircraftCarrier : public Ship {	//KB
	static int maxInstances;

public:
	AircraftCarrier();
	~AircraftCarrier();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const;

protected:
	virtual void DecreaseInstance();
};

class Battleship : public Ship {		//KB
	static int maxInstances;

public:
	Battleship();
	~Battleship();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const;

protected:
	virtual void DecreaseInstance();
};

class Cruiser : public Ship {			//KB
	static int maxInstances;

public:
	Cruiser();
	~Cruiser();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const;

protected:
	virtual void DecreaseInstance();
};

class Submarine : public Ship {			//KB
	static int maxInstances;

public:
	Submarine();
	~Submarine();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const;

protected:
	virtual void DecreaseInstance();
};

class PatrolBoat : public Ship {		//KB
	static int maxInstances;

public:
	PatrolBoat();
	~PatrolBoat();
	bool IsHit() const;
	void HitShip();
	virtual int AvailableShips() const;

protected:
	virtual void DecreaseInstance();
};

#endif