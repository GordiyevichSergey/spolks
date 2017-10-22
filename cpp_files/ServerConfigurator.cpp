#include "ServerConfigurator.h"

ServerConfigurator::ServerConfigurator(int maxConnections) : Configurator(), maxConnections(maxConnections) {

}

ServerConfigurator::ServerConfigurator(ADDRESS_FAMILY addressFamily, char *ip, unsigned short port, int maxConnections) 
	: Configurator(addressFamily, ip, port), maxConnections(maxConnections) {

}

SOCKET ServerConfigurator::configure() const{
	SOCKET sock;
	sockaddr_in sockAddr;

	try {
		sock = createSocket();
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		return -1;
	}

	sockAddr = createSockAddr();

	try {
		sock = bindSocket(sock, sockAddr);
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		closeSocket(sock);
		return -1;
	}

	try {
		sock = translateIntoListenMode(sock);
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		closeSocket(sock);
		return -1;
	}

	std::cout << "Succes server configuration" << std::endl;
	return sock;
}

SOCKET ServerConfigurator::bindSocket(SOCKET sock, sockaddr_in sockAddr) const {
	int ret;
	ret = bind(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if (ret == SOCKET_ERROR) {
		throw "bind() error";
	}

	return sock;
}

SOCKET ServerConfigurator::translateIntoListenMode(SOCKET sock) const {
	int ret;
	ret = listen(sock, this->maxConnections);
	if (ret == SOCKET_ERROR) {
		throw "listen() error";
	}

	return sock;
}