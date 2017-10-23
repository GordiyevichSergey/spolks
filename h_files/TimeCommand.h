#include "Command.h"
#include <time.h>

class TimeCommand : public Command {
public:
	TimeCommand();
	
	void execute(Type type, SOCKET sock, char *buffer);

private:
	char* getCurrentTime() const;
};