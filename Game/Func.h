#pragma once
#include<iostream>
#include<iomanip>
#include<string.h>
#include<conio.h>
#include <Windows.h>
#include "Enums.h"

void fill_game_fields(short fields[][4]) {
	short n = 1;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			fields[i][j] = n++;
		}
	}
}

void show_fields(short fields[][4]) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{

			if (is_right_pos(fields[i][j], i * 4 + j + 1)) {
				SetConsoleTextAttribute(hConsole, 250);
			}
			else {
				SetConsoleTextAttribute(hConsole, 244);
			}

			if (fields[i][j] == 16) {
				cout << right << setw(4) << ' ';
			}
			else {
				cout << right << setw(4) << fields[i][j];
			}
		}
		cout << "\n\n";
	}
}

void find_empty_cell(short fields[][4], short& x, short& y) {
	for (short i = 0; i < 4; i++)
	{
		for (short j = 0; j < 4; j++)
		{
			if (fields[i][j] == 16) {
				x = i;
				y = j;
			}
		}
	}
}

void move(short fields[][4], unsigned char key) {
	short x{}, y{};
	find_empty_cell(fields, x, y);
	switch (key)
	{
	case UP:
		if (x < 3) {
			swap(fields[x][y], fields[x + 1][y]);
			x++;
		}
		break;
	case DOWN:
		if (x != 0) {
			swap(fields[x][y], fields[x - 1][y]);
			x--;
		}

		break;
	case LEFT:
		if (y < 3) {
			swap(fields[x][y], fields[x][y + 1]);
			y++;
		}
		break;
	case RIGHT:
		if (y != 0) {
			swap(fields[x][y], fields[x][y - 1]);
			y--;
		}
		break;
	}
}

void start_position(short fields[][4]) {
	int side{};
	int sides[]{ UP, DOWN, LEFT, RIGHT };
	for (size_t i = 0; i < 10; i++)
	{
		side = rand() % 4;
		move(fields, sides[side]);
	}
}

bool is_win(short fields[][4]) {

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (!is_right_pos(fields[i][j], i * 4 + j + 1)) return false;
		}
	}

	return true;
}

bool is_right_pos(short value, short position_value) {
	if (value == position_value)  return true;
	return false;
}