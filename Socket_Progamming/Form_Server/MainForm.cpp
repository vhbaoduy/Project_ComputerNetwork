#include "pch.h"
#include "MainForm.h"
#include "Server.h"


System::Void Form_Server::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	Server^ server = Server::getObject();

	this->textBox_IP->Text = server->serverIpAddress;
	this->textBox_Port->Text = Convert::ToString(server->serverPortAddress);
	this->textBox_listClients->Text = nullptr;


	this->updateConnectedClient(server->getListOfClient());
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

	 backgroundWorker1->WorkerSupportsCancellation = true;
	 backgroundWorker1->RunWorkerAsync();
 }
 void Form_Server::MainForm::listenMessenger(Object^ obj) {
	 Socket^ socket = (Socket^)obj;
	 while (1) {
		 array<Byte>^ buffer = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
		 int receive = socket->Receive(buffer);
		 StructClass^ messageReceived = ProcessApp::unpack(buffer);



		 switch (messageReceived->messageType)
		 {
		 case StructClass::MessageType::LogIn:
		 {
			 Account^ logInAcc = (Account ^)messageReceived;
			 Server::getObject()->logIn(logInAcc->userName, logInAcc->passWord,socket);
			 break;
		 }
		 case StructClass:: MessageType :: SignUp:
		 {
			 Account^ signUpAcc = (Account^)messageReceived;
			 Server::getObject()->signUp(signUpAcc->userName, signUpAcc->passWord, socket);
			 break;

		 }

		 
		 default:
			 break;
		 }


	 }
	
 }
 System::Void Form_Server::MainForm::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	 Socket^ serverSocket = Server::getObject()->serverSocket;

	 while (true)
	 {
		 Socket^ connectionSocket = serverSocket->Accept(); //Accept Connection From Client
		 //lstConnectionSocket->Add(connectionSocket); //Add connection Socket to list

		 threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(MainForm::listenMessenger));
		 threadListenClient->IsBackground = true;
		 threadListenClient->Start(connectionSocket); //Listen messages from client

	 }
 }


 void Form_Server::MainForm::updateConnectedClient(List<String^>^ clients) {
	 this->textBox_listClients = nullptr;
	 for each (String^ userName in clients) {
		 this->textBox_listClients->AppendText(userName);
		 this->textBox_listClients->AppendText("\n");
	 }

}

 void Form_Server::MainForm::appendTextToBoxChat(String^ text) {
	 this->textBox_boxChat->AppendText(text);
	 this->textBox_boxChat->AppendText("\n");

 }
