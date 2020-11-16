#pragma once

//#include <iostream>
//#include <winsock2.h>
//#include <ws2tcpip.h>
//#include <string>
//#include <thread>
//#include <vector>
//#include <stdexcept>
//#include <sstream>
//#include <iomanip>
#include "MainForm.h"


using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Collections::Generic; //List
using namespace System::Threading; //Thread


#pragma comment (lib, "Ws2_32.lib")
#include <cstdint>
#define MAX_CLIENTS 10
#define DEFAULT_IP_ADDRESS L"192.168.0.1"
#define DEFAULT_PORT L"3504"
#define DEFAULT_BUFFER_LENGTH 512



const char OPTION_VALUE = 1;



ref class Account {
private:
	System::String^ userName, ^passWord;
public:
public:
	Account() {
		userName = passWord = "";
		
	}
	void setUserName(String^ user) { userName = user; }
	void setPassWord(String^ pw) { passWord = pw; }
	String^ getUserName() { return userName; }
	String^ getPassWord() { return passWord; }
	void changePassWord(String^ npw) {
		this->setPassWord(npw);
	}
	void registerAccount(String^ user, String^ pw) {
		this->setPassWord(pw);
		this->setUserName(user);
	}
	~Account() {

	}
};


ref class Client {
public:
	Socket^ clientSocket = nullptr;
	Account^ account = nullptr;
	int id;
	String^ userName;
	Client() {
		id = -1;
		userName = account->getUserName();
	}
};


ref class Server {
private:
	static Server^ instance = nullptr;

	int createSocket() {
		serverSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		return !(serverSocket == nullptr);
	}
public:

	List<Client^>^ clients = gcnew List<Client^>();
	Socket^ serverSocket = nullptr;
	int numberOfClients;
	String^ serverIpAddress;
	int serverPortAddress;
	List<Thread^>^ threads = gcnew List<Thread^>();

	// Form
	Form_Server::MainForm^ mainScreen;


	static Server^ getObject() {
		if (instance == nullptr)
			instance = gcnew Server();

		return instance;
	}
	Server(String^ ip, int port) {
		this->serverIpAddress = ip;
		this->serverPortAddress = port;
		createSocket();
	}
	Server() {
		this->serverIpAddress = "127.128.0.1";
		this->serverPortAddress = 2020;
		createSocket();
	}

	~Server() {
		delete serverSocket;
	}

	bool initializeSocket() {

		Server^ server = Server::getObject();

		IPAddress^ serverIpAddress = IPAddress::Parse(server->serverIpAddress);
		int serverPort = server->serverPortAddress;
		IPEndPoint^ serverIpEndPoint = gcnew IPEndPoint(serverIpAddress, serverPort);

		server->serverSocket->Bind(serverIpEndPoint);
		server->serverSocket->Listen(10);


		return 0;
	}

	//static bool processClient(Client^ newClient) {
	//	String^ messenger = "";
	//	//char* tempMessenger = new char[DEFAULT_BUFFER_LENGTH];
	//	array<Byte>^ buff = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
	//	if (newClient->clientSocket == nullptr)
	//		return false;

	//	while (1) {
	//		//(tempMessenger, 0, DEFAULT_BUFFER_LENGTH);
	//		//int checkResult = System::Net::Sockets::SocketReceiveFromResult(newClient->clientSocket, tempMessenger, DEFAULT_BUFFER_LENGTH, 0);
	//		int iResult = newClient->clientSocket->Receive(buff);



	//	}
	//	return true;
	//}


	// Login
	bool checkInputLogin(String^ user, String^ password, String^& errorMessenger) {
		if (String::IsNullOrEmpty(user) || String::IsNullOrEmpty(password)) {
			errorMessenger = "User Name or Password can't be blank !";
			return false;
		}


		return true;
	}


};



