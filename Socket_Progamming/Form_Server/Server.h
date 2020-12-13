#pragma once

#include "..\Struct\Header.h"
#include "MainForm.h"


#define DEFAULT_BUFFER_LENGTH 102912 // buffer file + buffer others
#define BUFFER_SIZE 102400


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
	//int numberOfClients;
	String^ serverIpAddress;
	int serverPortAddress;


	String^ accountPath = "Database\\accounts.txt";
	String^ inforPath = "Database\\infor.txt";

	// public file
	FileStream^ fileStream = nullptr;
	int fileSize = 0;
	String^ fileNamePath = "Database\\fileNames.txt";
	String^ filePath = "File\\";

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
		this->serverIpAddress = "192.168.18.122";
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
	bool checkChangePassword(String^ user, String^ oldPw, String^ newPw, String^ confirmPw, String^& errorMessage) {
		if (String::IsNullOrEmpty(user) || String::IsNullOrEmpty(oldPw) || String::IsNullOrEmpty(newPw)|| String::IsNullOrEmpty(confirmPw)) {
			errorMessage = "User Name or Password can't be blank !";
			return false;
		}
		if (user->Contains(",") || oldPw->Contains(",") || newPw->Contains(",") || confirmPw->Contains(","))
		{
			errorMessage = "Username or password can't contain special characters!";
			return false;
		}
		if (!checkAccountLogin(user, oldPw)) {
			errorMessage = "Username or password is not correct!";
			return false;
		}
		else {
			if (oldPw == newPw) {
				errorMessage = "New password cannot be the same as old password !";
				return false;
			}
		}

		if (newPw != confirmPw) {
			errorMessage = "Password and confirm password don't match!";
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
			System::IO::File::AppendAllText(inforPath, user + "," + "\n");
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
			this->mainScreen->appendTextToChatBox(userName + " has just online !");

			logInResponse(true, errorMessage, clientSocket);
			sendLogInNotification(userName, clientSocket);	
			this->mainScreen->updateConnectedClient(this->getListOfClient());

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


	bool changePassword(String^ Username, String^ oldPassword, String^ newPassword, String^ confirmnewPassword, Socket^ _ClientSocket)
	{
		String^ errorMsg = "";
		if (checkChangePassword(Username, oldPassword, newPassword, confirmnewPassword, errorMsg))
		{
			array<String^>^ lines = System::IO::File::ReadAllLines(accountPath);
			//for each (String ^ line in lines)
			for (int i = 0; i < lines->Length; i++)
			{
				//MessageBox::Show(line);
				if (lines[i] == Username + "," + oldPassword)
				{
					//MessageBox::Show(line);
					//line->Replace(/*Username + "|" + oldPassword*/line, Username + "|" + newPassword);
					lines[i] = Username + "," + newPassword;
					break;
				}
			}
			System::IO::File::WriteAllLines(accountPath, lines);
			changePasswordResponse(true, errorMsg, _ClientSocket);
			return true;
		}
		changePasswordResponse(false, errorMsg, _ClientSocket);
		return false; //Error 
	}
	void changePasswordResponse(bool IsSucc, String^ errorMsg, Socket^ _ClientSocket)
	{
		ResponseChangePassword^ resChangePass = gcnew ResponseChangePassword;
		resChangePass->isSuccessful = IsSucc;
		resChangePass->errorMessage = errorMsg;
		array<Byte>^ buff = resChangePass->pack();

		_ClientSocket->Send(buff); //Send the result to client.
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

	void sendLogOutNotification(Socket^ clientSocket) {
		LogOutNotification^ logOut = gcnew LogOutNotification;
		logOut->userName = getUserNameBySocket(clientSocket);
		array<Byte>^ data = logOut->pack();

		this->mainScreen->appendTextToChatBox(logOut->userName + " has just offline!");
		
		removeClientByUserName(logOut->userName);
		this->mainScreen->updateConnectedClient(getListOfClient());
		
		for each (Client ^ client in clients) {
			if (client->clientSocket != clientSocket)
				client->clientSocket->Send(data);
		}

	}
	void sendLogOutNotification(String^userName,Socket^ clientSocket) {
		LogOutNotification^ logOut = gcnew LogOutNotification;
		logOut->userName = userName;
		array<Byte>^ data = logOut->pack();

		this->mainScreen->appendTextToChatBox(logOut->userName + " has just offline!");

		removeClientByUserName(logOut->userName);
		this->mainScreen->updateConnectedClient(getListOfClient());

		for each (Client ^ client in clients) {
			if (client->clientSocket != clientSocket)
				client->clientSocket->Send(data);
		}

	}


	void userStatusResponse(Socket^ clientSocket) {
		UserStatusClass^ userStatus = gcnew UserStatusClass();
		userStatus->listUser = getListOfClient()->ToArray();

		array<Byte>^ data = userStatus->pack();

		clientSocket->Send(data);
	}

	void sendPublicMessageToClients(String^ message, Socket^ clientSocket) {
		String^ userName = getUserNameBySocket(clientSocket);
		String^ publicMessage = userName + ": " + message;

		this->mainScreen->appendTextToChatBox(publicMessage);
		PublicChat^ sendPublicMessage = gcnew PublicChat();
		sendPublicMessage->message = publicMessage;
		array<Byte>^ data = sendPublicMessage->pack();

		for each (Client ^ client in clients) {
			try {
				client->clientSocket->Send(data);
			}
			catch (Exception^ e) {
				MessageBox::Show(e->Message, "Error server sendpublic");
			}
		}
		

	}

	int sendPrivateMessage(String^ userNameReceiver, String^ message, Socket^ senderSocket) {
		String^ sender = getUserNameBySocket(senderSocket);
		Socket^ receiverSocket = getSocketByUserName(userNameReceiver);

		PrivateChat^ privateMessage = gcnew PrivateChat();
		if (receiverSocket == nullptr) {
			privateMessage->message = "[SERVER], " + userNameReceiver + " is offline!";
			privateMessage->userNameReceiver = userNameReceiver;
			array<Byte>^ data = privateMessage->pack();
			senderSocket->Send(data);
		}

		else {
			this->mainScreen->appendTextToChatBox("FROM " + sender + " TO " + userNameReceiver + ": " + message);
			privateMessage->message = sender + ": " + message;
			privateMessage->userNameReceiver = sender;
			array<Byte>^ data = privateMessage->pack();
			receiverSocket->Send(data);
		}

		return 0;

	}

	void requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize, Socket^ _ClientSocket)
	{
		String^ sender = getUserNameBySocket(_ClientSocket);
		RequestSendFile^ rqSendFileStruct = gcnew RequestSendFile;
		rqSendFileStruct->userName = sender;
		rqSendFileStruct->fileName = _FileName;
		rqSendFileStruct->iFileSize = _iFileSize;

		Socket^ receiver = getSocketByUserName(_ToUsername);
		array<Byte>^ byteData = rqSendFileStruct->pack();
		receiver->Send(byteData);
	}
	void responseSendFile(String^ _ToUsername, bool _IsAccept, Socket^ _ClientSocket)
	{
		String^ sender = getUserNameBySocket(_ClientSocket);
		ResponseSendFile^ rpSendFileStruct = gcnew ResponseSendFile;
		rpSendFileStruct->userName = sender;
		rpSendFileStruct->isAccept = _IsAccept;

		Socket^ receiver = getSocketByUserName(_ToUsername);
		array<Byte>^ byteData = rpSendFileStruct->pack();
		receiver->Send(byteData);
	}

	void sendPrivateFilePackage(String^ _ToUsername, String^ _Filename, int _iPackageNumber, int _TotalPackage, array<Byte>^ _bData, Socket^ _ClientSocket)
	{
		String^ sender = getUserNameBySocket(_ClientSocket);
		PrivateFile^ prvFile = gcnew PrivateFile();
		prvFile->userName = sender;
		prvFile->fileName = _Filename;
		prvFile->bData = _bData;
		//System::Array::Copy(_bData, 0, prvFile->bData, 0, _bData->Length);
		prvFile->iPackageNumber = _iPackageNumber;
		prvFile->iTotalPackage = _TotalPackage;

		array<Byte>^ byteData = prvFile->pack();
		Socket^ receiver = getSocketByUserName(_ToUsername);
		receiver->Send(byteData);
	}

	void setInfor(String^ userName, String^ birthDate)
	{
		array<String^>^ lines = System::IO::File::ReadAllLines(inforPath);
		for (int i = 0; i < lines->Length; i++)
		{
			if (lines[i]->Contains(userName + ","))
				//if (lines[i] == userName + "|")
			{
				//MessageBox::Show("Hello guy");
				lines[i] = userName + "," + birthDate;
				break;
			}
		}
		System::IO::File::WriteAllLines(inforPath, lines);
	}
	void responseInfor(String^ _friendUsername, Socket^ _ClientSocket)
	{
		array<String^>^ lines = System::IO::File::ReadAllLines(inforPath);
		String^ BirthDate;
		for (int i = 0; i < lines->Length; i++)
		{
			if (lines[i]->Contains(_friendUsername + ","))
			{
				//MessageBox::Show("Hello guy");
				BirthDate = lines[i]->Remove(0, _friendUsername->Length + 1);
				break;
			}
		}
		//System::IO::File::WriteAllLines(inforPath, lines);
		ResponseInforClass^ resInfor = gcnew ResponseInforClass();
		resInfor->friendUsername = _friendUsername;
		resInfor->birthDate = BirthDate;

		//Socket^ receiver = getSocketByUsername(_ToUsername);
		array<Byte>^ buff = resInfor->pack();
		_ClientSocket->Send(buff);
	}


	// others

	List<String^>^ getListOfClient() {
		List<String^>^ list = gcnew List<String^>;


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


	String^ getUserNameBySocket(Socket^ clientSocket) {
		for each (Client ^ client in clients) {
			if (client->clientSocket == clientSocket)
				return client->userName;
		}

		return nullptr;
	}
	void removeClientByUserName(String^ userName) {
		for each (Client ^ client in clients) {
			if (client->userName == userName) {
				clients->Remove(client);
				break;
			}
				
		}
	}
	
	// file
	void sendPublicFile(String^ fileName,Socket^ clientSocket) {
		array<Byte>^ buffer = System::IO::File::ReadAllBytes(filePath + fileName);
		DownloadPublicFileClass^ pubFile = gcnew DownloadPublicFileClass();
		pubFile->fileName = fileName;
		pubFile->iFileSize = buffer->Length;
		int check = 0;
		try {
			
			int sum = buffer->Length;
			int counter = 0;
			int curPackageNumber = 1;
			int iTotalPackage = sum / (BUFFER_SIZE + 1) + 1;
			pubFile->iTotalPackage = iTotalPackage;
			//prvChatForm->setUpProcessBar(1, iTotalPackage);
			for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
			{

				int copyLength = BUFFER_SIZE < sum ? BUFFER_SIZE : (sum % BUFFER_SIZE);
				sum -= copyLength;
				pubFile->bData = gcnew array<Byte>(copyLength);
				System::Array::Copy(buffer, counter, pubFile->bData, 0, copyLength);
				counter += copyLength;
				
				pubFile->iPackageNumber = curPackageNumber;

				array<Byte>^ byteData = pubFile->pack();
				clientSocket->Send(byteData);
				check += pubFile->bData->Length;
				//Server::getObject()->mainScreen->appendTextToChatBox(Convert::ToString(copyLength));
				//Server::getObject()->mainScreen->appendTextToChatBox(Convert::ToString(counter));
				//Server::getObject()->mainScreen->appendTextToChatBox(Convert::ToString(pubFile->bData->Length));
				//Server::getObject()->mainScreen->appendTextToChatBox(Convert::ToString(byteData->Length));

				//Server::getObject()->mainScreen->appendTextToChatBox(Convert::ToString(curPackageNumber));
				Thread::Sleep(5);
				delete[] pubFile->bData;
				delete[] byteData;

			}

			if (check == buffer->Length)
				Server::getObject()->mainScreen->appendTextToChatBox("Sent " + pubFile->fileName + "(" + Convert::ToString(check) + " bytes)" + " to " + getUserNameBySocket(clientSocket) + " successfully !");

			delete[] buffer;
		}
		catch (Exception^ e) {
			return;
		}

	}
	array<String^>^ getListOfFileName() {
		array<String^>^ lines = nullptr;
		lines = System::IO::File::ReadAllLines(fileNamePath);
		
		return lines;
	}

	void listFileNameResponse(Socket^ clientSocket) {
		ListPublicFileNameClass^ listFileName = gcnew ListPublicFileNameClass();
		listFileName->listFileName = getListOfFileName();
		array<Byte>^ data = listFileName->pack();
		clientSocket->Send(data);
	}




	bool addFileName(String^ fileName) {
		try {
			array<String^>^ lines = System::IO::File::ReadAllLines(fileNamePath);
			for (int i = 0; i < lines->Length; i++)
			{
				if (lines[i]->Contains(fileName))
				{
					return false;
				}
			}
			System::IO::File::AppendAllText(this->fileNamePath, fileName+"\n");
		}
		catch (Exception^ e) {
			return false;
		}

		return true;
	}
};



