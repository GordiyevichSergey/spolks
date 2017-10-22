#include "Command.h"

class EchoCommand : public Command {
public:
	EchoCommand();
	
	EchoCommand(Protocol protocol);

	void execute(Type type, SOCKET socket, char *buffer) const;
};