#include "Server.h"



int main() {

	int iRs;
	WSADATA stWsd;
	SOCKET iListenSocket = INVALID_SOCKET;
	SOCKET iClientSocket = INVALID_SOCKET;
	
	printf("Preparing.\n");
	prepareServer(&stWsd, &iListenSocket, iClientSocket);
	printf("  Done.\n");

	printf("Waiting client connect.\n");
	iRs = waitForUsrConn(iListenSocket, &iClientSocket);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "waitForUsrConn", iRs);
		return -1;
	}
	printf("  Connected.\n");

	printf("Waiting Data.\n");
	recvClientData(iClientSocket);

	printf("Hello world!");

	return 0;
}


int prepareServer(WSADATA *stWsd, SOCKET *iListenSocket, SOCKET * iClientSocket) {

	int iRs;

	iRs = init(stWsd, iListenSocket, C_DEFAULT_PORT);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "init", iRs);
		return -1;
	}

	iRs = startListen(*iListenSocket, C_CONNECT_MAX);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "startListen", iRs);
		return -1;
	}


	return 1;
}