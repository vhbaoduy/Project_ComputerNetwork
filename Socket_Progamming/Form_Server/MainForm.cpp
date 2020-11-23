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
	 Server^ controller = Server::getObject();
	 
	 if (!controller->initializeSocket()) {
		 MessageBox::Show("Run Server successfully !", "Notification", MessageBoxButtons::OKCancel);
		 this->button_RunServer->Enabled = false;
	 }

	 backgroundWorker1->WorkerSupportsCancellation = true;
	 backgroundWorker1->RunWorkerAsync();
 }
 void Form_Server::MainForm::listenMessage(Object^ obj) {
	 Socket^ socket = (Socket^)obj;
	 while (1) {
		 try {
			 array<Byte>^ buffer = gcnew array<Byte>(512);
			 int receive = socket->Receive(buffer);
			 StructClass^ messageReceived = ProcessApp::unpack(buffer);



			 switch (messageReceived->messageType)
			 {
			 case StructClass::MessageType::LogIn:
			 {
				 LogInClass^ logInAcc = (LogInClass^)messageReceived;
				 Server::getObject()->logIn(logInAcc->userName, logInAcc->passWord, socket);
				 break;
			 }
			 case StructClass::MessageType::SignUp:
			 {
				 SignUpClass^ signUpAcc = (SignUpClass^)messageReceived;
				 Server::getObject()->signUp(signUpAcc->userName, signUpAcc->passWord, socket);
				 break;

			 }


			 default:
				 break;
			 }
		 }
		 catch(Exception^ e){
			 MessageBox::Show(e->Message,"Error server");
			 return;

		 }


	 }
	
 }
 System::Void Form_Server::MainForm::backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {

	 Socket^ serverSocket = Server::getObject()->serverSocket;

	 while (true)
	 {
		 Socket^ connectionSocket = serverSocket->Accept(); //Accept Connection From Client
		 //lstConnectionSocket->Add(connectionSocket); //Add connection Socket to list

		 threadListenClient = gcnew Thread(gcnew ParameterizedThreadStart(&MainForm::listenMessage));
		 threadListenClient->IsBackground = true;
		 threadListenClient->Start(connectionSocket); //Listen messages from client

	 }
 }


 void Form_Server::MainForm::updateConnectedClient(List<String^>^ clients) {
	 this->textBox_listClients->Text = nullptr;
	 for each (String^ userName in clients) {
		 this->textBox_listClients->AppendText(userName);
		 this->textBox_listClients->AppendText("\r\n");
	 }

}

 void Form_Server::MainForm::appendTextToBoxChat(String^ text) {
	 this->textBox_boxChat->AppendText(text);
	 this->textBox_boxChat->AppendText("\r\n");

 }
