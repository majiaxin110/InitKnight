
#ifndef IPCONFIG__
#define IPCONFIG__

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class IP
{
public:
	IP() {};
	~IP() {};
	string getip();
private:
	string ipv4;
};

#endif // !IPCONFIG__

