#ifndef PROCESS_H
#define PROCESS_H

#include "headers.h"
#include "Configurator.h"
#include "Command.h"
#include "TimeCommand.h"
#include "EchoCommand.h"
#include "UploadCommand.h"

class Process {
public:
	static const int BUFFER_SIZE;
protected:
	char *buffer;
public:
	Process();

	virtual ~Process();

	virtual void start() = 0 {

	}

protected:
	Command* selectCommand(SOCKET sock, Type type, char *command);
};

#endif PROCESS_H