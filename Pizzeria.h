#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <vector>

#include "IngredientType.h"
#include "Pizza.h"
#include "Menu.h"
#define CLEAR_CONSOLE system("cls")
using namespace std;

//=================================================
class Pizzeria
{
private:
	string Name;
	string language;
	vector<IngredientType> ingredient;
	vector<Pizza> _Pizza;
public:
	Pizzeria(string Name)
		:Name(Name), language("")
	{};
	//=================================================
	void menu()
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		language = "eng";
		//switch (Menu<string>::Show({ "English","Ураїнська" }))
		//{
		//case 0:
		//	language = "eng";
		//	break;
		//case 1:
		//	language = "ua";
		//	break;
		//default:
		//	cout << "[CLOSED]" << endl;
		//	return;
		//	break;
		//}
		Loaddataing(); Loaddatapizza();
		Savedataing(); Savedatapizza();
		ShowIngr(); ShowPizza();
		_getch();
		int select = 0;
		do
		{
			select = Menu<string>::Show({
				//[#] - error,[ ] - norm
				/* # 0 */ "&Edit pizza",
				/* # 1 */ "&Edit product",
				/*   2 */ "&Save database pizzas",
				/*   3 */ "&Save database ingredients",
				/*   4 */ "&Load data pizza from file",
				/*   5 */ "&Load data ingredients from file",
				/*   6 */ "&Show list of pizza",
				/*   7 */ "&Show list of ingredients",
				/* # 8 */ "-Found pizza of ingredient", }, "PIZZERIA MENU", select);
			switch (select)
			{
			case 0:
			{
				int method = 0;
				int PizzaN = 0;
				while (method != -1)
				{
					method = (language == "ua")
						? Menu<string>::Show({ "*Редагувати піцу","*Додати піцу","&Видалити піцу" }, "МЕТОДИ", method)
						: Menu<string>::Show({ "*Edit pizza","*Add pizza","&Delete pizza" }, "METHODS", method);
					if (method == 1)
					{
						int instrt = 0;
						while (instrt != -1)
						{
							instrt = Menu<Pizza>::Show(_Pizza, "ADD PIZZA?", instrt);
							if (instrt != -1)
							{
								_Pizza.insert(_Pizza.begin() + instrt, Pizza());
								cout << "Pizza pushed." << endl;
							}
						}
					}
					else if (method != -1)
						while (PizzaN != -1)
						{
							PizzaN = Menu<Pizza>::Show(_Pizza, "PIZZA", PizzaN);
							if (PizzaN != -1)
							{
								cout << string(40, '=') << endl;
								switch (method)
								{
								case 0:
									cout << "Pizza etited." << endl;
									_Pizza[PizzaN].Edit(ingredient);
									break;
								case 2:
									cout << "Pizza has been deleted." << endl;
									if (!_Pizza.empty())_Pizza.erase(_Pizza.begin() + PizzaN);
									break;
								}
							}
						}
					PizzaN = 0;
				}
			}
			break;
			case 1:
			{
				int method = 0;
				int ingT = 0;
				int ingN = 0;
				while (method != -1)
				{
					method = (language == "ua")
						? Menu<string>::Show({ "&Редагувати інгредієнти","Додати новий інгредієнт","Видалити інгредієнти" }, "CONSTRUCTOR", method)
						: Menu<string>::Show({ "&Edit ingredient","&Add new ingredient","&Delete ingredient" }, "CONSTRUCTOR", method);
					if (method != -1)
						while (ingT != -1)
						{
							ingT = Menu<IngredientType>::Show(ingredient, "PIZZA MENU");
							if (ingT != -1)
								if (method == 1)
								{
									int insert = 0;
									while (insert != -1)
									{
										insert = ingredient[ingT].Choise(insert, "ADD PRODUCT?");
										if (insert != -1)
										{
											string title;
											float price;
											int count;
											cout << "\nEnter new title of product:";
											while (title == "")
												getline(cin, title);
											cout << "\nEnter new count number of product:"; cin >> count; cin.clear();
											cout << "\nEnter new price number of product:"; cin >> price; cin.clear();
											ingredient[ingT].AddNew(title, count, price, insert);
											cout << "Ingredient pushed." << endl;
										}
									}
								}
								else while (ingN != -1)
								{
									ingN = ingredient[ingT].Choise(ingN);
									if (ingN != -1)
										switch (method)
										{
										case 0:
											cout << "Ingredient etited." << endl;
											ingredient[ingT][ingN].Constructor();
											break;
										case 2:
											ingredient[ingT].Delete(ingN);
											cout << "Ingredient has been deleted." << endl;
											break;
										}
								}
							ingN = 0;
						}
					ingT = 0;
				}
			}
			break;
			case 2:
				cout << "Saving..." << endl;
				Savedatapizza();
				cout << "Saved data to file complite." << endl;
				break;
			case 3:
				cout << "Saving..." << endl;
				Savedataing();
				cout << "Saved data to file complite." << endl;
				break;
			case 4:
				ingredient.clear();
				Loaddataing();
				_getch();
				break;
			case 5:
				_Pizza.clear();
				Loaddatapizza();
				_getch();
				break;
			case 6:
				cout << "Pizza on the case:" << endl;
				ShowPizza();
				_getch();
				break;
			case 7:
				cout << "Ingredient on the case:" << endl;
				ShowIngr();
				_getch();
				break;
			case 8:
				cout << "Method is empty." << endl;
				_getch();
				break;
			}
		} while (select != -1);

	}

	float GetValueIng(int type, int num) { return Pizzeria::ingredient[type][num].Price(); }
	//=================================================
	void Loaddataing()
	{
		ifstream file(Name + language + "ingredient.txt");
		if (!file)
		{
			cout << "Error file reading.";
			return;
		}
		int count;
		file >> count;
		for (size_t i = 0; i < count; i++)
		{
			IngredientType tt(file);
			ingredient.push_back(tt);
		}
		file.close();
	}
	void Loaddatapizza()
	{
		ifstream file(Name + language + "pizza.txt");
		if (!file)
		{
			cout << "Error file reading.";
			return;
		}
		int count;
		file >> count;
		for (size_t i = 0; i < count; i++)
		{
			_Pizza.push_back(Pizza(file));
		}
		file.close();
	}
	//=================================================
	void Savedatapizza()
	{
		ofstream file(Name + "menu1.txt");
		if (!file)
		{
			cout << "File no finded.";
			return;
		}
		file << _Pizza.size() << endl;
		for (Pizza s : _Pizza)
		{
			file << s;
		}
		file.close();
	}
	void Savedataing()
	{
		ofstream file(Name + "ingr1.txt");
		if (!file)
		{
			cout << "File no finded.";
			return;
		}
		file << ingredient.size() << endl;
		for (IngredientType s : ingredient)
		{
			file << s;
		}
		file.close();
	}
	//=================================================
	void ShowIngr()
	{
		for (IngredientType s : ingredient)
		{
			cout << s << endl;
		}
	}
	void ShowPizza()
	{
		for (Pizza s : _Pizza)
		{
			cout << s << endl;
		}
	}
	//=================================================
};