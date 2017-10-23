#include "DownloadCommand.h"

DownloadCommand::DownloadCommand() {
	this->lastPos = 0;
	this->isCompleted = false;
	this->fileName = new char[strlen("file.mp4") + 1];
	strcpy(this->fileName, "file.mp4");
}

DownloadCommand::DownloadCommand(char *fileName) {
	this->lastPos = 0;
	this->isCompleted = false;
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);
}

DownloadCommand::~DownloadCommand() {
	delete[] this->fileName;
}

void DownloadCommand::execute(Type type, SOCKET sock, char *buffer) {
	std::string fName(this->fileName);
	int nowRecv, nowReaded;

	if (type == CLIENT) {
		std::string fPath(CLIENT_PATH);
		fPath += fName;
		FILE *file = fopen(fPath.c_str(), "a+b");
		do {
			_send(sock, this->OK_MSG, 2);
			nowRecv = _recv(sock, buffer);
			fwrite(buffer, 1, nowRecv, file);
		} while (strncmp(buffer, this->END_MSG, 3));

		fclose(file);
		this->isCompleted = true;
	}
	else {
		std::cout << "DOWNLOAD COMMAND" << std::endl;

		std::string fPath(SERVER_PATH);
		fPath += fName;
		FILE *file = fopen(fPath.c_str(), "r+b");
		fseek(file, this->lastPos, SEEK_SET);

		_recv(sock, buffer);
		nowReaded = fread(buffer, 1, Process::BUFFER_SIZE, file);
		if (nowReaded == 0) {
			_send(sock, this->END_MSG, 3);
			this->isCompleted = true;
		}
		else {
			this->lastPos += nowReaded;
			_send(sock, buffer, nowReaded);
		}

		fclose(file);
	}
}