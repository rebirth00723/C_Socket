#include "StoreServer.h"

int c_init(WSADATA *pstWsd, SOCKET *iSocket, PCSTR iPort, PCSTR pcIp) {

	int iRs = -1;
	struct addrinfo* pstAddr;

	iRs = WSAStartup(MAKEWORD(2, 2), pstWsd);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		return -1;
	}

	iRs = reqSocket(iSocket, &pstAddr, iPort, pcIp, 'S');
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		WSACleanup();
		return -1;
	}

	iRs = bind(*iSocket, pstAddr->ai_addr, (int)pstAddr->ai_addrlen);
	if (iRs == SOCKET_ERROR) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "bind", iRs);
		freeaddrinfo(pstAddr);
		closesocket(*iSocket);
		WSACleanup();
		return -1;
	}

	freeaddrinfo(pstAddr);

	return 0;
}

int startListen(SOCKET iSocket, int iConnAmt) {

	int iRs;

	iRs = listen(iSocket, iConnAmt);
	if (iRs == SOCKET_ERROR) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "listen", iRs);
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
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "accept", _iClientSocket);
		closesocket(iListenSocket);
		WSACleanup();
		return -1;
	}

	*piClientSocket = _iClientSocket;

	return 0;
}


int recvClientData(SOCKET iClientSocket, char* pcBuffer, int *iLen) {

	char cLen[C_BUFFER_LENGTH_SIZE + 1];
	int _iLen = -1;
	int iRs = -1;

	memset(pcBuffer, '\0', sizeof(pcBuffer));
	memset(cLen, '\0', sizeof(cLen));
	
	//recv() will respond length of recieved.
	iRs = recv(iClientSocket, pcBuffer, C_BUFFER_LENGTH_SIZE, 0);
	if (iRs == C_BUFFER_LENGTH_SIZE) {

		memcpy(cLen, pcBuffer, C_BUFFER_LENGTH_SIZE);

		cLen[4] = '\0';
	
		_iLen = atoi(cLen);
		*iLen = _iLen;

		iRs = recv(iClientSocket, pcBuffer, _iLen, 0);
		if (iRs < 0) {
			c_Alter(__FILE__, __FUNCTION__, __LINE__, "recv", iRs);
			closesocket(iClientSocket);
			WSACleanup();
			return - 1;
		}
		else if (iRs == _iLen) {
			pcBuffer[_iLen] = '\0';
		}
		else if (iRs > C_BUFFER_SIZE) {
			c_Alter(__FILE__, __FUNCTION__, __LINE__, "recv [The buffer is not enough.]", iRs);
		}
	}
	else {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "recv [The Data format is invalid.]", iRs);
		closesocket(iClientSocket);
		WSACleanup();
		return -1;
	}

	return 0;
}

int storeDataOfRecv(char* pcFileName, char* pcBuffer, int iSize) {

	FILE* pFile;

	pFile = fopen(pcFileName, "w");

	if (pFile == NULL) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "fopen", -1);
		return -1;
	}

	if (fputs(pcBuffer, pFile) == EOF) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "fputs", -1);
		fclose(pFile);
		return -1;
	}
	
	fclose(pFile);

	return 0;
}

int closeServer(SOCKET iClientSocket, SOCKET iListenSocket) {

	int iRs = -1;

	closesocket(iListenSocket);

	iRs = shutdown(iClientSocket, SD_BOTH);
	if (iRs == SOCKET_ERROR) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "shutdown", iRs);
		closesocket(iClientSocket);
		WSACleanup();
		return -1;
	}

	closesocket(iClientSocket);
	WSACleanup();

	return 0;
}