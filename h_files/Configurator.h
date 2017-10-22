#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "headers.h"

class Configurator {
protected:
	ADDRESS_FAMILY addressFamily;
	char *ip;
	unsigned short port;

public:
	Configurator();

	Configurator(ADDRESS_FAMILY addressFamily, char *ip, unsigned short port);

	virtual ~Configurator();

	virtual SOCKET configure() const = 0;

	SOCKET createSocket() const;

	static void closeSocket(SOCKET sock);

	sockaddr_in createSockAddr() const;

	static SOCKET setupKeepAlive(SOCKET sock);
};

#endif CONFIGURATOR_H