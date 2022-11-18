#include "Menu.h"

Menu::Menu()
{
    //disable click X to close console
   /*EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE),
        SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);  */
   //SetConsoleCtrlHandler(ctrl_handler, TRUE);
   run();
}

BOOL WINAPI Menu::ctrl_handler(DWORD event)
{
    if (event == CTRL_CLOSE_EVENT) {
        string msg = "\n\tGame will not be saved!!!\n";
        IO::colorize(msg, RED);
        Sleep(5000);
        return TRUE;
    }
    return FALSE;
}

void Menu::run()
{
    Game game;

	while (true)
	{
        system("cls");
		cout << "\tGame Caro\n";
        cout << "[" << login << "] Dang nhap\n";
        cout << "[" << registerPlayer << "] Dang ky\n";
        cout << "[" << getInfo << "] Thong tin nguoi choi\n";
        cout << "[" << combat << "] Choi\n";
        cout << "[" << close << "] Logout\n\n";

        cout << "Type your option: ";
        int option = UserInput<int>::input();

        switch (option)
        {
        case login:
        {
            //cout << "Dang nhap\n"; 
            system("cls");
            game.login();
            break;
        }
        case registerPlayer:
        {
            system("cls");
            game.registerPlayer();
            break;
        }
        case getInfo:
        {
            system("cls");
            //cout << "\tPlayer:\n";
            game.getInfo();
            cout << "\n";
            IO::pause();
            break;
        }
        case combat:
        {
            system("cls");
            game.combat();
            IO::pause();
            break;
        }
        case close:
        {
            system("cls");
            game.closeClient();
            IO::pause();
            break;
        }
        default:
        {
            system("cls");
            cout << "Option 1 - " << close << ".\n\n";
            IO::pause();
        }
        }
	}    
}