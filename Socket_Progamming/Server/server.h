#ifndef server_h_
#define server_h_




#include "Account.h"


#define MAX_CLIENTS 10
#define DEFAULT_IP_ADDRESS "192.168.0.1"
#define DEFAULT_PORT "3503"
#define DEFAULT_BUFFER_LENGTH 512


const char OPTION_VALUE = 1;

struct Client {
	int id;
	SOCKET socket;
	Account *account;
};


////struct AddressInformation {
////	int AI_Family,AI_SockType, AI_Port, AI_Protocol, AI_Flags;
////	size_t AI_AddressLength;
////	sockaddr* AI_Address;
////
////};

#endif
