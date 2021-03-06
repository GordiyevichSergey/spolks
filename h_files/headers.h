#ifndef HEADERS_H
#define HEADERS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32

#include <winsock2.h>
#include <MSTcpIP.h>
#pragma comment(lib, "WS2_32.lib")
#pragma warning(disable:4996)
typedef int socklen_t;
#define CLIENT_PATH "E:\\spolks\\client files\\"
#define SERVER_PATH "E:\\spolks\\server files\\"

#endif

#ifdef __linux

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
#define CLIENT_PATH "E:\\spolks\\client files\\"
#define SERVER_PATH "E:\\spolks\\server files\\"

#endif

enum Protocol {
	TCP, UDP
};

enum Type {
	CLIENT, SERVER
};

#endif