#include "Configurator.h"

Configurator::Configurator() {
	this->addressFamily = AF_INET;
	this->port = 27015;

	this->ip = new char[strlen("127.0.0.1") + 1];
	strcpy(this->ip, "127.0.0.1");
}

Configurator::Configurator(ADDRESS_FAMILY addressFamily, char *ip, unsigned short port) {
	this->addressFamily = addressFamily;
	this->port = port;

	this->ip = new char[strlen(ip) + 1];
	strcpy(this->ip, ip);
}

Configurator::~Configurator() {
	delete[] this->ip;
}

SOCKET Configurator::createSocket() const{
	SOCKET sock;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {
		throw "socket() error";
	}

	return sock;
}

void Configurator::closeSocket(SOCKET sock) {
#ifdef _WIN32
	closeSocket(sock);
#endif

#ifdef __linux
	close(sock);
#endif
}

sockaddr_in Configurator::createSockAddr() const{
	sockaddr_in sockAddr;

	sockAddr.sin_family = this->addressFamily;
	sockAddr.sin_addr.s_addr = inet_addr(this->ip);
	sockAddr.sin_port = htons(this->port);

	return sockAddr;
}

SOCKET Configurator::setupKeepAlive(SOCKET sock) {
#ifdef _WIN32
	DWORD dwBytesRet = 0;
	struct tcp_keepalive keepalive;
	keepalive.onoff = TRUE;
	keepalive.keepalivetime = 7200000;
	keepalive.keepaliveinterval = 120000;

	int ret;
	ret = WSAIoctl(sock, SIO_KEEPALIVE_VALS, &keepalive, sizeof(keepalive), NULL, 0, &dwBytesRet, NULL, NULL);
	if (ret == SOCKET_ERROR) {
		throw "WSAIoctl() error";
	}
#endif

#ifdef __linux
	int optval = 1;
	socklen_t  optlen = sizeof(optval);

	int ret;
	ret = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen);
	if (ret == SOCKET_ERROR) {
		throw "setsockopt() error";
	}
#endif

	return sock;
}