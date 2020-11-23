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
#include "..\Struct\Header.h"
#include "MainForm.h"




#pragma comment (lib, "Ws2_32.lib")
#include <cstdint>
#define MAX_CLIENTS 10
#define DEFAULT_IP_ADDRESS L"192.168.0.1"
#define DEFAULT_PORT L"3504"
#define DEFAULT_BUFFER_LENGTH 512



const char OPTION_VALUE = 1;


//ref class Client {
//public:
//	Socket^ clientSocket = nullptr;
//	String^ userName = nullptr;
//	Client() {};
//	Client(Socket^ socket, String^ user) {
//		clientSocket = socket;
//		userName = user;
//	}
//};


ref class Server {
private:
	static Server^ instance = nullptr;

	int createSocket() {
		serverSocket = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
		return !(serverSocket == nullptr);
	}
public:

	List<Client^>^ clients = gcnew List<Client^>();
	String^ test;
	Socket^ serverSocket = nullptr;
	int numberOfClients;
	String^ serverIpAddress;
	int serverPortAddress;


	String^ accountPath = "Account\\accounts.txt";

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



	// Login
	bool checkLogin(String^ user, String^ password, String^& errorMessage) {
		if (String::IsNullOrEmpty(user) || String::IsNullOrEmpty(password)) {
			errorMessage = "User Name or Password can't be blank !";
			return false;
		}

		if(user->Contains(",") || password->Contains(","))
		{
			errorMessage = "Username or password can't contain special characters!";
			return false;
		}
		if (!checkAccountLogin(user, password)) {
			errorMessage = "Username or password is not correct!";
			return false;
		}

		for each (String ^ userName in this->getListOfClient()) {
			if (user == userName) {
				errorMessage = user + " is current login on another client!";
				return false;
			}
		}

		return true;

	
	}

	bool checkSignUp(String^ user, String^ password, String^& errorMessage) {
		if (String::IsNullOrEmpty(user) || String::IsNullOrEmpty(password)) {
			errorMessage = "User Name or Password can't be blank !";
			return false;
		}
		if (user->Contains(",") || password->Contains(","))
		{
			errorMessage = "Username or password can't contain special characters!";
			return false;
		}
		if (isAccountExists(user)) {
			errorMessage = "Account has been registered!";
			return false;
		}

		if (!addAccount(user, password)) {
			errorMessage = "Can't register!";
			return false;
		}

		return true;
	}


	
	bool checkAccountLogin(String^ user, String^ pw) {
		array<String^>^ lines = System::IO::File::ReadAllLines(this->accountPath);
		
		for each (String^ line in lines) {
			if (line == user + "," + pw )
				return true;
		}

		return false;
	}

	bool isAccountExists(String^ user) {
		array<String^>^ lines = System::IO::File::ReadAllLines(this->accountPath);
		for each (String ^ line in lines) {
			if (line->Contains(user+ ","))
				return true;
		}

		return false;
	}


	bool addAccount(String^ user, String^ pw) {
		try {
			System::IO::File::AppendAllText(this->accountPath,user + "," + pw + "\n");
		}
		catch (Exception^ e) {
			return false;
		}

		return true;
	}



	//  Main login 
	bool logIn(String^ userName, String^ pw, Socket^ clientSocket) {
		String^ errorMessage = "";
		if (checkLogin(userName, pw, errorMessage)) {
			clients->Add(gcnew Client(clientSocket, userName));
			this->mainScreen->updateConnectedClient(this->getListOfClient());
			this->mainScreen->appendTextToBoxChat(userName + " has just onlline !");

			logInResponse(true, errorMessage, clientSocket);
			//this->mainScreen->updateConnectedClient(this->getListOfClient());

			//sendLogInNotification(userName, clientSocket);

			return true;
		}

		logInResponse(false, errorMessage, clientSocket);

		return false;
	}

	void logInResponse(bool isSuccessful, String^ errorMessage, Socket^ clientSocket) {
		ResponseLogIn^ result = gcnew ResponseLogIn(isSuccessful,errorMessage);
		//result->isSuccessful = isSuccessful;
		//result->errorMessage = errorMessage;
		array<Byte>^ buffer = result->pack();

		clientSocket->Send(buffer);
	}

	void sendLogInNotification(String^ userName, Socket^ clientSocket) {
		LogInNotification^ lgNoti = gcnew LogInNotification;
		lgNoti->userName = userName;
		array<Byte>^ buffer = lgNoti->pack();


		for each (Client ^ client in clients) {
			if (client->clientSocket != clientSocket)
				client->clientSocket->Send(buffer);
		}
	}



	bool signUp(String^ userName, String^ pw, Socket^ clientSocket) {
		String^ errorMessage = "";
		if (checkSignUp(userName, pw, errorMessage)) {
			
			signUpResponse(true, errorMessage, clientSocket);

			return true;
		}

		signUpResponse(false, errorMessage, clientSocket);

		return false;
	}


	void signUpResponse(bool isSuccessful, String^ errorMessage, Socket^ clientSocket) {
		ResponseSignUp^ result = gcnew ResponseSignUp(isSuccessful,errorMessage);
		//result->isSuccessful = isSuccessful;
		//result->errorMessage = errorMessage;
		array<Byte>^ buffer = result->pack();

		clientSocket->Send(buffer);
	}







	// others

	List<String^>^ getListOfClient() {
		List<String^>^ list = gcnew List<String^>();


		for each (Client ^ client in clients) {
			list->Add(client->userName);
		}


		return list;
	}

	Socket^ getSocketByUserName(String^ userName) {
		for each (Client ^ client in clients) {
			if (client->userName == userName)
				return client->clientSocket;
		}

		return nullptr;
	}
	void removeClientByUserName(String^ userName) {
		for each (Client ^ client in clients) {
			if (client->userName == userName)
				clients->Remove(client);
		}
	}



};



