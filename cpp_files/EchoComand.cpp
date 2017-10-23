#include "EchoCommand.h"

EchoCommand::EchoCommand() : Command() {
	this->isCompleted = false;
}

void EchoCommand::execute(Type type, SOCKET sock, char *buffer) {
	int nowRecv;

	if (type == CLIENT) {
		nowRecv = _recv(sock, buffer);
		buffer[nowRecv] = '\0';
		std::cout << "ECHO result:" << buffer << std::endl;
	}
	else {
		std::cout << "ECHO command" << std::endl;
		_send(sock, buffer + 5, strlen(buffer) - 5);
	}

	this->isCompleted = true;
}