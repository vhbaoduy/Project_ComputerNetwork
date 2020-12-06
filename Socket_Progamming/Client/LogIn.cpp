#include "pch.h"
#include "LogIn.h"
#include "CentralController.h"

System::Void Form_Client::LogIn::LogIn_Load(System::Object^ sender, System::EventArgs^ e) {
	//if (CentralController::getObject()->appSocket->connectToServer()!=0) //Connect to server
	//{
	//	Application::Exit(); //Exit app
	//}
	CentralController::getObject()->createThreadListenMessageFromServer();
}
System::Void Form_Client::LogIn::button_LogIn_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ userName = this->textBox_UserName->Text;
	String^ passWord = this->textBox_Password->Text;
	CentralController::getObject()->logIn(userName, passWord);
	CentralController::getObject()->userName = userName;
	//CentralController::getObject()->createThreadListenMessageFromServer();
}


System::Void Form_Client::LogIn::button_SignUp_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ userName = this->textBox_UserName->Text;
	String^ passWord = this->textBox_Password->Text;

	CentralController::getObject()->signUp(userName, passWord);
	
	//CentralController::getObject()->createThreadListenMessageFromServer();
}


