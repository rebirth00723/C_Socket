#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma warning( disable : 4996 )

int parsingAddr(struct addrinfo **pstAddr, PCSTR iPort, PCSTR pcIp, char cStatus);
int reqSocket(SOCKET *iSocket, struct addrinfo **pstAddr, PCSTR iPort, PCSTR pcIp, char cStatus);

void c_Alter(const char* cpcFile, const char* cpcSFunc, int iLine, const char* cpcFunc, int iRs);

