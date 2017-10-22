#ifndef COMMAND_H
#define COMMAND_H

#include "headers.h"

class Command {
protected:
	Protocol protocol;
	static const char OK_MSG[];

public:
	static const int MAX_COMMAND_LENGTH;

	Command();

	Command(Protocol protocol);

public:
	virtual void execute(Type type, SOCKET sock, char *buffer) const = 0 {

	}

	int _send(SOCKET sock, const char *buffer, unsigned char length) const;
	
	int _recv(SOCKET sock, char *buffer) const;
};

#endif 