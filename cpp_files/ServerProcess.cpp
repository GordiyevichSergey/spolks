#include "ServerProcess.h"

ServerProcess::ServerProcess(SOCKET sock) : Process() {
	this->fd_max = sock;
	this->serverSock = sock;
	FD_ZERO(&this->master);
	FD_ZERO(&this->temp);
	FD_SET(sock, &this->master);
}

void ServerProcess::start() {
	while (true) {
		this->temp = this->master;
		try {
			_select();
		}
		catch (char *exception) {
			std::cout << exception << std::endl;
			return;
		}

		for (SOCKET currentSocket = 0; currentSocket <= this->fd_max; currentSocket++) {
			if (FD_ISSET(currentSocket, &this->temp)) {
				if (currentSocket == this->serverSock) {
					try {
						acceptConnection();
					}
					catch (char *exception) {
						std::cout << exception << std::endl;
						return;
					}
				}
				else {
					Command *command;

					if ((command = checkActiveCommands(currentSocket)) == nullptr) {
						try {
							command = selectCommand(currentSocket, Type::SERVER, this->buffer);
						}
						catch (char *exception) {
							std::cout << exception << std::endl;
							return;
						}

						if (typeid(*command) == typeid(UploadCommand) || typeid(*command) == typeid(DownloadCommand))
							this->activeCommands.push_back(std::make_pair(currentSocket, command));
					}

					command->execute(Type::SERVER, currentSocket, this->buffer);

					if (command->checkStatus()) {
						removeCompletedCommand(currentSocket);
					}
				}
			}
		}
	}
}

void ServerProcess::_select() {
	int ret;
	ret = select(this->fd_max + 1, &this->temp, NULL, NULL, NULL);
	if (ret == SOCKET_ERROR) {
		throw "socket() error";
	}

	return;
}

void ServerProcess::acceptConnection() {
	SOCKET clientSock;
	sockaddr_in sockAddr;
	socklen_t sockAddrLen = sizeof(struct sockaddr_in);

	clientSock = accept(this->serverSock, (struct sockaddr*)&sockAddr, &sockAddrLen);
	if (clientSock == INVALID_SOCKET) {
		throw "accept() error";
	}

	std::cout << "Client " << inet_ntoa(sockAddr.sin_addr) << " connected" << std::endl;

	try {
		clientSock = Configurator::setupKeepAlive(clientSock);
	}
	catch (char *exception) {
		std::cout << exception << std::endl;
		Configurator::closeSocket(this->serverSock);
		throw "setupKeepAlive() error";
	}

	FD_SET(clientSock, &this->master);
	if (clientSock > this->fd_max) {
		this->fd_max = clientSock;
	}
}

Command* ServerProcess::checkActiveCommands(SOCKET sock) {
	for (auto it = std::begin(this->activeCommands); it != std::end(this->activeCommands); it++) {
		if (it->first == sock) {
			return it->second;
		}
	}

	return nullptr;
}

void ServerProcess::removeCompletedCommand(SOCKET sock) {
	for (auto it = std::begin(activeCommands); it != std::end(activeCommands);) {
		if (it->first == sock) {
			it = activeCommands.erase(it);
		}
		else {
			it++;
		}
	}
}