#include "pch.h"
#include "MainForm.h"
#include "Server.h"


System::Void Form_Server::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	Server^ server = Server::getObject();

	this->textBox_IP->Text = server->serverIpAddress;
	this->textBox_Port->Text = Convert::ToString(server->serverPortAddress);
	this->textBox_listClients->Text = nullptr;

	this->updateConnectedClient(server->getListOfClient());
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
			 array<Byte>^ buffer = gcnew array<Byte>(1024);
			 int receive = socket->Receive(buffer);
			 //MessageBox::Show(Convert::ToString(buffer->Length));
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
			 case StructClass::MessageType::LogOutNotification:
			 {
				 LogOutNotification^ logOut = (LogOutNotification^)messageReceived;
				 Server::getObject()->sendLogOutNotification(logOut->userName,socket);
				 break;
			 }
			 case StructClass::MessageType::UserStatus:
			 {
				 //UserStatusClass^ userStatus = (UserStatusClass^)messageReceived;
				 Server::getObject()->userStatusResponse(socket);
				 break;
			 }

			 case StructClass::MessageType::PublicChat:
			 {
				 PublicChat^ publicMessage = (PublicChat^)messageReceived;
				 Server::getObject()->sendPublicMessageToClients(publicMessage->message,socket);
				 break;
			 }
			 case StructClass::MessageType::PrivateChat:
			 {
				 PrivateChat^ privateMsgStr = (PrivateChat^)messageReceived;
				 Server::getObject()->sendPrivateMessage(privateMsgStr->userNameReceiver, privateMsgStr->message, socket);

				 break;
			 }

			 case StructClass::MessageType::RequestSendFile:
			 {
				 RequestSendFile^ rqSendFileStruct = (RequestSendFile^)messageReceived;
				 //MessageBox::Show("Server received\nUsername: " + rqSendFileStruct->userName + "\nFile name: " + rqSendFileStruct->fileName + "\nFile size: " + Convert::ToString(rqSendFileStruct->iFileSize));
				 Server::getObject()->requestSendFile(rqSendFileStruct->userName, rqSendFileStruct->fileName, rqSendFileStruct->iFileSize, socket);
				 break;
			 }
			 case StructClass::MessageType::ResponseSendFile:
			 {
				 ResponseSendFile^ rpSendFileStruct = (ResponseSendFile^)messageReceived;
				 //MessageBox::Show("Server responsed\nUsername: " + rpSendFileStruct->userName + "isAccept: " + Convert::ToString(rpSendFileStruct->isAccept));
				 Server::getObject()->responseSendFile(rpSendFileStruct->userName, rpSendFileStruct->isAccept, socket);
				 break;
			 }

			 case StructClass::MessageType::PrivateFile:
			 {
				 try {
					 PrivateFile^ prvFile = (PrivateFile^)messageReceived;
					 //MessageBox::Show("debug private file");
					 Server::getObject()->sendPrivateFilePackage(prvFile->userName, prvFile->fileName, prvFile->iPackageNumber, prvFile->iTotalPackage, prvFile->bData, socket);

				 }
				 catch (Exception^e) {
					 MessageBox::Show(e->Message, "Error Server(Private File)");
				 }

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

 void Form_Server::MainForm::appendTextToChatBox(String^ text) {
	 this->textBox_chatBox->AppendText(text);
	 this->textBox_chatBox->AppendText("\r\n");

 }
