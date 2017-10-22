#include "ClientProcess.h"

ClientProcess::ClientProcess(SOCKET sock) : Process(), clientSocket(sock) {

}

void ClientProcess::start() {
	printHelp();
	while (true) {
		std::cout << ">";
		char *command = new char[Command::MAX_COMMAND_LENGTH];
		std::cin.getline(command, Command::MAX_COMMAND_LENGTH);

		if (checkCommand(command)) {
			Command *com;
			try {
				com = selectCommand(this->clientSocket, Type::CLIENT, command);
			}
			catch (char *exception) {
				std::cout << exception << std::endl;
				return;
			}

			com->execute(Type::CLIENT, this->clientSocket, command);
		}
		else {
			std::cout << "Wrong command" << std::endl;
		}

		delete[] command;
	}
}

void ClientProcess::printHelp() const{
	std::cout << "Select the command:" << std::endl;
	std::cout << "ECHO" << std::endl;
	std::cout << "TIME" << std::endl;
	std::cout << "UPLOAD" << std::endl;
	std::cout << "DOWNLOAD" << std::endl;
	std::cout << "CLOSE" << std::endl;
}

bool ClientProcess::checkCommand(char *command) const {
	return (!strncmp(command, "CLOSE", 5) || !strncmp(command, "TIME", 4) || !strncmp(command, "ECHO", 4)
		|| !strncmp(command, "UPLOAD", 6) || !strncmp(command, "DOWNLOAD", 8));
}