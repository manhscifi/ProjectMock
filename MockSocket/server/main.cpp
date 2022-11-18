//#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>
#include"TCPServer.h"
using namespace std;

int main()
{
	TCPServer server;
	server.init(PORT);
	return 0;
}