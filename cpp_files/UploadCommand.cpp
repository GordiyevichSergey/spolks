#include "UploadCommand.h"

UploadCommand::UploadCommand() : Command() {
	this->isCompleted = false;
	this->fileName = new char[strlen("file.mp4") + 1];
	strcpy(this->fileName, "file.mp4");
}

UploadCommand::UploadCommand(char *fileName) {
	this->isCompleted = false;
	this->fileName = new char[strlen(fileName) + 1];
	strcpy(this->fileName, fileName);
}

UploadCommand::~UploadCommand() {
	delete[] fileName;
}

void UploadCommand::execute(Type type, SOCKET sock, char *buffer) {
	std::string fName(this->fileName);
	int nowReaded;

	if (type == CLIENT) {
		std::string fPath(CLIENT_PATH);
		fPath += fName;
		FILE *file = fopen(fPath.c_str(), "r+b");

		while ((nowReaded = fread(buffer, 1, Process::BUFFER_SIZE, file)) != 0) {
			_send(sock, buffer, nowReaded);
		}
		_send(sock, this->END_MSG, 3);

		fclose(file);

		this->isCompleted = true;
	}
	else {
		std::cout << "UPLOAD COMMAND" << std::endl;

		int nowRecv = 0;
		std::string fPath(SERVER_PATH);
		fPath += fName;
		FILE *file = fopen(fPath.c_str(), "a+b");
		nowRecv = _recv(sock, buffer);
		if (!strncmp(buffer, this->END_MSG, 3)) {
			this->isCompleted = true;
		}
		else {
			fwrite(buffer, 1, nowRecv, file);
		}

		fclose(file);
	}
}