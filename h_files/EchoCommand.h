#include "Command.h"

class EchoCommand : public Command {
public:
	EchoCommand();

	void execute(Type type, SOCKET socket, char *buffer);
};