#include "ipconfig.h"

string IP::getip()
{
	string line;
	ifstream IPFile;
	int offset;
	char* search0 = "IPv4 µØÖ· . . . . . . . . . . . . :";

	system("ipconfig > ip.txt");

	IPFile.open("ip.txt");
	if (IPFile.is_open())
	{
		while (!IPFile.eof())
		{
			getline(IPFile, line);
			if ((offset = line.find(search0, 0)) != string::npos)
			{
				line.erase(0, 39);
				cout << line << endl;
				ipv4 = line;
				IPFile.close();
				return line;
			}
		}
	}
	return 0;
}