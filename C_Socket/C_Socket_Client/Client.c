#include "Client.h"

int main() {

	int iRs;
	WSADATA stWsd;
	SOCKET iConnectSocket = INVALID_SOCKET;
	struct addrinfo* pstAddr;
	char pcBuffer[C_BUFFER_SIZE + 1];


	iRs = c_Cinit(&stWsd, &iConnectSocket, &pstAddr, C_DEFAULT_PORT, "127.0.0.1");
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "c_init", iRs);
		return -1;
	}

	iRs = connectToServer(iConnectSocket, pstAddr);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "connectToSocket", iRs);
		return -1;
	}

	iRs = getDataOfSend("req.txt", pcBuffer);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "getDataOfSend", -1);
		return -1;
	}

	iRs = sendData(iConnectSocket, pcBuffer);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "sendData", iRs);
		return -1;
	}

	iRs = closeConnect(iConnectSocket);
	if (iRs != 0) {
			c_Alter(__FILE__, __FUNCTION__, __LINE__, "closeConnect", iRs);
			return -1;
		}

	printf("Hello world!\n");
	system("pause");
	return 0;
}

