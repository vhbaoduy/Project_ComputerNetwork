#pragma once
#include "..\Struct\Header.h"

#include "LogIn.h"
#include "ConnectServer.h"
#include "AppSocket.h"
#include "MainForm.h"
#include "PrivateChatForm.h"



ref class CentralController
{
private:
	static CentralController^ instance = nullptr;
	CentralController() {
		//this->appSocket = gcnew AppSocket();
		appSocket = nullptr;
	}
	//CentralController(String^ ip, int port) {
	//	appSocket = gcnew AppSocket(ip, port);
	//}
public:
	~CentralController() {
		delete appSocket;
	}

	static CentralController^ getObject() {
		if (instance == nullptr)
			instance = gcnew CentralController();
		return instance;
	}
	//static CentralController^ getObject(String^ ip, int port) {
	//	if (instance == nullptr)
	//		instance = gcnew CentralController(ip,port);
	//	return instance;
	//}
	AppSocket^ appSocket;
	Form_Client::ConnectServer^ connectScreen = nullptr; // connect form
	Form_Client::LogIn^ logInScreen = nullptr; // login form
	Form_Client::MainForm^ mainForm = nullptr;
	
	Thread^ threadListenClient;
	String^ userName = nullptr;

	int logIn(String^ userName, String^ passWord) {
		LogInClass^ logInAcc = gcnew LogInClass();
		logInAcc->userName = userName;
		logInAcc->passWord = passWord;
		
		array<Byte>^ buffer = logInAcc->pack();

		appSocket->sendMessage(buffer);
		return 0;
	}

	int signUp(String^ userName, String^ passWord) {
		SignUpClass^ signUpAcc = gcnew SignUpClass();
		signUpAcc->userName = userName;
		signUpAcc->passWord = passWord;
		array<Byte>^ buffer = signUpAcc->pack();
		appSocket->sendMessage(buffer);

		return 0;
	}

	int requestListOnlineUsers()
	{
		UserStatusClass^ userStatus = gcnew UserStatusClass();
		array<Byte>^ byteData = userStatus->pack();
		appSocket->sendMessage(byteData);

		return 0;
	}

	int logOut() {
		LogOutNotification^ logOut = gcnew LogOutNotification();
		logOut->userName = CentralController::getObject()->userName;
		array<Byte>^ data = logOut->pack();
		this->appSocket->sendMessage(data);


		return 0;
	}

	int sendPublicMassage(String^ message) {
		PublicChat^ publicMsg = gcnew PublicChat();
		publicMsg->message = message;
		array<Byte>^ data = publicMsg->pack();

		this->appSocket->sendMessage(data);
		return 0;
	}

	System::Void listenMessage() {
		while (1) {
			array<Byte>^ buffer = gcnew array<Byte>(1024);
			Socket^ clientSocket = CentralController::getObject()->appSocket->clientSocket;

			int receive;
			try {
				receive = clientSocket->Receive(buffer);
			}
			catch(Exception^ e){
				MessageBox::Show("Server has just disconnected!");
				//CentralController::getObject()->appSocket->clientSocket->Disconnect(true);
				CentralController::getObject()->appSocket->clientSocket = nullptr;
				Application::Exit();
				break;
			}

			StructClass^ messageReceived = ProcessApp::unpack(buffer);
			//MessageBox::Show(Convert::ToString(messageReceived->messageType));
			switch (messageReceived->messageType) {
			case StructClass::MessageType::LogIn:
				MessageBox::Show("Login message?");
				break;
			case StructClass::MessageType::ResponseLogin:
			{
				ResponseLogIn^ responseLogIn = (ResponseLogIn^)messageReceived;
				if (responseLogIn->isSuccessful) {
					MessageBox::Show("LogIn successfully!","Notification",MessageBoxButtons::OK);
					//CentralController::getObject()->connectScreen->Hide();
					CentralController::getObject()->logInScreen->Hide();
					CentralController::getObject()->mainForm = gcnew Form_Client::MainForm;
					CentralController::getObject()->mainForm->ShowDialog();
					// main screen show
				}
				else {
					MessageBox::Show(responseLogIn->errorMessage);
				}

				break;
			}
			case StructClass::MessageType::SignUp:
			{
				MessageBox::Show("Sign up received?");
				break;
			}
			case StructClass::MessageType::ResponseSignUp:
			{
				ResponseSignUp^ responseSignUp = (ResponseSignUp^)messageReceived;
				if (responseSignUp->isSuccessful) {
					MessageBox::Show("Registered successfully!","Notificaion");
					// main screen show
				}
				else {
					MessageBox::Show(responseSignUp->errorMessage);
				}

				break;
			}
			case StructClass::MessageType::LogInNotification:
			{
				LogInNotification^ logNoti = (LogInNotification^)messageReceived;
				CentralController::getObject()->mainForm->addTextToBoxChat(logNoti->userName + " has just online!");
				CentralController::getObject()->mainForm->addAnOnlineUser(logNoti->userName);
				break;
				

			}
			case StructClass::MessageType::LogOutNotification:
			{
				LogOutNotification^ logNoti = (LogOutNotification^)messageReceived;
				CentralController::getObject()->mainForm->addTextToBoxChat(logNoti->userName+ " has just offline!");
				CentralController::getObject()->mainForm->deleteAnOnline(logNoti->userName);
				break;
			}

			case StructClass::MessageType::UserStatus:
			{
				UserStatusClass^ userStatus = (UserStatusClass^)messageReceived;
				CentralController::getObject()->mainForm->setOnlineUsers(userStatus->listUser);
				break;
			}

			case StructClass::MessageType::PublicChat:
			{
				PublicChat^ publicMessage = (PublicChat^)messageReceived;
				CentralController::getObject()->mainForm->addTextToBoxChat(publicMessage->message);
				break;
			}

			case StructClass::MessageType::PrivateChat:
			{
				PrivateChat^ privateMessage = (PrivateChat^)messageReceived;
				CentralController::getObject()->setPrivateMessage(privateMessage->userNameReceiver, privateMessage->message);
				break;
			}

			case StructClass::MessageType::RequestSendFile:
			{
				RequestSendFile^ rqSendFile = (RequestSendFile^)messageReceived;
				if (MessageBox::Show(rqSendFile->userName + " want to send you a file " +
					rqSendFile->fileName + " (" + Convert::ToString(rqSendFile->iFileSize) +
					" bytes).\nDo you want to receive?", "Receive a file", MessageBoxButtons::YesNo) == DialogResult::Yes)
				{
					CentralController::getObject()->responseSendFile(rqSendFile->userName, true);
				}
				else
				{
					CentralController::getObject()->responseSendFile(rqSendFile->userName, false);
				}
				break;

			}
			case StructClass::MessageType::ResponseSendFile:
			{
				ResponseSendFile^ rpSendFile = (ResponseSendFile^)messageReceived;
				Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(rpSendFile->userName);
				if (rpSendFile->isAccept) {
					setPrivateMessage(rpSendFile->userName, rpSendFile->userName + " accept a file "
						+ prvChatForm->fileNameToSend + " (" + Convert::ToString(prvChatForm->fileSizeToSend) + " bytes) from you!");
					//setPrivateMessage(rpSendFile->userName, "Starting  process ");
					sendPrivateFile(prvChatForm->strFriendUsername, prvChatForm->fileNameToSend, prvChatForm->filePathToSend);
				}
				else
				{

					setPrivateMessage(rpSendFile->userName, rpSendFile->userName + " don't accept to receive file "
						+ prvChatForm->fileNameToSend + " (" + Convert::ToString(prvChatForm->fileSizeToSend) + " bytes) from you!");
				}
				break;

			}

			case StructClass::MessageType::PrivateFile:
			{
				try {
					PrivateFile^ prvFile = (PrivateFile^)messageReceived;
					//MessageBox::Show("debug private file");
					setPrivateMessage(prvFile->userName, "Received: " + prvFile->iPackageNumber + "/" + prvFile->iTotalPackage);
					Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(prvFile->userName);
					//MessageBox::Show("debug private file");
					if (prvFile->iPackageNumber == 1) {
						prvChatForm->writerStream = gcnew System::IO::FileStream(prvChatForm->pathFileToReceiver + prvFile->fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
					}
					prvChatForm->writerStream->Write(prvFile->bData, 0, prvFile->bData->Length);
					
		
				}
				catch (Exception^ e) {
					MessageBox::Show(e->Message, "Error Client(Private File)");
				}
				break;
			}

			default:
				break;
			}



		}

	}

	int createThreadListenMessageFromServer() {
		Thread^ thread = gcnew Thread(gcnew ThreadStart(this, &CentralController::listenMessage));
		thread->SetApartmentState(ApartmentState::STA);
		thread->Start();
		return 0;
	}

	// Send file
	int requestSendFile(String^ _ToUsername, String^ _FileName, int _iFileSize) {
		RequestSendFile^ rqSendFileStruct = gcnew RequestSendFile;
		rqSendFileStruct->fileName = _FileName;
		rqSendFileStruct->userName = _ToUsername;
		rqSendFileStruct->iFileSize = _iFileSize;
		array<Byte>^ byteData = rqSendFileStruct->pack();
		appSocket->sendMessage(byteData);
		return 0;
	}
	int responseSendFile(String^ _ToUsername, bool _IsAccept) {
		ResponseSendFile^ rpSendFileStruct = gcnew ResponseSendFile;
		rpSendFileStruct->userName = _ToUsername;
		rpSendFileStruct->isAccept = _IsAccept;
		array<Byte>^ byteData = rpSendFileStruct->pack();
		appSocket->sendMessage(byteData);
		return 0;
	}
	int sendPrivateFile(String^ _ToUsername, String^ _FileName, String^ _FilePath)
	{
		PrivateFile^ prvFile = gcnew PrivateFile;
		prvFile->fileName = _FileName;
		prvFile->userName = _ToUsername;
	
		//Spit to smaller packages to send to server

		array<Byte>^ buffer;

		System::IO::FileStream^ fileStream = nullptr;
		//System::IO::FileStream^ writeStream = gcnew System::IO::FileStream(_FileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			fileStream = gcnew System::IO::FileStream(_FilePath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
			//writeSteam = gcnew FileStream("Debug/" + _FilePath, FileMode::Create, FileAccess::Write);

			int length = (int)fileStream->Length;  // get file length
			buffer = gcnew array<Byte>(length);            // create buffer
			int count;                            // actual number of bytes read
			int sum = 0;                          // total number of bytes read
			//int SIZE = 512;
			// read until Read method returns 0 (end of the stream has been reached)
			while ((count = fileStream->Read(buffer,sum,length-sum)) >0)
			{
				sum += count;
			}

			int BUFF_SIZE = 512;
			int counter = 0;
			int curPackageNumber = 1;
			int iTotalPackage = sum / (BUFF_SIZE + 1) + 1;
			//Console::WriteLine("Start send file: ");
			for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
			{
				//System::Array::Copy(buffer, counter, bData, BUFF_SIZE);
				
				int copyLength = counter + BUFF_SIZE < sum ? BUFF_SIZE : (sum % BUFF_SIZE);
				array<Byte>^ bData = gcnew array<Byte>(copyLength);
				//MessageBox::Show(Convert::ToString(copyLength));
				System::Array::Copy(buffer, counter, bData, 0, copyLength);
				counter += BUFF_SIZE;
				//MessageBox::Show(Convert::ToString(bData->Length));

				prvFile->iPackageNumber = curPackageNumber;
				prvFile->iTotalPackage = iTotalPackage;
				prvFile->bData = bData;
				//MessageBox::Show(Convert::ToString(prvFile->iPackageNumber) + " "+ Convert::ToString(prvFile->iTotalPackage));
				//writeStream->Write(bData, 0, copyLength);
				array<Byte>^ byteData = prvFile->pack();
				//MessageBox::Show(Convert::ToString(byteData->Length));
				//if (byteData != nullptr)
				appSocket->sendMessage(byteData);
				

				//MessageBox::Show("Debug");
				setPrivateMessage(_ToUsername, "Sent: " + curPackageNumber + "/" + iTotalPackage);
				//appSocket->clientSocket->SySendPacketsElement(_FilePath);
				//writeSteam->Write(bData, 0, copyLength);
			}
			//Console::WriteLine("End of sending file");
			//CentralController::getObject()->appSocket->clientSocket->SendFile()
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message,"Send file");
		}
		finally
		{
			if (fileStream != nullptr)
				fileStream->Close();
		}


		return 0;
	}




	// Private Chat 
	List<Form_Client::PrivateChatForm^>^ lstPrivateChatForm = gcnew List<Form_Client::PrivateChatForm^>();
	
	int sendPrivateMessage(String^ _ToUsername, String^ _Message) {
		PrivateChat^ privateMessageStruct = gcnew PrivateChat;
		privateMessageStruct->userNameReceiver = _ToUsername;
		privateMessageStruct->message = _Message;

		array<Byte>^ byteData = privateMessageStruct->pack();
		appSocket->sendMessage(byteData);
		return 0;
	}

	int setPrivateMessage(String^ _ToUsername, String^ _Message)
	{
		Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
		if (prvChatForm != nullptr)
		{
			prvChatForm->addTextToDisplayChatBox(_Message);
		}
		else
		{
			Form_Client::PrivateChatForm^ pChat = gcnew Form_Client::PrivateChatForm(this->userName, _ToUsername);
			CentralController::getObject()->lstPrivateChatForm->Add(pChat);
			setPrivateMessage(_ToUsername, _Message); //Re set private message

			Application::Run(pChat);
			//threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(CentralController::threadPrivateChatForm));
			//threadListenClient->IsBackground = true;
			//threadListenClient->Start(pChat);
		}

		return 0;
	}

	//Others
	Form_Client::PrivateChatForm^ getPrivateChatFormByFriendUsername(String^ _Username) {
		for each (Form_Client::PrivateChatForm ^ prvChat in CentralController::getObject()->lstPrivateChatForm)
		{
			if (prvChat->strFriendUsername == _Username)
				return prvChat;
		}

		return nullptr; //not found

	}
	//void getFileToSendInfoByFriendUsername(String^& _FileName, String^& _FilePath, int& _iFileSize, String^ _Username);
	static void threadPrivateChatForm(Object^ obj) {
		MessageBox::Show("Debug thread");
		//How can I know my friend chat username. -> Solved!
		Form_Client::PrivateChatForm^ pChat = (Form_Client::PrivateChatForm^)obj;
		//Application::Run(pChat);
		//createThreadListenMessageFromServer();
		//MessageBox::Show("Debug");
		pChat->Show();
		MessageBox::Show("End Debug thread");
	}
	//Thread^ threadListenClient;
};

