#include "SendClient.h"

int c_Cinit(WSADATA* pstWsd, SOCKET *iSocket, struct addrinfo **pstAddr, PCSTR iPort, PCSTR pcIp) {

	int iRs = -1;

	iRs = WSAStartup(MAKEWORD(2, 2), pstWsd);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		return -1;
	}


	iRs = reqSocket(iSocket, pstAddr, iPort, pcIp, 'C');
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		WSACleanup();
		return -1;
	}
	return 0;
}

int connectToServer(SOCKET iConnectSocket, struct addrinfo* pcAddr) {
	int iRs = -1;

	iRs = connect(iConnectSocket, pcAddr->ai_addr, (int)pcAddr->ai_addrlen);
	if (iRs == SOCKET_ERROR) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "connect", iRs);
		closesocket(iConnectSocket);
		iConnectSocket = INVALID_SOCKET;
		freeaddrinfo(pcAddr);
		WSACleanup();
		return -1;
	}

	if (iConnectSocket == INVALID_SOCKET) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "connect", iConnectSocket);
		return -1;
	}
	return 0;
}


int sendData(SOCKET iSocket, char* pcBuffer) {

	int iRs = -1;
	int iLen;
	char caLen[C_BUFFER_LENGTH_SIZE];

	iLen = strlen(pcBuffer);
	c_itoa(iLen, caLen);

	iRs = send(iSocket, caLen, C_BUFFER_LENGTH_SIZE, 0);
	if (iRs > 0) {
		iRs = send(iSocket, pcBuffer, iLen, 0);
		
		return 0;
	}
	else{
		closesocket(iSocket);
		WSACleanup();
		return -1;
	}

}
int getDataOfSend(char* pcFileName, char* pcBuffer){

	FILE* pFile;
	
	pFile = fopen(pcFileName, "r");

	if (pFile == NULL) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "fopen", -1);
		return -1;
	}

	if (fgets(pcBuffer, C_BUFFER_SIZE+1, pFile) != NULL) {
		fclose(pFile);
		return 0;
	}

	fclose(pFile);
	return -1;
}

void c_itoa(int iNum, char* pcOutNum) {

	char caTNum[C_BUFFER_LENGTH_SIZE];
	int iNumLen;
	int iOffset;

	memset(pcOutNum, '0', sizeof(pcOutNum));

	itoa(iNum, caTNum, 10);
	iNumLen = strlen(caTNum);
	iOffset = C_BUFFER_LENGTH_SIZE - iNumLen;

	memcpy(pcOutNum + iOffset, caTNum, iNumLen);
}

int closeConnect(SOCKET iConnectSocket) {

	int iRs = -1;

	iRs = shutdown(iConnectSocket, SD_BOTH);
	if (iRs == SOCKET_ERROR) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "shutdown", iRs);
		closesocket(iConnectSocket);
		WSACleanup();
		return -1;
	}

	closesocket(iConnectSocket);
	WSACleanup();

	return 0;
}