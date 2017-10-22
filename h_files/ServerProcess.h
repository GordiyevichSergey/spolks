#include "Process.h"

class ServerProcess : public Process {
private:
	fd_set master, temp;
	SOCKET serverSock;
	SOCKET fd_max;
public:
	ServerProcess(SOCKET sock);

	void start();

private:
	void _select();
	void acceptConnection();
};