#pragma once
#include "SocketInterFace.h"


int init(WSADATA* pstWsd, SOCKET* iSocket, PCSTR iPort);

int settingSomething(SOCKET* iSocket, PCSTR iPort);
int startListen(SOCKET iSocket, int iConnAmt);
int waitForUsrConn(SOCKET iListenSocket, SOCKET* piClientSocket);
int recvClientData();
int closeServer(SOCKET iClientSocket);


#define C_BUFFER_SIZE	512
#define C_BUFFER_LENGTH_SIZE	4

