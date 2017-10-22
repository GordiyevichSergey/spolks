#include "Configurator.h"

class ServerConfigurator : public Configurator {
private:
	int maxConnections;
public:
	ServerConfigurator(int maxConnections);

	ServerConfigurator(ADDRESS_FAMILY addressFamily, char *ip, unsigned short port, int maxConnections);

	SOCKET configure() const;
private:
	SOCKET bindSocket(SOCKET sock, sockaddr_in sockAddr) const;

	SOCKET translateIntoListenMode(SOCKET sock) const;
};
