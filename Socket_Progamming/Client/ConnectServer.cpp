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
		MessageBox::Show("Connected!");
		controller->connectScreen->Hide();
		controller->logInScreen = gcnew LogIn;
		controller->logInScreen->Show();
		//Application::Run(controller->logInScreen);
	}


	else
		Application::Exit();

}