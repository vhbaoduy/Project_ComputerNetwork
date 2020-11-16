#include "pch.h"
#include "MainForm.h"
#include "Server.h"


System::Void Form_Server::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	Server^ server = Server::getObject();

	this->textBox_IP->Text = server->serverIpAddress;
	this->textBox_Port->Text = Convert::ToString(server->serverPortAddress);
}

 System :: Void Form_Server::MainForm:: textBox_IP_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
 System::Void Form_Server:: MainForm ::  textBox_Port_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	 
}

 System::Void Form_Server::MainForm::button_RunServer_Click(System::Object^ sender, System::EventArgs^ e) {
	 if (!Server::getObject()->initializeSocket()) {
		 MessageBox::Show("Run Server successfully !", "Notification", MessageBoxButtons::OKCancel);
		 this->button_RunServer->Enabled = false;
	 }
 }
 System::Void Form_Server::MainForm::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	 //Socket^ serverSocket = Server::getObject()->serverSocket;

	 //while (true)
	 //{
		// Socket^ connectionSocket = serverSocket->Accept(); //Accept Connection From Client
		// //lstConnectionSocket->Add(connectionSocket); //Add connection Socket to list

		// threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(&MainForm::textBox_IP_TextChanged));
		// threadListenClient->IsBackground = true;
		// threadListenClient->Start(connectionSocket); //Listen messages from client

		// //String^ announce = L"Kết nối " + connectionSocket->RemoteEndPoint->ToString();
		// //AddTextToMainChat(announce);
		// this->listBox_Clients->Items->Add(L"connect");
	 //}
 }