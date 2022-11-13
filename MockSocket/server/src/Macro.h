#pragma once
#define SIZE 10
#define CONDITION_WIN 4
#define EMPTY ' '
#define W (SIZE+1)+3*SIZE
#define DATABASE_DIR "./data"
#define PLAYERS_DATABASE "./data/players.ini"
#define REPLAY_DATABASE "./data/replay.ini"
#define RED 12
#define BLUE 9
#define DEFAULT 15
//
enum symbol
{
	symbolX = 'X',
	symbolO = 'O'
};

enum choice
{
	registerPlayer = 1,
	play,
	showListPlayers,
	replayGames,
	exitGame,
};
