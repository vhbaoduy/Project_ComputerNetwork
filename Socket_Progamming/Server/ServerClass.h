#pragma once

#include "server.h"
class ServerClass
{
private:
	vector<Client> clients;
	addrinfo hints;
	addrinfo*server;
	vector<thread> threads;
	SOCKET serverSocket;
	int numberOfClients;
	WSADATA wsaData;

public:
	ServerClass() {
		//clients.resize(MAX_CLIENTS);
		//threads.resize(MAX_CLIENTS);
		serverSocket = INVALID_SOCKET;
		server = NULL;
		numberOfClients = -1;
		clients.resize(MAX_CLIENTS);
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			clients[i] = { -1, INVALID_SOCKET,NULL };
		}
		threads.resize(MAX_CLIENTS);
	}
	void initiateWinSock() {
		WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	void setIPv4WithProtocolTCP() {
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;
		hints.ai_flags = AI_PASSIVE;

	}

	void setUpServer(PCSTR IP, PCSTR PORT) {
			
		getaddrinfo(IP, PORT, &hints, &server);
	}
	bool createServerSocket() {
		this->serverSocket = socket(server->ai_family, server->ai_socktype, server->ai_protocol);
		if (serverSocket != INVALID_SOCKET) {
			setsockopt(this->serverSocket, SOL_SOCKET, SO_REUSEADDR, &OPTION_VALUE, sizeof(int));
			setsockopt(this->serverSocket, IPPROTO_TCP, TCP_NODELAY, &OPTION_VALUE, sizeof(int));
			return true;
		}
			
		return false;
	}

	void Bind() {
		bind(this->serverSocket, server->ai_addr, (int)server->ai_addrlen);

	}
	void Listen() {
		listen(serverSocket, SOMAXCONN);
	}


	void initiateServer() {
		this->initiateWinSock();
		this->setUpServer(DEFAULT_IP_ADDRESS, DEFAULT_PORT);
		this->createServerSocket();
		this->Bind();
		this->Listen();
	}

	bool checkLogIn(Client& newClient) {

	}


	bool procesClient(Client& newClient) {
		string messenger = "";
		char* tempMessenger = new char[DEFAULT_BUFFER_LENGTH];
		if (newClient.socket == 0)
			return false;

		while (1) {
			memset(tempMessenger, 0, DEFAULT_BUFFER_LENGTH);
			int checkResult = recv(newClient.socket, tempMessenger, DEFAULT_BUFFER_LENGTH, 0);

			if (checkResult != SOCKET_ERROR) {
				if (strcmp("", tempMessenger))
					messenger = "Client #" + std::to_string(newClient.id) + ": " + tempMessenger;
					//+ hex_to_string(tempmsg)
				cout << messenger.c_str() << endl;

				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (this->clients[i].socket != INVALID_SOCKET)
						if (newClient.id != i)
							checkResult = send(this->clients[i].socket, messenger.c_str(), strlen(messenger.c_str()), 0);
				}

			}

			else
			{
				messenger = "Client #" + std::to_string(newClient.id) + " Disconnected";

				cout << messenger << endl;

				closesocket(newClient.socket);
				closesocket(this->clients[newClient.id].socket);
				this->clients[newClient.id].socket = INVALID_SOCKET;

				//Broadcast the disconnection message to the other clients
				for (int i = 0; i < MAX_CLIENTS; i++)
				{
					if (this->clients[i].socket != INVALID_SOCKET)
						checkResult = send(this->clients[i].socket, messenger.c_str(), strlen(messenger.c_str()), 0);
				}

				break;
			}
		}
		threads[newClient.id].detach();

		return true;
	}


	void mainLoop(){

	}

};

