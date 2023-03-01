#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	string filename = "Misha";
	ifstream file(filename + ".txt");
	if (file)
	{
		int count = 0;
		file >> count;
		for (int i = 0; i < count; i++)
		{
			string a, b = "";
			getline(file, a);
			cout << a << endl;
		}
		file.close();
	}
	else cout << "Error file reading.";
}