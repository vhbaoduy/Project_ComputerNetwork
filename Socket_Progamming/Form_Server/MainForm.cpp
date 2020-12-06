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
		 this->textBox_IP->ReadOnly = true;
		 this->textBox_Port->ReadOnly = true;
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
				 if (logInAcc->isEncrypted) {
					 logInAcc->userName = convertHexToString(logInAcc->userName);
					 logInAcc->passWord = convertHexToString(logInAcc->passWord);
				 }
				 Server::getObject()->logIn(logInAcc->userName, logInAcc->passWord, socket);
				 break;
			 }
			 case StructClass::MessageType::SignUp:
			 {
				 SignUpClass^ signUpAcc = (SignUpClass^)messageReceived;
				 if (signUpAcc->isEncrypted) {
					 signUpAcc->userName = convertHexToString(signUpAcc->userName);
					 signUpAcc->passWord = convertHexToString(signUpAcc->passWord);
				 }
				 Server::getObject()->signUp(signUpAcc->userName, signUpAcc->passWord, socket);
				 break;

			 }

			 case StructClass::MessageType::ChangePassword:
			 {
				 ChangePasswordClass^ changePw = (ChangePasswordClass^)messageReceived;
				 if (changePw->isEncrypted) {
					 changePw->userName = convertHexToString(changePw->userName);
					 changePw->oldPassword = convertHexToString(changePw->oldPassword);
					 changePw->newPassword = convertHexToString(changePw->newPassword);
					 changePw->confirmPassword = convertHexToString(changePw->confirmPassword);
				 }
				 Server::getObject()->changePassword(changePw->userName, changePw->oldPassword, changePw->newPassword, changePw->confirmPassword, socket);
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

 String^ Form_Server::MainForm::convertStringToHex(String^ input)
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

 String^ Form_Server::MainForm::convertHexToString(String^ hexInput)
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
