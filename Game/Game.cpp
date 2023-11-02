#include<iostream>
#include<iomanip>
#include<string.h>
#include<conio.h>
#include <Windows.h>

using namespace std;

enum keys
{
	UP = 72,
	DOWN = 80,
	LEFT = 75,
	RIGHT = 77
};

enum levels {
	EASY,
	NORMAL,
	HARD
};

void fill_game_fields(short fields[][4]);
void show_fields(short fields[][4]);
void find_empty_cell(short fields[][4], short& x, short& y);
void move(short fields[][4], unsigned char key);
void start_position(short fields[][4],const int level);
bool is_win(short fields[][4]);
bool is_right_pos(short value, short position_value);

int menuChoice(const char* Menu[], int length) {
	HANDLE level = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned char key{};
	int choice{};
	while (key != 13) {
		system("cls");
		for (size_t i = 0; i < length; i++)
		{
			SetConsoleTextAttribute(level, 244);
			if (choice == i) {
				cout << '>';
			}
			else cout << ' ';
			cout << ' ' << Menu[i] << endl;
		}
		key = _getch();
		if (key == 224) {
			key = _getch();
		}
		switch (key)
		{
		case UP:
			choice--;
			if (choice < 0) choice = length - 1;
			break;
		case DOWN:
			(++choice) %= length;
			break;
		}
	}
	system("cls");
		return choice;
}

void saveFile(short game_field[][4]) {
	FILE* file;
	fopen_s(&file, "game.dat", "wb");
	fwrite((char*)game_field, sizeof(short), 16, file);
	fclose(file);
}
void loadFile(short game_field[][4]) {
	FILE* file;
	fopen_s(&file, "game.dat", "rb");
	fread((char*)game_field, sizeof(short), 16, file);
	fclose(file);
}

int main() {
#pragma region Start
	srand(time(NULL));

	short game_field[4][4]{};
	unsigned char key{};
	int choice{};
	const char* levelmenu[3]{
		"Easy",
		"Normal",
		"Hard"
	};

	const char* gamemenu[3]{
		"Start new game",
		"Load saved game",
		"Exit"
	};


	choice = menuChoice(gamemenu, 3);
	if (choice == 0) {
		choice = menuChoice(levelmenu, 3);
	}
	else if (choice == 1) {
		loadFile(game_field);
	}
	else {
		return 0;
	}
	fill_game_fields(game_field);
	start_position(game_field,choice);
	show_fields(game_field);
#pragma endregion
#pragma region Game
	while (!is_win(game_field))
	{
		key = _getch(); // 224
		key = _getch();
		move(game_field, key);
		system("cls");
		show_fields(game_field);

	}
#pragma endregion
#pragma region Win
	system("cls");
	cout << "Win" << endl;
#pragma endregion
}

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
	saveFile(fields);
}

void start_position(short fields[][4],const int level) {
	int side{};
	int leveles[]{ 100,500,1200 };
	int sides[]{ UP, DOWN, LEFT, RIGHT };
	for (size_t i = 0; i < leveles[level]; i++)
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