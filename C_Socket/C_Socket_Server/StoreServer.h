#pragma once
#include "SocketInterFace.h"


int init(WSADATA* pstWsd, SOCKET* iSocket, PCSTR iPort);

int startListen(SOCKET iSocket, int iConnAmt);
int waitForUsrConn(SOCKET iListenSocket, SOCKET* piClientSocket);
int recvClientData();

#define C_BUFFER_SZIE	512
#define C_BUFFER_LENGTH_SZIE	512

