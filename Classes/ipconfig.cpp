#include "ipconfig.h"

string IP::getip()//获取IP
{
	string line;
	ifstream IPFile;//利用文件流读取保存
	int offset;
	char* search0 = "IPv4 地址 . . . . . . . . . . . . :";

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