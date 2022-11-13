//#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include"TCPServerSelect.h"
using namespace std;

#define PORT 5150 


int main()
{
	TCPServerSelect server;
	server.init(PORT);
	return 0;
}