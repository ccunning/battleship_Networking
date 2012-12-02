/**********************************************************************
 * 
 * PROJECT: BATTLESHIP
 * AUTHORS: KENNETH BOGNER
 * 			CURT CUNNING
 * CREATED: NOVEMBER 2012
 * 
 **********************************************************************/

//This class allows for easy transmition and parsing of the protocol
//CC

#ifndef BATSHPPRT
#define BATSHPPRT
 
#include <sstream>
#include <string>

using namespace std;
 
enum Packet_t {
	ACK = 0,
	START,
	FIRE,
	QUIT
};
 
class BaShPr //creates a class for the protocol commands
{
public:
	BaShPr();
    BaShPr(int nCommand, int nOption1, int nOption2);
 
    void getCommand(int & nCommand, int & nOption1, int & nOption2);
    void setCommand(int nCommand, int nOption1, int nOption2);
    
    string outputComm(void);
    void inputComm(const string & nBScomm);

private:
    int command;
    int option1;
    int option2;
};
 
BaShPr::BaShPr() //initialize as all zeros
{
	command = 0;
	option1 = 0;
	option2 = 0;
}

BaShPr::BaShPr(int nCommand, int nOption1, int nOption2) //initialize with 3 ints as the command and arguments
{
	command = nCommand;
	option1 = nOption1;
	option2 = nOption2;
}

void BaShPr::getCommand(int & nCommand, int & nOption1, int & nOption2) //get the current values for the command and two arguments
{
	nCommand = command;
	nOption1 = option1;
	nOption2 = option2;
	
	return;
}

void BaShPr::setCommand(int nCommand, int nOption1, int nOption2) //set the command and arguments for sending
{
	command = nCommand;
	option1 = nOption1;
	option2 = nOption2;
}

string BaShPr::outputComm(void) //outputs the three variables as a string for the protocol as specified in order to send across the socket
{
	string temp;
	stringstream ss;
	
	ss.clear();
	ss.str("");
	
	ss << "(" << command << "," << option1 << "," << option2 << ")";
	
	ss >> temp;
	
	return temp;
}

void BaShPr::inputComm(const string & nBScomm) //input the string into the object
{
	char temp;
	stringstream ss;
	
	ss.clear();
	ss.str("");
	
	ss << nBScomm;
	
	ss >> temp >> command >> temp >> option1 >> temp >> option2 >> temp;
	
	return;
}

#endif
