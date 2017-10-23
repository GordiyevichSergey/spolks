#ifndef DCOMMAND_H
#define DCOMMAND_H

#include "Command.h"
#include "Process.h"

class DownloadCommand : public Command {
private:
	char *fileName;
	int lastPos;
public:
	DownloadCommand();

	DownloadCommand(char *fileName);

	~DownloadCommand();

	void execute(Type type, SOCKET sock, char *buffer);
};

#endif DCOMMAND_H