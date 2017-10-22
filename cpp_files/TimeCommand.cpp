#include "TimeCommand.h"

TimeCommand::TimeCommand() : Command() {

}

TimeCommand::TimeCommand(Protocol protocol) : Command(protocol) {

}

void TimeCommand::execute(Type type, SOCKET sock, char *buffer) const{
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
}

char* TimeCommand::getCurrentTime() const {
	time_t rawtime;
	struct tm* timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	return asctime(timeinfo);
}