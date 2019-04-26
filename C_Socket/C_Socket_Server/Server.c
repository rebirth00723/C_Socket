#include "Server.h"



int main() {

	int iRs;
	WSADATA stWsd;
	SOCKET iListenSocket = INVALID_SOCKET;
	SOCKET iClientSocket = INVALID_SOCKET;
	char caBuffer[C_BUFFER_SIZE+1];
	int iLen;
	
	iRs = prepareServer(&stWsd, &iListenSocket, iClientSocket);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "prepareServer", iRs);
		return -1;
	}

	iRs = waitForUsrConn(iListenSocket, &iClientSocket);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "waitForUsrConn", iRs);
		return -1;
	}

	printf("Connected.\n\n");

	iRs = recvClientData(iClientSocket, caBuffer, &iLen);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "waitForUsrConn", iRs);
		return -1;
	}

	printf("%s\n%d\n", caBuffer, iLen);

	iRs = stroeDataOfRecv("store.txt", caBuffer, iLen);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "stroeRecvData", iRs);
		return -1;
	}

	iRs = closeServer(iClientSocket, iListenSocket);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "closeServer", iRs);
		return -1;
	}
	system("pause");


	return 0;
}


int prepareServer(WSADATA *stWsd, SOCKET *iListenSocket, SOCKET * iClientSocket) {

	int iRs;

	iRs = c_init(stWsd, iListenSocket, C_DEFAULT_PORT, "127.0.0.1");
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "c_init", iRs);
		return -1;
	}

	iRs = startListen(*iListenSocket, C_CONNECT_MAX);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "startListen", iRs);
		return -1;
	}


	return 0;
}