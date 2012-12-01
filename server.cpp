#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <iostream>
#include <string>
//#include <stdlib.h>

#include "battleshipprotocol.h"

using namespace std;

int main()
{
	struct sockaddr_in SAddr;
	struct sockaddr_in C1Addr;
	struct sockaddr_in C2Addr;
	
	BaShPr temp;
	
	int c1socket, c2socket;
	int alen;
	int i, j, k, n;
	
	int commTemp, op1Temp, op2Temp;
	
	string buf;
	
	commTemp = 1;
	op1Temp = 9;
	op2Temp = 2;
	
	temp.setCommand(commTemp, op1Temp, op2Temp);
	
	buf = temp.outputComm();
	
	cout << buf <<endl;
	
	return 0;
}
	
	
	
