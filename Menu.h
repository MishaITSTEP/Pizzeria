#pragma once
#include <iostream>
#include <conio.h>
#include <vector>
#include <Windows.h>


using namespace std;

enum ConsoleColor {
	BLACK = 0,
	DARKBLUE = FOREGROUND_BLUE,
	DARKGREEN = FOREGROUND_GREEN,
	DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
	DARKRED = FOREGROUND_RED,
	DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
	DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	GRAY = FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
	MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
};

void SetColor(ConsoleColor textColor)
{
	ConsoleColor backColor = BLACK;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)backColor << 4 | (WORD)textColor);
}

void SetColor(bool i = 0)
{
	i ? SetColor(WHITE) : SetColor(GRAY);
}

template<typename T>
class Menu
{
	string TableName;
	vector<T> data;
public:
	static int Show(const vector<T>& data, string Name = "MENU", int selecte = 0)
	{
		if (selecte >= data.size())selecte = data.size() - 1;
			int input = 'q';
		do
		{
			system("cls");
			SetColor(ConsoleColor::YELLOW);
			cout << "\t" << Name;
				SetColor(ConsoleColor::BLUE);
			cout << " [&](Робочі), [*](частково робочі), [-](Неробочі), [Q]BACK" << endl;
			if (data.empty())
			{
				return -1;
				SetColor(ConsoleColor::RED);
				cout << "Database is empty.";
				SetColor();
				_getch();
			}
			for (size_t i = 0; i < data.size(); i++)
			{
				SetColor(i == selecte);
				cout << data[i] << endl;
			}
			//cout << selecte << endl;
			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 80: selecte >= data.size() - 1 ? selecte = 0 : selecte++; break;
				case 72: selecte <= 0 ? selecte = data.size() - 1 : selecte--; break;
				}
			}
			else if (input == 13)
				return selecte;
		} while (input != 'q');
		SetColor();
		return -1;
	}
	static int Show(vector<T>& data, string Name = "MENU", int selecte = 0)
	{
		int input = 'q';
		do
		{
			system("cls");
			SetColor(ConsoleColor::YELLOW);
			cout << "\t" << Name;
			SetColor(ConsoleColor::BLUE);
			cout << " [&](Робочі), [*](частково робочі), [-](Неробочі), [Q]BACK" << endl;
			if (data.empty())
			{
				SetColor(ConsoleColor::RED);
				cout << "Database is empty.";
				_getch();
				SetColor();
				return -1;
			}
			for (size_t i = 0; i < data.size(); i++)
			{
				SetColor(i == selecte);
				cout << data[i] << endl;
			}
			//cout << selecte << endl;
			input = _getch();
			if (input == 224)
			{
				input = _getch();
				switch (input)
				{
				case 80: selecte >= data.size() - 1 ? selecte = 0 : selecte++; break;
				case 72: selecte <= 0 ? selecte = data.size() - 1 : selecte--; break;
				}
			}
			else if (input == 13)
				return selecte;
		} while (input != 'q');
		SetColor();
		return -1;
	}
};

