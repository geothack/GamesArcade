#include "game_window.h"

void game_window::create_window(const int width, const int height)
{
	m_width = width;
	m_height = height;

	SMALL_RECT windowSize = { 10, 10, width + 20, height + 20 };
	if (!SetConsoleWindowInfo(h_console, TRUE, &windowSize))
	{
		std::cerr << "SetConsoleWindowInfo failed with error " << GetLastError() << std::endl;
	}

	if (!SetConsoleTitle(L"Space Invaders")) // cover sting types (termination)
	{
		std::cerr << "SetConsoleTitle failed with error " << GetLastError() << std::endl;
	}

#pragma region hideCursor
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE); // this code hides the cursor
	CONSOLE_CURSOR_INFO     cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
#pragma endregion

#pragma region changeFont
	CONSOLE_FONT_INFOEX cfi = { sizeof(cfi) };

	HANDLE hcsb = CreateFileA("CONOUT$", GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	// Populate cfi with the screen buffer's current font info
	GetCurrentConsoleFontEx(hcsb, FALSE, &cfi);

	// Modify the font size in cfi
	cfi.dwFontSize.X *= 2;
	cfi.dwFontSize.Y *= 2;

	// Use cfi to set the screen buffer's new font
	SetCurrentConsoleFontEx(hcsb, FALSE, &cfi);
#pragma endregion
}

void game_window::set_cursor(const int x, const int y)
{
	static const HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(h_out, coord);
}
