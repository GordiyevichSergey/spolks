#ifndef COMMAND_H
#define COMMAND_H

#include "headers.h"

class Command {
protected:
	static const char OK_MSG[];
	static const char END_MSG[];
	bool isCompleted;

public:
	static const int MAX_COMMAND_LENGTH;

	Command();

	virtual ~Command();

public:
	virtual void execute(Type type, SOCKET sock, char *buffer) = 0 {

	}

	int _send(SOCKET sock, const char *buffer, unsigned char length) const;
	
	int _recv(SOCKET sock, char *buffer) const;

	bool checkStatus();
};

#endif 