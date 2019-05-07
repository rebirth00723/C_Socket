#pragma once
#include "SocketInterface.h"


int c_init(WSADATA* pstWsd, SOCKET* iSocket, PCSTR iPort, PCSTR pcIp);
int startListen(SOCKET iSocket, int iConnAmt);
int waitForUsrConn(SOCKET iListenSocket, SOCKET* piClientSocket);
int recvClientData(SOCKET iClientSocket, char* pcBuffer, int* iLen);
int storeDataOfRecv(char* pcFileName, char* pcBuffer, int iSize);
int closeServer(SOCKET iClientSocket, SOCKET iListenSocket);


#define C_BUFFER_SIZE	512
#define C_BUFFER_LENGTH_SIZE	4

