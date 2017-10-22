#include "Process.h"

const int Process::BUFFER_SIZE = 250;

Process::Process() {
	buffer = new char[BUFFER_SIZE];
}

Process::~Process() {
	delete[] buffer;
}

Command* Process::selectCommand(SOCKET sock, Type type, char *buffer) {
	TimeCommand temp;
	Command *out = nullptr;
	int num = 0;

	if (type == SERVER) {
		num = temp._recv(sock, buffer);
		buffer[num] = '\0';
	}
	else {
		num = temp._send(sock, buffer, strlen(buffer));
	}

	if (num == -1) {
		throw "recv() error";
	}

	if (!strncmp(buffer, "TIME", 4)) {
		out = new TimeCommand(Protocol::TCP);
	}
	else if (!strncmp(buffer, "ECHO", 4)) {
		out = new EchoCommand(Protocol::TCP);
	}
	else if (!strncmp(buffer, "UPLOAD", 6)) {
		out = nullptr;
	}
	else if (!strncmp(buffer, "DOWNLOAD", 8)) {
		out = nullptr;
	}
	else if (!strncmp(buffer, "CLOSE", 5)) {
		out = nullptr;
	}

	return out;
}