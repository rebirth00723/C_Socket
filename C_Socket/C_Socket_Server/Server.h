#pragma once
#include "../LibSocket/StoreServer.h"

#define C_CONNECT_MAX 1 
#define C_DEFAULT_PORT "27015"

int prepareServer(WSADATA* stWsd, SOCKET* iListenSocket);