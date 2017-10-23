#include "TimeCommand.h"

TimeCommand::TimeCommand() : Command() {
	this->isCompleted = false;
}

void TimeCommand::execute(Type type, SOCKET sock, char *buffer) {
	int nowRecv;

	if (type == CLIENT) {
		nowRecv = _recv(sock, buffer);
		buffer[nowRecv] = '\0';
		std::cout << "Server time:" << buffer << std::endl;
	}
	else {
		std::cout << "Time command" << std::endl;
		char *time = getCurrentTime();
		_send(sock, time, (char)strlen(time));
	}

	this->isCompleted = true;
}

char* TimeCommand::getCurrentTime() const {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return asctime(timeinfo);
}