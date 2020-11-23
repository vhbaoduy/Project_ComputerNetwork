#pragma once
#include "..\Struct\Header.h"

#include "LogIn.h"
#include "ConnectServer.h"
#include "AppSocket.h"
#include "MainForm.h"


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
	System::Void listenMessage() {
		while (1) {
			array<Byte>^ buffer = gcnew array<Byte>(512);
			Socket^ clientSocket = CentralController::getObject()->appSocket->clientSocket;

			int receive;
			try {
				receive = clientSocket->Receive(buffer);
			}
			catch(Exception^ e){
				MessageBox::Show("Server has just disconnected!");
				CentralController::getObject()->appSocket->clientSocket = nullptr;
				Application::Exit();
				break;
			}

			StructClass^ messagedReceived = ProcessApp::unpack(buffer);

			switch (messagedReceived->messageType) {
			case StructClass::MessageType::LogIn:
				MessageBox::Show("Login message?");
				break;
			case StructClass::MessageType::ResponseLogin:
			{
				ResponseLogIn^ responseLogIn = (ResponseLogIn^)messagedReceived;
				if (responseLogIn->isSuccessful) {
					MessageBox::Show("LogIn successfully!");
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
				ResponseSignUp^ responseSignUp = (ResponseSignUp^)messagedReceived;
				if (responseSignUp->isSuccessful) {
					MessageBox::Show("Registered successfully!");
					// main screen show
				}
				else {
					MessageBox::Show(responseSignUp->errorMessage);
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



};

