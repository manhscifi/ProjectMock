#include "Menu.h"

Menu::Menu()
{
    //disable click X to close console
   /*EnableMenuItem(GetSystemMenu(GetConsoleWindow(), FALSE),
        SC_CLOSE, MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);  */
   SetConsoleCtrlHandler(ctrl_handler, TRUE);
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
    game.loadPlayerList();
    game.loadMatchRecord();
	while (true)
	{
		cout << "\tGame Caro\n";
        cout << "[" << registerPlayer << "] Register new player\n";
        cout << "[" << play << "] Start Game\n";		
		cout << "[" << showListPlayers << "] Players List\n";
        cout << "[" << replayGames << "] Replay\n";
		cout << "[" << exitGame << "] Save & Exit\n\n";

        cout << "Option: ";
        int option = UserInput<int>::input();
        switch (option)
        {
        case registerPlayer:
        {
            system("cls");
            cout << "Register new player\n";            
            game.registerPlayer();
            system("cls");
            break;
        }
        case play:
        {
            system("cls");
            game.initGame();
            game.playGame();
            game.clearGame();
            break;
        }
        case showListPlayers:
        {
            system("cls");
            cout << "\tPlayer:\n";
            game.showPlayers();
            cout << "\n";
            break;
        }
        case replayGames:
        {
            system("cls");
            game.replayMatch();
            break;
        }
        case exitGame:
        {
            game.updateMatchRecord();
            game.updatePlayerList();
            Sleep(1000);
            exit(0);
        }
        default:
        {
            system("cls");
            cout << "Option 1 - " << exitGame << ".\n\n";
        }
        }
	}    
}