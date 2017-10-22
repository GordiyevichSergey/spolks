#include "Process.h"

class ClientProcess : public Process {
private:
	SOCKET clientSocket;

public:
	ClientProcess(SOCKET sock);

	void start();

private:
	void printHelp() const;
	bool checkCommand(char *command) const;
};