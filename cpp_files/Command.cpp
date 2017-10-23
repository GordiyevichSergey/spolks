#include "Command.h"

const char Command::OK_MSG[] = "ok";
const char Command::END_MSG[] = "end";
const int Command::MAX_COMMAND_LENGTH = 128;

Command::Command() {
	
}

Command::~Command() {

}

int Command::_send(SOCKET sock, const char *buffer, unsigned char length) const {
	int nowSent, nowRecv;
	char okBuffer[2];

	send(sock, reinterpret_cast<const char*>(&length), 1, MSG_OOB);
	nowSent = send(sock, buffer, (size_t)length, 0);

	if (nowSent != (int)length) {
		return -1;
	}
	std::cout << nowSent << " bytes sent" << std::endl;

	nowRecv = recv(sock, okBuffer, 2, 0);
	std::cout << nowRecv << " bytes received" << std::endl;
		
	if (strncmp(okBuffer, OK_MSG, 2)) {
		return -1;
	}

	return nowSent;
}

int Command::_recv(SOCKET sock, char *buffer) const {
	int nowSent, nowRecv;
	unsigned char length = 0;

	while (recv(sock, reinterpret_cast<char*>(&length), 1, MSG_OOB) == -1) {

	}
	nowRecv = recv(sock, buffer, (size_t)length, 0);
	if (nowRecv != (int)length) {
		return -1;
	}
	std::cout << nowRecv << " bytes received" << std::endl;

	nowSent = send(sock, OK_MSG, 2, 0);
	std::cout << nowSent << " bytes sent" << std::endl;

	return nowRecv;
}

bool Command::checkStatus() {
	return this->isCompleted;
}