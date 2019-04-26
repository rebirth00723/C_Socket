#include "SocketInterface.h"


/*
Get Socket
*/
int reqSocket(SOCKET *iSocket, struct addrinfo **pstAddr, PCSTR iPort, PCSTR pcIp, char cStatus) {

	int iRs;
	struct addrinfo* _pstAddr;

	iRs = parsingAddr(pstAddr, iPort, pcIp, cStatus);
	if (iRs != 0) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "parsingAddr", iRs);
		return -1;
	}

	_pstAddr = *pstAddr;


	*iSocket = socket(_pstAddr->ai_family, _pstAddr->ai_socktype, _pstAddr->ai_protocol);
	if (*iSocket == INVALID_SOCKET) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "socket", *iSocket);
		freeaddrinfo(_pstAddr);
		return -1;
	}

	return 0;
}

int parsingAddr(struct addrinfo **pstAddr, PCSTR iPort, PCSTR pcIp, char cStatus) {

	int iRs;
	struct addrinfo hints;
	memset(&hints, '\0', sizeof(hints));

	hints.ai_family = cStatus == 'S' ? AF_INET : AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if(cStatus == 'S')
		hints.ai_flags = AI_PASSIVE;
	
	iRs = getaddrinfo(pcIp, iPort, &hints, pstAddr);

	return iRs;
}


void c_Alter(const char *cpcFile, const char* cpcSFunc, int iLine, const char* cpcFunc, int iRs) {

	printf("[%s][%s][%d] %s function error[%d][%d]\n", cpcFile, cpcSFunc, iLine, cpcFunc, iRs, WSAGetLastError());
}
