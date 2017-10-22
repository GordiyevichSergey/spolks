#ifndef PROCESS_H
#define PROCESS_H

#include "headers.h"
#include "Configurator.h"
#include "Command.h"
#include "TimeCommand.h"
#include "EchoCommand.h"

class Process {
protected:
	char *buffer;
	static const int BUFFER_SIZE;

public:
	Process();

	virtual ~Process();

	virtual void start() = 0 {

	}

protected:
	Command* selectCommand(SOCKET sock, Type type, char *command);
};

#endif PROCESS_H