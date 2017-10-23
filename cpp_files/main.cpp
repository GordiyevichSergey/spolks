#define _CRT_SECURE_NO_WARNINGS
#include "ClientProcess.h"
#include "ServerProcess.h"
#include "ServerConfigurator.h"
#include "ClientConfigurator.h"

int main(int argc, char *argv[]) {
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	SOCKET sock;
	Configurator *configurator;
	Process *process = nullptr;

	if (!strcmp(argv[1], "server")) {

		configurator = new ServerConfigurator(3);
		sock = configurator->configure();
		process = new ServerProcess(sock);
	}
	else {
		configurator = new ClientConfigurator();
		sock = configurator->configure();
		process = new ClientProcess(sock);
	}

	if (sock != -1) {
		process->start();
	}

	configurator->closeSocket(sock);
#ifdef _WIN32
	WSACleanup();
#endif
	delete configurator;
	delete process;

	system("pause");

	return 0;
}