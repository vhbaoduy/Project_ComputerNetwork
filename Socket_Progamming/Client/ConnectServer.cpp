#include "pch.h"
#include "ConnectServer.h"
#include "CentralController.h"

System::Void Form_Client::ConnectServer::ConnectServer_Load(System::Object^ sender, System::EventArgs^ e) {
	
}
System::Void Form_Client::ConnectServer::button_connect_Click(System::Object^ sender, System::EventArgs^ e) {

	String^ ipAddr = this->textBox_IP->Text->ToString();
	int portAddr = Convert::ToInt32(this->textBox_Port->Text->ToString());
	CentralController^ controller = CentralController::getObject();
	controller->appSocket = gcnew AppSocket(ipAddr,portAddr);
	if (!controller->appSocket->connectToServer() && controller->appSocket != nullptr && controller->appSocket->clientSocket != nullptr) {
		MessageBox::Show("Connected Successfully!","Notification");
		controller->connectScreen->Hide();
		controller->logInScreen = gcnew Form_Client::LogIn;
		controller->logInScreen->Show();
		//controller->connectScreen->();
		//Application::Run(controller->logInScreen);
	}


	else
		Application::Exit();

}

System::Void Form_Client::ConnectServer::ConnectServer_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	//CentralController::getObject()->logOut();
	//CentralController::getObject()->appSocket->clientSocket->Disconnect(false);
	//CentralController::getObject()->appSocket->clientSocket = nullptr;
	//Application::ExitThread();
	//Application::Exit();
}
System::Void Form_Client::ConnectServer::ConnectServer_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	//CentralController::getObject()->logOut();
	

}