#pragma once
#include"Game/Game.h"
#include"Macro.h"

class Menu
{
public:
	Menu();
	void run();
	static BOOL WINAPI ctrl_handler(DWORD event);
};

