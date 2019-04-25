#include "StoreServer.h"

int init(WSADATA *pstWsd, SOCKET *iSocket, PCSTR iPort) {

	int iRs = -1;

	iRs = WSAStartup(MAKEWORD(2, 2), pstWsd);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		return -1;
	}

	iRs = settingSomething(iSocket, iPort);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "settingSomething", iRs);
		return -1;
	}

	return 0;
}


int startListen(SOCKET iSocket, int iConnAmt) {

	int iRs;

	iRs = listen(iSocket, iConnAmt);
	if (iRs == SOCKET_ERROR) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "listen", iRs);
		closesocket(iSocket);
		WSACleanup();
		return -1;
	}
	return 0;
}


int waitForUsrConn(SOCKET iListenSocket, SOCKET* piClientSocket) {

	SOCKET _iClientSocket = INVALID_SOCKET;

	_iClientSocket = accept(iListenSocket, NULL, NULL);
	if (_iClientSocket == INVALID_SOCKET) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "accept", _iClientSocket);
		closesocket(iListenSocket);
		WSACleanup();
		return -1;
	}

	*piClientSocket = _iClientSocket;

	return 0;
}



int settingSomething(SOCKET *iSocket, PCSTR iPort) {

	int iRs;
	struct addrinfo* pstAddr;

	iRs = reqSocket(iSocket, &pstAddr, iPort, NULL);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		WSACleanup();
		return -1;
	}

	iRs = bind(*iSocket, pstAddr->ai_addr, (int)pstAddr->ai_addrlen);
	if (iRs == SOCKET_ERROR) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "bind", iRs);
		freeaddrinfo(pstAddr);
		closesocket(*iSocket);
		WSACleanup();
		return -1;
	}

	freeaddrinfo(pstAddr);

	return 0;

}

int recvClientData(SOCKET iClientSocket ) {

	char cBuffer[C_BUFFER_SIZE + 1];
	char cLen[C_BUFFER_LENGTH_SIZE + 1];
	int iLen;
	int iRs = -1;

	memset(cBuffer, '\0', sizeof(cBuffer));
	memset(cLen, '\0', sizeof(cLen));
	
	//recv() will respond length of recieved.
	iRs = recv(iClientSocket, cBuffer, C_BUFFER_LENGTH_SIZE, 0);
	if (iRs == C_BUFFER_LENGTH_SIZE) {

		memcpy(cLen, cBuffer, C_BUFFER_LENGTH_SIZE);
		memset(cBuffer, '\0', sizeof(cBuffer));

		cLen[4] = '\0';

		iLen = atoi(cLen);



		iRs = recv(iClientSocket, cBuffer, iLen, 0);
		if (iRs == iLen) {
			printf("Recieved data:%s", cBuffer);
		}
		else if (iRs > C_BUFFER_SIZE) {
			printf("The buffer is not enough. Size:%d\n", iRs);
		}


		printf("Data length:%d\n", iLen);
	}

	return 0;
}


int closeServer(SOCKET iClientSocket) {

	int iRs = -1;

	iRs = shutdown(iClientSocket, SD_SEND);
	if (iRs == SOCKET_ERROR) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "shutdown", iRs);
		closesocket(iClientSocket);
		WSACleanup();
		return -1;
	}

	closesocket(iClientSocket);
	WSACleanup();

	return 0;
}