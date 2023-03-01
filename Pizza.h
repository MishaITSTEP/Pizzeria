#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>

#include "Ingredient.h"
#include "IngredientType.h"
#include "Menu.h"
using namespace std;
//=================================================
class Pizza
{
private:
	string Name;
	struct Node
	{
		int Type = 0;
		int Num = 0;
		/*Node() :Type(0), Num(0) {}
		Node(int Type = 0, int Num = 0) : Type(Type), Num(Num) {}
		Node(Node& node) :Type(node.Type), Num(node.Num) {  }*/
		/*ostream& operator<<(ostream& cout)
		{
			cout << this->Type << " " << this->Num;
			return cout;
		}*/
	};
	vector<Node> ing;
	float price;
	//=================================================
	friend void operator<<(ofstream&, const Pizza&);
	friend ostream& operator<<(ostream&, const Pizza&);
	//=================================================
public:
	Pizza() :Name("NULL_NAME"), price(0)
	{};
	Pizza(ifstream& file) :price(0)
	{
		int count;
		file >> count;
		getline(file, Name);
		for (size_t i = 0; i < count; i++)
		{
			Node ptr;
			file >> ptr.Type;
			file >> ptr.Num;
			ing.push_back(ptr);
			//price += ingredient[ptr.Type][ptr.Num].Price();
			price += 10;
		}
	}
	static Pizza& Constructor(vector<IngredientType>& ingr)
	{

	}

	//void Constructor()
	void Edit(vector<IngredientType>& ingr)
	{

		//ingr[0].Show();
		string Name;
		float value;
		//=================================================
		cout << "Edit title?" << endl;
		if (_getch() == 13)
		{
			cout << "\nEnter new title of product: "; getline(cin, Name);
		}
		//=================================================
		Node ptr;
		cout << "Edit component?" << endl;

		if (_getch() == 13)
		{
			ing.clear();
			while (ptr.Type != -1)
			{
				ptr.Type = Menu<IngredientType>::Show(ingr);
				if (ptr.Num != -1)
				{
					ingr[ptr.Type];
					ptr.Num = ingr[ptr.Type].Choise(ptr.Num);
					if (ptr.Num != -1)ing.push_back({ ptr });
					Show();
				}
			}
		}
	}
	string& NameP() { return Name; }
	//=================================================
	void Show()
	{
		cout << *this << endl;
	}
};
//=================================================
ostream& operator<<(ostream& cout, const Pizza& pizza)
{
	cout << pizza.Name << " : " << pizza.price << "grn";
	return cout;
}
void operator<<(ofstream& file, const Pizza& pizza)
{
	file << pizza.ing.size() << pizza.Name;
	for (Pizza::Node node : pizza.ing)
	{
		file << node.Type << ' ' << node.Num << endl;
	}
};