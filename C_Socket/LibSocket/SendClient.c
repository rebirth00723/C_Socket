#include "SendClient.h"

int init(WSADATA *pstWsd) {

	int iRs = -1;

	iRs = WSAStartup(MAKEWORD(2, 2), pstWsd);
	if (iRs != 0) {
		cAlter(__FILE__, __FUNCTION__, __LINE__, "WSAStartup", iRs);
		return -1;
	}
}