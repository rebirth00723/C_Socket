#pragma once
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "Ws2_32.lib")

int parsingAddr(struct addrinfo **pstAddr, PCSTR iPort);
int reqSocket(SOCKET* iSocket, struct addrinfo **pstAddr, PCSTR iPort);

void cAlter(const char* cpcFile, const char* cpcSFunc, int iLine, const char* cpcFunc, int iRs);

