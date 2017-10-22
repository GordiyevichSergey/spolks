#include "Configurator.h"

class ClientConfigurator : public Configurator{
public:
	ClientConfigurator();

	ClientConfigurator(ADDRESS_FAMILY addressFamily, char *ip, unsigned short port);

	SOCKET configure() const;

private:
	void connectToServer(SOCKET sock, sockaddr_in sockAddr) const;
};