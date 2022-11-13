#pragma once
#define TABLE_SIZE 10
#define CONDITION_WIN 4
#define EMPTY ' '
#define ALIGN (TABLE_SIZE+1)+3*TABLE_SIZE
#define RED 12
#define BLUE 9
#define DEFAULT 15

#define BUFFER_LENGHT 1024
#define PORT 5150
#define MAX_ATTEMPT 5
//
enum symbol
{
	symbolX = 'X',
	symbolO = 'O'
};

enum clientOption
{
	login = 1,
	registerPlayer,
	getInfo,
	combat,
	close,

};