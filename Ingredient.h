#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "Ingredient.h"
#include "Menu.h"

using namespace std;


class Ingredient
{
private:
	string title;
	float price;
	int count;
	friend ostream& operator<<(ostream&, const Ingredient&);
	friend void operator<<(ofstream&, const Ingredient&);
public:
	Ingredient()
		:title("NULL"), price(0), count(0) {}
	Ingredient(string title, float price, int count)
		:title(title), price(price), count(count) {}

	Ingredient(ifstream& file)
	{
		file >> title;
		file >> price;
		file >> count;
	}

	bool IsEmpty()const { return count == 0; }
	float Price()const { return price; }
	string& Title() { return title; }
	void Show()const { cout << title << "\n\tX" << count << "\n\t\t" << price << "grn" << endl; }

	void Constructor()
	{
		Show();
		cout << "Edit title?"<<endl;
		if (_getch() == 13)
		{
			cout << "\nEnter new title of product:"; 
			while(title=="")
			getline(cin,title);
		}
		cout << "Edit count?"<<endl;
		if (_getch() == 13)
		{
			cout << "\nEnter new count number of product:"; cin >> count;
			cin.clear();
		}
		cout << "Edit price?"<<endl;
		if (_getch() == 13)
		{
			cout << "\nEnter new price number of product:"; cin >> count;
			cin.clear();
		}

		//=================================================
	}

	void operator--(int) { --count; }
	void operator--() { --count; }
	void Update() { count = 100; }
};
ostream& operator<<(ostream& cout, const Ingredient& ptr)
{
	cout << ptr.title;
	return cout;
}
void operator<<(ofstream& file, const Ingredient& ptr)
{
	file << "" << ptr.title << " " << ptr.price << " " << ptr.count << endl;
}