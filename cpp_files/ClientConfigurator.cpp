#include "ClientConfigurator.h"

ClientConfigurator::ClientConfigurator() : Configurator() {

}

ClientConfigurator::ClientConfigurator(ADDRESS_FAMILY addrFamily, char *ip, unsigned short port) 
	: Configurator(addressFamily, ip, port) {

}

SOCKET ClientConfigurator::configure() const{
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
		connectToServer(sock, sockAddr);
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		return -1;
	}

	try {
		sock = setupKeepAlive(sock);
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		return -1;
	}

	return sock;
}

void ClientConfigurator::connectToServer(SOCKET sock, sockaddr_in sockAddr) const{
	int ret;
	ret = connect(sock, (struct sockaddr*)&sockAddr, sizeof(sockAddr));
	if (ret == SOCKET_ERROR) {
		throw "connect() error";
	}
}