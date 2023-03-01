#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>

#include "Ingredient.h"
#include "Menu.h"

using namespace std;


class IngredientType
{
private:
	string title;
	vector<Ingredient> ingredient;
	friend ostream& operator<<(ostream&, IngredientType&);
	friend void operator<<(ofstream&, IngredientType&);
public:
	IngredientType() :title("NULL") {}
	IngredientType(ifstream& file)
	{
		int count;
		file >> count;
		getline(file, title);
		for (size_t i = 0; i < count; i++)
		{
			Ingredient ptr(file);;
			ingredient.push_back(ptr);
		}
	}

	int Choise(int selecte = 0, string Name = "INGREDIENTS")
	{
		vector<string>str;
		for (Ingredient s : ingredient)
		{
			str.push_back(s.Title());
		}
		return Menu<string>::Show(str, Name, selecte);
	}
	string& Title() { return title; }
	Ingredient& operator[](int i) { return ingredient[i]; }

	void AddNew(string title, float value, int count, int insert = 0)
	{
		ingredient.insert(ingredient.begin() + insert, Ingredient(title, value, count));
	}
	void Delete(int num) { if (!ingredient.empty())ingredient.erase(ingredient.begin() + num); }

	void Show()
	{
		cout << " >> Type: " << title << endl;
		for (int i = 0; i < ingredient.size(); i++)
		{
			cout << i + 1 << ')';
			ingredient[i].Show();
		}
		cout << endl;
	}
};
ostream& operator<<(ostream& cout, IngredientType& ingr)
{
	cout << ingr.title << ": ";
	for (size_t i = 0; i < ingr.ingredient.size(); i++)
		cout << ingr.ingredient[i] << ", ";
	return cout;
}
void operator<<(ofstream& file, IngredientType& ingr)
{
	file << ingr.ingredient.size() << ingr.title << endl;
	for (Ingredient s : ingr.ingredient) { file << s; }
}
