#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "IngredientType.h"
#include "Pizza.h"
#include "Menu.h"

class Client
{
private:
	vector<Pizza> pizza;
public:
	Client(vector<Pizza>& pizza)
	{
		this->pizza = pizza;
	}
	Client(vector<Pizza> _Pizza,vector<Ingredient> ingr)
	{
		switch (Menu<string>::Show({ "Standart pizza","My pizza" }))
		{
		case 0:
			int PizzaN = 0;
			while (PizzaN != -1)
			{
				PizzaN = Menu<Pizza>::Show(_Pizza, "ADD PIZZA?", PizzaN);
				if (PizzaN != -1)
				{
					pizza.push_back(_Pizza[PizzaN]);
				}
			}
			for (Pizza ptr:pizza) 
			{
			
			}
			break;
		case 1:
			break;
		}
		if (pizza.size() != 0) Pay();
	};
	void Pay()
	{
		cout << "\t\tPizzeria Freddy" << endl;
		for (Pizza s : pizza)
		{
			cout << s;
		}
	}
	/*void StandartPizza(vector<Pizza>& pizzas)
	{
		Menu<Pizza>::Show(pizzas);
	}*/
};