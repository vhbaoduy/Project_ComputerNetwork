#pragma once
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Threading; //Thread

ref class StructClass abstract
{
public:
	enum class MessageType { LogIn, ResponseLogin, SignUp, ResponseSignUp, LogInNotification, LogOutNotification, PublicChat, PrivateChat, UserStatus, RequestSendFile, ResponseSendFile, PrivateFile };
	MessageType messageType;
	virtual array<Byte>^ pack() = 0;
	virtual StructClass^ unpack(array<Byte>^ buffer) = 0;
};


ref class Client {
public:
	Socket^ clientSocket = nullptr;
	String^ userName = nullptr;
	Client() {};
	Client(Socket^ socket, String^ user) {
		clientSocket = socket;
		userName = user;
	}
};

