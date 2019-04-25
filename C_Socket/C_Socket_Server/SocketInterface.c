#include "SocketInterface.h"



int reqSocket(SOCKET *iSocket, struct addrinfo **pstAddr, PCSTR iPort) {

	int iRs;
	struct addrinfo* _pstAddr;

	// WSAStartup¡B[parsingAddr]¡Bsocket¡Bbind
	iRs = parsingAddr(pstAddr, iPort);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "parsingAddr", iRs);
		return -1;
	}

	_pstAddr = *pstAddr;

	// WSAStartup¡BparsingAddr¡B[socket]¡Bbind
	*iSocket = socket(_pstAddr->ai_family, _pstAddr->ai_socktype, _pstAddr->ai_protocol);
	if (iSocket == INVALID_SOCKET) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "socket", iSocket);
		freeaddrinfo(pstAddr);
		return -1;
	}

	return 0;
}

int parsingAddr(struct addrinfo **pstAddr, PCSTR iPort) {

	int iRs;
	struct addrinfo hints;
	memset(&hints, '\0', sizeof(hints));

	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	iRs = getaddrinfo(NULL, iPort, &hints, pstAddr);

	return iRs;
}


void cAlter(const char * cpcFile, const char* cpcSFunc, int iLine, const char* cpcFunc, int iRs) {

	printf("[%s][%s][%d] %s function error[%d][%d]\n", cpcFile, cpcSFunc, iLine, cpcFunc, iRs, WSAGetLastError());
}