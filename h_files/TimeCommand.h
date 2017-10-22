#include "Command.h"
#include <time.h>

class TimeCommand : public Command {
public:
	TimeCommand();
	
	TimeCommand(Protocol protocol);
	
	void execute(Type type, SOCKET sock, char *buffer) const;

private:
	char* getCurrentTime() const;
};