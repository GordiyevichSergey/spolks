#include "EchoCommand.h"

EchoCommand::EchoCommand() : Command() {

}

EchoCommand::EchoCommand(Protocol protocol) : Command(protocol) {

}

void EchoCommand::execute(Type type, SOCKET sock, char *buffer) const {
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
}