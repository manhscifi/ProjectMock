#pragma once
#define EMPTY ' '
#define W (SIZE+1)+3*SIZE
#define DATABASE_DIR "./data"
#define PLAYERS_DATABASE "./data/players.ini"
#define REPLAY_DATABASE "./data/replay.ini"
#define RED 12
#define BLUE 9
#define DEFAULT 15
//

int const MAX_CLIENTS_IN_ROOM = 2;
int const OPTION = true;
int const PORT = 5150;
int const MAX_CLIENT = 2;
int const BUFFER_LENGHT = 1024;

enum symbol
{
	symbolX = 'X',
	symbolO = 'O'
};