#pragma once
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Runtime::Serialization;
using namespace System::Collections::Generic; //List
using namespace System::Text; //Encoding


ref class AppSocket {
private:
	String^ serverIpAddress;
	int serverPortAddress;

public:
	Socket^ clientSocket = nullptr;
	AppSocket() {
		serverIpAddress = "127.128.0.1";
		serverPortAddress = 2020;
	}

	AppSocket(String^ ip, int port) {
		serverIpAddress = ip;
		serverPortAddress = port;
	}

	int createSocket() {
		if (clientSocket == nullptr)
			clientSocket = gcnew Socket(AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp);

		return !(clientSocket == nullptr);
	}

	bool initializeSocket() {
		return this->createSocket();
	}

	int connectToServer(String^ ip, int port) {
		serverIpAddress = ip;
		serverPortAddress = port;
		return connectToServer();
	}
	int connectToServer() {
		IPAddress^ ip = IPAddress::Parse(serverIpAddress);
		IPEndPoint^ serverIpEndPoint = gcnew IPEndPoint(ip, serverPortAddress);

		try
		{
			clientSocket->Connect(serverIpEndPoint);
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message, "Error Connection",
				MessageBoxButtons::OK, MessageBoxIcon::Error);
			return 1; //Error
		}

		return 0;
	}
};


