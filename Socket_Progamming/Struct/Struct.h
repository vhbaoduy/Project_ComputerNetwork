#pragma once
 //Thread
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Windows::Forms;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Threading;


ref class StructClass abstract
{
public:
	enum class MessageType { LogIn, ResponseLogin, SignUp, ResponseSignUp, LogInNotification, LogOutNotification, PublicChat, PrivateChat, UserStatus, RequestSendFile, ResponseSendFile, PrivateFile, ChangePassword,ResponseChangePassword,SetInfor,RequestInfor,ResponseInfor};
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

//String^ convertStringToHex(String^ input);
//String^ convertHexToString(String^ hexInput);
//{
//    List<Byte>^ stringBytes = gcnew List<Byte>();
//    stringBytes->AddRange(Encoding::UTF8->GetBytes(input));
//    // Byte[] stringBytes = encoding.GetBytes(input);
//    array<Byte>^ temp = stringBytes->ToArray();
//    StringBuilder^ sbBytes = gcnew StringBuilder(temp->Length * 2);
//    for each (Byte b in temp)
//    {
//        sbBytes->AppendFormat("{0:X2}", b);
//    }
//    return sbBytes->ToString();
//}
//

//{
//    int numberChars = hexInput->Length;
//    array<Byte>^ bytes = gcnew array<Byte>(numberChars / 2);
//    // byte[] bytes = new byte[numberChars / 2];
//    for (int i = 0; i < numberChars; i += 2)
//    {
//        bytes[i / 2] = Convert::ToByte(hexInput->Substring(i, 2), 16);
//    }
//    return Encoding::UTF8->GetString(bytes);
//}

