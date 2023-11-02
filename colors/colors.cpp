#include <iostream>
#include <Windows.h>
#include <iomanip>
using namespace std;

int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (size_t i = 0; i <= 256; i++)
	{
		SetConsoleTextAttribute(hConsole, i);
		cout << setw(3) << i;
		if ((i + 1) % 16 == 0 && i != 0) cout << "\n";
	}
	SetConsoleTextAttribute(hConsole, 15);
}