#pragma once
#include "SocketInterface.h"


int c_Cinit(WSADATA* pstWsd, SOCKET *iSocket, struct addrinfo** pstAddr, PCSTR iPort, PCSTR pcIp);
int connectToServer(SOCKET iConnectSocket, struct addrinfo* pcAddr);
int sendData(SOCKET iSocket, char* pcFileName);
int getDataOfSend(char* pcFileName, char* pcBuffer);
int closeConnect(SOCKET iConnectSocket);
void c_itoa(int iNum, char* pcOutNum);
#define C_BUFFER_SIZE	512
#define C_BUFFER_LENGTH_SIZE	4
