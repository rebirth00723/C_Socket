#include <stdio.h>
#pragma warning( disable : 4996 )

int sstroeRecvData(char* pcFileName, char* pcBuffer, int iSize) {


	FILE* pFile;

	pFile = fopen(pcFileName, "w");

	if (pFile == NULL) {
		c_Alter(__FILE__, __FUNCTION__, __LINE__, "fopen", -1);
		return -1;
	}

	if (fputs(pcBuffer, pFile) != NULL) {
		fclose(pFile);
		return 0;
	}
	c_Alter(__FILE__, __FUNCTION__, __LINE__, "fputs", -1);
	fclose(pFile);
	return -1;


}

int main() {
	int size;
	char* B = "12345";
	sstroeRecvData("store.txt", B, 5);
	return 1;
}
