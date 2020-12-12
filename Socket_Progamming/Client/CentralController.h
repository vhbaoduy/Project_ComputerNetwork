#pragma once
#include "..\Struct\Header.h"

#include "LogIn.h"
#include "ConnectServer.h"
#include "AppSocket.h"
#include "MainForm.h"
#include "PrivateChatForm.h"
#include "ChangePasswordForm.h"
#include "SetInforForm.h"
#include "PublicFileForm.h"

#define DEFAULT_BUFFER_LENGTH 2560
#define BUFFER_SIZE 2048

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
	Form_Client::ChangePasswordForm^ changePasswordForm = nullptr;
	Form_Client::SetInforForm^ setInforForm = nullptr;
	Form_Client::PublicFileForm^ publicFileForm = nullptr;
	
	Thread^ threadListenClient;
	String^ userName = nullptr;
	bool flagLogIn;
	bool flagSignUp;
	bool flagChangePassword;
	int logIn(String^ userName, String^ passWord) {
		LogInClass^ logInAcc = gcnew LogInClass();
		logInAcc->userName = userName;
		logInAcc->passWord = passWord;
		flagLogIn = false;
		if (MessageBox::Show("Do you want to encrypt message before sending ?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes) {
			logInAcc->isEncrypted = true;
			logInAcc->userName = convertStringToHex(userName);
			logInAcc->passWord = convertStringToHex(passWord);
			flagLogIn = true;
		}

		array<Byte>^ buffer = logInAcc->pack();

		appSocket->sendMessage(buffer);
		return 0;
	}

	int signUp(String^ userName, String^ passWord) {
		SignUpClass^ signUpAcc = gcnew SignUpClass();
		signUpAcc->userName = userName;
		signUpAcc->passWord = passWord;
		flagSignUp = false;
		if (MessageBox::Show("Do you want to encrypt message before sending ?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes) {
			signUpAcc->isEncrypted = true;
			signUpAcc->userName = convertStringToHex(userName);
			signUpAcc->passWord = convertStringToHex(passWord);
			flagSignUp = true;
		}
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

	int changePassword(String^ userName,String^ oldPw,String^ newPw,String^ confirmPw) {
		ChangePasswordClass^ changePw = gcnew ChangePasswordClass();
		changePw->userName = userName;
		changePw->oldPassword = oldPw;
		changePw->newPassword = newPw;
		changePw->confirmPassword = confirmPw;
		flagChangePassword = false;
		if (MessageBox::Show("Do you want to encrypt message before sending ?", "Notification", MessageBoxButtons::YesNo) == DialogResult::Yes) {
			changePw->isEncrypted = true;
			changePw->userName = convertStringToHex(userName);
			changePw->oldPassword = convertStringToHex(oldPw);
			changePw->newPassword = convertStringToHex(newPw);
			changePw->confirmPassword = convertStringToHex(confirmPw);
			flagChangePassword = true;
		}

		array<Byte>^ data = changePw->pack();
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
			array<Byte>^ buffer = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
			Socket^ clientSocket = CentralController::getObject()->appSocket->clientSocket;

			int receive;
			try {
				receive = clientSocket->Receive(buffer);
			}
			catch(Exception^ e){
				//MessageBox::Show("Server has just disconnected!");
				//CentralController::getObject()->appSocket->clientSocket->Disconnect(true);
				CentralController::getObject()->appSocket->clientSocket = nullptr;
				Application::Exit();
				break;
			}

			StructClass^ messageReceived = ProcessApp::unpack(buffer);
			//MessageBox::Show(Convert::ToString(messageReceived->messageType));
			if (messageReceived == nullptr) {
				//MessageBox::Show("Mess null client");
				continue;
			}
			switch (messageReceived->messageType) {
			case StructClass::MessageType::LogIn:
				MessageBox::Show("Login message?");
				
				break;
			case StructClass::MessageType::ResponseLogin:
			{
				ResponseLogIn^ responseLogIn = (ResponseLogIn^)messageReceived;
				if (responseLogIn->isSuccessful) {
					if (flagLogIn) {
						MessageBox::Show("LogIn successfully! \n Wellcome to server and Message was encrypted.", "Notification", MessageBoxButtons::OK);
					}
					else
						MessageBox::Show("LogIn successfully! \n Wellcome to server and Message wasn't encrypted.", "Notification", MessageBoxButtons::OK);


					CentralController::getObject()->connectScreen->Close();
					CentralController::getObject()->logInScreen->Close();
					CentralController::getObject()->mainForm = gcnew Form_Client::MainForm;
					//CentralController::getObject()->mainForm->Show();
					Application::Run(CentralController::getObject()->mainForm);
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
					if (flagSignUp) {
						MessageBox::Show("Register successfully and Message was encrypted.", "Notification", MessageBoxButtons::OK);
					}
					else
						MessageBox::Show("Register successfully and Message wasn't encrypted.", "Notification", MessageBoxButtons::OK);

				}
				else {
					MessageBox::Show(responseSignUp->errorMessage);
				}
				
				break;
			}
			case StructClass ::MessageType :: ChangePassword:
				break;
			case StructClass::MessageType::ResponseChangePassword:
			{
				ResponseChangePassword^ resChangePw = (ResponseChangePassword^)messageReceived;
				if (resChangePw->isSuccessful) {
					if (flagChangePassword) {
						MessageBox::Show("Changed password successfully and Message was encrypted.", "Notification", MessageBoxButtons::OK);
						
					}
					else
						MessageBox::Show("Changed password successfully and Message wasn't encrypted.", "Notification", MessageBoxButtons::OK);
					CentralController::getObject()->changePasswordForm->Close();
				}
				else {
					MessageBox::Show(resChangePw->errorMessage);
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


			case StructClass::MessageType::ListPublicFileName:
			{
				ListPublicFileNameClass^ fileName = (ListPublicFileNameClass^)messageReceived;
				if (fileName->listFileName != nullptr)
					CentralController::getObject()->publicFileForm->setListFileName(fileName->listFileName);

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
			case StructClass::MessageType::ResponseInfor:
			{
				ResponseInforClass^ resInfor = (ResponseInforClass^)messageReceived;
				MessageBox::Show("Name: " + resInfor->friendUsername + "\nBirthdate: " + resInfor->birthDate, "Information");
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
					setPrivateMessage(prvFile->userName, "Receiving...");
					Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(prvFile->userName);
					//else
						//setPrivateMessage(prvFile->userName, nullptr);
					if (prvFile->iPackageNumber == 1) {
						CentralController::getObject()->createThreadListenMessageFromServer();
						prvChatForm->setUpProcessBar(1, prvFile->iTotalPackage);
						prvChatForm->writerStream = gcnew System::IO::FileStream(prvChatForm->pathFileToReceiver + prvFile->fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);

					}
					//prvChatForm->fileSizeToSend += prvFile->bData->Length;
					prvChatForm->writerStream->Write(prvFile->bData, 0, prvFile->bData->Length);
					//System::IO::File::WriteAllBytes(prvChatForm->pathFileToReceiver + prvFile->fileName, prvFile->bData);
					prvChatForm->setValueOfProcessBar(prvFile->iPackageNumber);

					if (prvFile->iPackageNumber == prvFile->iTotalPackage) {
						setPrivateMessage(prvFile->userName, "Received " + prvFile->fileName + "(" + Convert::ToString((int)prvChatForm->writerStream->Length) + "bytes)  successfully !");
						prvChatForm->resetProcessBar();
						prvChatForm->writerStream->Close();
						prvChatForm->writerStream = nullptr;
					}
					break;

				}
				catch (Exception^ e) {
					MessageBox::Show(e->Message, "Error Client(Receice Private File)");
				}
				
				

			}
			case StructClass::MessageType::DownloadPublicFile:
			{
				DownloadPublicFileClass^ pubFile = (DownloadPublicFileClass^)messageReceived;
				try{
					
					if (pubFile->iPackageNumber == 1) {
						CentralController::getObject()->createThreadListenMessageFromServer();
						
						CentralController::getObject()->publicFileForm->writerStream = gcnew System::IO::FileStream(CentralController::getObject()->publicFileForm->pathFileToReceiver + CentralController::getObject()->publicFileForm->fileNameToReceive, System::IO::FileMode::Create, System::IO::FileAccess::Write);
						//CentralController::getObject()->publicFileForm->setUpProcessBar(1, pubFile->iTotalPackage);
					}
					//CentralController::getObject()->publicFileForm->writerStream = System::IO::File::OpenWrite(CentralController::getObject()->publicFileForm->pathFileToReceiver + CentralController::getObject()->publicFileForm->fileNameToReceive);
					CentralController::getObject()->publicFileForm->writerStream->Write(pubFile->bData, 0, pubFile->bData->Length);
					//System::IO::File::WriteAllBytes(CentralController::getObject()->publicFileForm->pathFileToReceiver + CentralController::getObject()->publicFileForm->fileNameToReceive, pubFile->bData);
					//CentralController::getObject()->publicFileForm->setValueOfProcessBar(pubFile->iPackageNumber);
					if (pubFile->iPackageNumber == pubFile->iTotalPackage) {
						//CentralController::getObject()->publicFileForm->resetProcessBar();
						if (pubFile->iFileSize == (int)CentralController::getObject()->publicFileForm->writerStream->Length)
							MessageBox::Show("Downloaded " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + ") bytes successfully!", "Notification");
						else
							MessageBox::Show("Downloaded " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + ") bytes (missed " + Convert::ToString(pubFile->iFileSize - (int)CentralController::getObject()->publicFileForm->writerStream->Length) + "bytes)!", "Notification");
						CentralController::getObject()->publicFileForm->writerStream->Close();
						CentralController::getObject()->publicFileForm->writerStream = nullptr;
						
						
					}

				}

				catch (Exception^ e) {
					//CentralController::getObject()->publicFileForm->writerStream->Close();
					//CentralController::getObject()->publicFileForm->writerStream = nullptr;
					MessageBox::Show(e->Message, "Error Client(Receive Public File)");
				}
				break;
			}

			default:
				break;
			}

			delete[] buffer;
			
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
		CentralController::getObject()->createThreadListenMessageFromServer();
		Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
		//setPrivateMessage(_ToUsername, "Sending...");
		//setPrivateMessage(_ToUsername, "Sending...");
		PrivateFile^ prvFile = gcnew PrivateFile;
		prvFile->fileName = _FileName;
		prvFile->userName = _ToUsername;
		//Spit to smaller packages to send to server
		array<Byte>^ buffer;

		System::IO::FileStream^ fileStream = nullptr;
		//System::IO::FileStream^ writeStream = gcnew System::IO::FileStream(_FileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			//fileStream = gcnew System::IO::FileStream(_FilePath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
			////writeSteam = gcnew FileStream("Debug/" + _FilePath, FileMode::Create, FileAccess::Write);

			//int length = (int)fileStream->Length;  // get file length
   //        // create buffer
			//int count;                            // actual number of bytes read
			//int sum = 0;                          // total number of bytes read
			//int SIZE = 512;
			// read until Read method returns 0 (end of the stream has been reached)
			/*int curPackageNumber = 1;
			int iTotalPackage = length / (BUFFER_SIZE + 1) + 1;
			prvChatForm->setUpProcessBar(1, iTotalPackage);
			while (1) {
				buffer = gcnew array<Byte>(BUFFER_SIZE);
				count = fileStream->Read(buffer, 0, BUFFER_SIZE);
				if (count == 0)
					break;
				else {
					prvFile->bData = gcnew array<Byte>(count);
					System::Array::Copy(buffer, 0, prvFile->bData, 0, count);
					prvFile->iPackageNumber = curPackageNumber;
					prvFile->iTotalPackage = iTotalPackage;
					array<Byte>^ byteData = prvFile->pack();
					setPrivateMessage(_ToUsername, "Sending...");
					CentralController::getObject()->appSocket->sendMessage(byteData);
					prvChatForm->setValueOfProcessBar(curPackageNumber++);
					delete[] prvFile->bData;
				}



				delete[] buffer;
			}*/


			//buffer = gcnew array<Byte>(length);
			//while (length > 0) {
			//	count = fileStream->Read(buffer, sum, length);
			//	if (count == 0)
			//		break;
			//	sum += count;
			//	length -= count;
			//}
			//length = buffer->Length;


			//while ((count = fileStream->Read(buffer,sum,length-sum)) >0)
			//{
			//	sum += count;
			//}
			buffer = System::IO::File::ReadAllBytes(_FilePath);
			int sum = buffer->Length;
			int counter = 0;
			int curPackageNumber = 1;
			int iTotalPackage = sum / (BUFFER_SIZE + 1) + 1;
			prvChatForm->setUpProcessBar(1, iTotalPackage);
			for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
			{

				int copyLength = BUFFER_SIZE < sum ? BUFFER_SIZE : (sum % BUFFER_SIZE);
				sum -= copyLength;
				prvFile->bData = gcnew array<Byte>(copyLength);
				System::Array::Copy(buffer, counter, prvFile->bData, 0, copyLength);
				counter += copyLength;

				prvFile->iPackageNumber = curPackageNumber;
				prvFile->iTotalPackage = iTotalPackage;
				array<Byte>^ byteData = prvFile->pack();
				setPrivateMessage(_ToUsername, "Sending...");
				CentralController::getObject()->appSocket->sendMessage(byteData);
				prvChatForm->setValueOfProcessBar(curPackageNumber);
				delete[] prvFile->bData;
			}
			delete[] buffer;
			
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message,"Send file");
		}
		finally
		{
			prvChatForm->resetProcessBar();
			setPrivateMessage(_ToUsername, "Sent " + _FileName + "(" + Convert::ToString(prvChatForm->fileSizeToSend) + "bytes)  successfully !");
			/*if (fileStream != nullptr) {
				fileStream->Close();
				prvChatForm->resetProcessBar();
				setPrivateMessage(_ToUsername, "Sent " + _FileName + "(" + Convert::ToString(prvChatForm->fileSizeToSend) + "bytes)  successfully !");
			}*/
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
	int setPrivateMessage(String^ _ToUsername)
	{
		Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
		if (prvChatForm != nullptr)
		{
		}
		else
		{
			Form_Client::PrivateChatForm^ pChat = gcnew Form_Client::PrivateChatForm(this->userName, _ToUsername);
			CentralController::getObject()->lstPrivateChatForm->Add(pChat);
			Application::Run(pChat);
			//threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(CentralController::threadPrivateChatForm));
			//threadListenClient->IsBackground = true;
			//threadListenClient->Start(pChat);
		}

		return 0;
	}
	int setPrivateFileProcess(String^ _ToUsername, int value)
	{
		Form_Client::PrivateChatForm^ prvChatForm = getPrivateChatFormByFriendUsername(_ToUsername);
		if (prvChatForm != nullptr)
		{
			prvChatForm->setValueOfProcessBar(value);
		}
		else
		{
			Form_Client::PrivateChatForm^ pChat = gcnew Form_Client::PrivateChatForm(this->userName, _ToUsername);
			CentralController::getObject()->lstPrivateChatForm->Add(pChat);
			setPrivateFileProcess(_ToUsername, value); //Re set private message

			Application::Run(pChat);
			//threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(CentralController::threadPrivateChatForm));
			//threadListenClient->IsBackground = true;
			//threadListenClient->Start(pChat);
		}

		return 0;
	}

	int setInfor(String^ _Username, String^ _Birthdate)
	{
		SetInforClass^ setInfor = gcnew SetInforClass();
		setInfor->userName = _Username;
		setInfor->birthDate = _Birthdate;

		array<Byte>^ byteData = setInfor->pack();
		appSocket->sendMessage(byteData);
		return 0;
	}

	int requestInfor(String^ _friendUsername)
	{
		RequestInforClass^ inforFriend = gcnew RequestInforClass();
		inforFriend->friendUsername = _friendUsername;
		array<Byte>^ byteData = inforFriend->pack();
		appSocket->sendMessage(byteData);
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
	static String^ convertStringToHex(String^ input)
	{
		List<Byte>^ stringBytes = gcnew List<Byte>();
		stringBytes->AddRange(Encoding::UTF8->GetBytes(input));
		// Byte[] stringBytes = encoding.GetBytes(input);
		array<Byte>^ temp = stringBytes->ToArray();
		StringBuilder^ sbBytes = gcnew StringBuilder(temp->Length * 2);
		for each (Byte b in temp)
		{
			sbBytes->AppendFormat("{0:X2}", b);
		}
		return sbBytes->ToString();
	}

	static String^ convertHexToString(String^ hexInput)
	{
		int numberChars = hexInput->Length;
		array<Byte>^ bytes = gcnew array<Byte>(numberChars / 2);
		// byte[] bytes = new byte[numberChars / 2];
		for (int i = 0; i < numberChars; i += 2)
		{
			bytes[i / 2] = Convert::ToByte(hexInput->Substring(i, 2), 16);
		}
		return Encoding::UTF8->GetString(bytes);
	}
	//Thread^ threadListenClient;

	int requestListPublicFileName()
	{
		ListPublicFileNameClass^ fileName = gcnew ListPublicFileNameClass();
		array<Byte>^ byteData = fileName->pack();
		appSocket->sendMessage(byteData);

		return 0;
	}

	int requestDownloadPublicFile(String^ fileName) {
		RequestSendPublicFileClass^ rqFile = gcnew RequestSendPublicFileClass();
		rqFile->fileName = fileName;
		array<Byte>^ byteData = rqFile->pack();
		appSocket->sendMessage(byteData);
		return 0;
	}

	int receiveFileFormServer(DownloadPublicFileClass^& pubFile) {
		//DownloadPublicFileClass^ pubFile = (DownloadPublicFileClass^)messageReceived;
		if (pubFile->iPackageNumber == 1) {
			//CentralController::getObject()->createThreadListenMessageFromServer();
			CentralController::getObject()->publicFileForm->writerStream = gcnew System::IO::FileStream(CentralController::getObject()->publicFileForm->pathFileToReceiver + CentralController::getObject()->publicFileForm->fileNameToReceive, System::IO::FileMode::Create, System::IO::FileAccess::Write);
			CentralController::getObject()->publicFileForm->setUpProcessBar(1, pubFile->iTotalPackage);
		}
		CentralController::getObject()->publicFileForm->writerStream->Write(pubFile->bData, 0, pubFile->bData->Length);
		CentralController::getObject()->publicFileForm->setValueOfProcessBar(pubFile->iPackageNumber);

		if (pubFile->iPackageNumber == pubFile->iTotalPackage) {
			if (pubFile->iFileSize == (int)CentralController::getObject()->publicFileForm->writerStream->Length)
				MessageBox::Show("Downloaded " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + ") bytes successfully!", "Notification");
			else
				MessageBox::Show("Downloaded " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + ") bytes (missed " + Convert::ToString(pubFile->iFileSize - (int)CentralController::getObject()->publicFileForm->writerStream->Length) + "bytes)", "Notification");
			CentralController::getObject()->publicFileForm->writerStream->Close();
			CentralController::getObject()->publicFileForm->writerStream = nullptr;
			CentralController::getObject()->publicFileForm->resetProcessBar();
		}

		return 0;

	}

	void uploadPublicFileToServer(String^ filePath, String^ fileName) {
		//CentralController::getObject()->createThreadListenMessageFromServer();
		//CentralController::getObject()->createThreadListenMessageFromServer();
		UploadPublicFileClass^ pubFile = gcnew UploadPublicFileClass();

		//Spit to smaller packages to send to server
		//array<Byte>^ buffer;
		array<Byte>^ buffer = System::IO::File::ReadAllBytes(filePath);
		pubFile->fileName = fileName;
		pubFile->iFileSize = buffer->Length;
		int check = 0;
		//System::IO::FileStream^ fileStream = nullptr;
		//System::IO::FileStream^ writeStream = gcnew System::IO::FileStream(_FileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
		try
		{
			//fileStream = gcnew System::IO::FileStream(filePath, System::IO::FileMode::Open, System::IO::FileAccess::Read);
			//writeSteam = gcnew FileStream("Debug/" + _FilePath, FileMode::Create, FileAccess::Write);

			//int length = (int)fileStream->Length;  // get file length
		   // create buffer
			//int count;                            // actual number of bytes read
			//int sum = 0;                          // total number of bytes read


			
			/*
			int counter = 0;
			int curPackageNumber = 1;
			int iTotalPackage = length / (BUFFER_SIZE + 1) + 1;
			CentralController::getObject()->publicFileForm->setUpProcessBar(1, iTotalPackage);
			pubFile->iTotalPackage = iTotalPackage;

			while (curPackageNumber <= iTotalPackage) {
				buffer = gcnew array<Byte>(BUFFER_SIZE);
				count = fileStream->Read(buffer, 0, BUFFER_SIZE);

				if (count == 0)
					break;
				else {
					pubFile->bData = gcnew array<Byte>(count);
					System::Array::Copy(buffer, 0, pubFile->bData, 0, count);
					pubFile->iPackageNumber = curPackageNumber;
					array<Byte>^ byteData = pubFile->pack();
					CentralController::getObject()->appSocket->sendMessage(byteData);
					CentralController::getObject()->publicFileForm->setValueOfProcessBar(curPackageNumber++);

					delete[]pubFile->bData;

				}
				delete[] buffer;
			}*/
			//length = buffer->Length;

			//buffer = gcnew array<Byte>(length);
			//while ((count = fileStream->Read(buffer,sum,length-sum)) >0)
			//{
			//	sum += count;
			//}
			int counter = 0;
			int curPackageNumber = 1;
			int sum = buffer->Length;
			int iTotalPackage = buffer->Length / (BUFFER_SIZE ) + 1;

			//MessageBox::Show(Convert::ToString(sum));
			CentralController::getObject()->publicFileForm->setUpProcessBar(1, iTotalPackage);
			for (; curPackageNumber <= iTotalPackage; ++curPackageNumber)
			{

				int copyLength = BUFFER_SIZE < sum ? BUFFER_SIZE : (sum % BUFFER_SIZE);
				sum -= copyLength;
				array<Byte>^ bData = gcnew array<Byte>(copyLength);
				System::Array::Copy(buffer, counter, bData, 0, copyLength);
				counter += copyLength;

				pubFile->bData = bData;
				check += bData->Length;
				pubFile->iPackageNumber = curPackageNumber;
				pubFile->iTotalPackage = iTotalPackage;
				array<Byte>^ byteData = pubFile->pack();
				CentralController::getObject()->appSocket->sendMessage(byteData);
				CentralController::getObject()->publicFileForm->setValueOfProcessBar(curPackageNumber);
				delete[] pubFile->bData;
			}
			



		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message, "Send public file");
		}
		finally
		{
		
			CentralController::getObject()->requestListPublicFileName();
			CentralController::getObject()->publicFileForm->resetProcessBar();
			if (check == buffer->Length)
				MessageBox::Show("Uploaded " + fileName + "(" + Convert::ToString(check) + ") bytes sucessfully!", "Notification");


			delete[] buffer;
			//CentralController::getObject()->requestListPublicFileName();
			//CentralController::getObject()->publicFileForm->resetProcessBar();
	/*		if (fileStream != nullptr) {
				fileStream->Close();
				CentralController::getObject()->requestListPublicFileName();
				CentralController::getObject()->publicFileForm->resetProcessBar();
			}*/
		}

	}
};

