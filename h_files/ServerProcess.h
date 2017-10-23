#include "Process.h"

class ServerProcess : public Process {
private:
	fd_set master, temp;
	SOCKET serverSock;
	SOCKET fd_max;

	std::vector<std::pair<SOCKET, Command*>> activeCommands;
public:
	ServerProcess(SOCKET sock);

	void start();

private:
	void _select();
	void acceptConnection();
	Command* checkActiveCommands(SOCKET sock);
	void removeCompletedCommand(SOCKET sock);
};