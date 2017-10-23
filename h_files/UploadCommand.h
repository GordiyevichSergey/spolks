#ifndef UCOMMAND_H
#define UCOMMAND_H

#include "Command.h"
#include "Process.h"

class UploadCommand : public Command {
private:
	char* fileName;
public:
	UploadCommand();

	UploadCommand(char *fileName);

	~UploadCommand();

	void execute(Type type, SOCKET sock, char *buffer);
};

#endif UCOMMAND_H