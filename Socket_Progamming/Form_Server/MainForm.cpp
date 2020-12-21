#include "pch.h"
#include "MainForm.h"
#include "Server.h"


System::Void Form_Server::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	Server^ server = Server::getObject();


	
	this->textBox_listClients->Text = nullptr;

	this->updateConnectedClient(server->getListOfClient());
	//this->updateConnectedClient(server->getListOfClient());
}

 System :: Void Form_Server::MainForm:: textBox_IP_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	
}
 System::Void Form_Server:: MainForm ::  textBox_Port_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	 
}

 System::Void Form_Server::MainForm::button_RunServer_Click(System::Object^ sender, System::EventArgs^ e) {
	 //Server^ controller = Server::getObject();
	 //controller->serverIpAddress = this->textBox_IP->Text;
	 //controller->serverPortAddress = Convert::ToInt32(this->textBox_Port->Text);
	 //this->textBox_IP->ReadOnly = true;
	 //this->textBox_Port->ReadOnly = true;

	 Server^ server = Server::getObject();
	 server->serverIpAddress = this->textBox_IP->Text;
	 server->serverPortAddress = Convert::ToInt32(this->textBox_Port->Text);

	/* IPAddress^ serverIpAddress = IPAddress::Parse(server->serverIpAddress);
	 int serverPort = server->serverPortAddress;
	 IPEndPoint^ serverIpEndPoint = gcnew IPEndPoint(serverIpAddress, serverPort);

	 server->serverSocket->Bind(serverIpEndPoint);
	 server->serverSocket->Listen(10);*/
	 if (!server->initializeSocket()) {
	 MessageBox::Show("Run Server successfully !", "Notification", MessageBoxButtons::OKCancel);
	 this->button_RunServer->Enabled = false;
	 this->textBox_IP->Text = server->serverIpAddress;
	 this->textBox_Port->Text = Convert::ToString(server->serverPortAddress);
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
			 array<Byte>^ buffer = gcnew array<Byte>(DEFAULT_BUFFER_LENGTH);
			 int receive = socket->Receive(buffer);
			 //MessageBox::Show(Convert::ToString(buffer->Length));
			 StructClass^ messageReceived = ProcessApp::unpack(buffer);
			 if (messageReceived == nullptr) {
				 //MessageBox::Show(Convert::ToString(buffer->Length));
				//MessageBox::Show("mess null");
				 //StructClass::MessageType messageType = (StructClass::MessageType)BitConverter::ToInt32(buffer, 0);
				 //ResponsePackageClass^ rpPackage = gcnew ResponsePackageClass();
				 //Server::getObject()->soc
				 //array<Byte>^ data = rpPackage->pack();
				 //socket->Send(data);
				 continue;
				 //MessageBox::Show(Convert::ToString(messageType));
			 }
				 //continue;
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

			 case StructClass::MessageType::SetInfor:
			 {
				 SetInforClass^ setInforStruct = (SetInforClass^)messageReceived;
				 Server::getObject()->setInfor(setInforStruct->userName, setInforStruct->birthDate);
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
			 case StructClass::MessageType::ListPublicFileName:
			 {
				 //UserStatusClass^ userStatus = (UserStatusClass^)messageReceived;
				 Server::getObject()->listFileNameResponse(socket);
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

			 case StructClass::MessageType::RequestInfor:
			 {
				 RequestInforClass^ rpSendFileStruct = (RequestInforClass^)messageReceived;
				 Server::getObject()->responseInfor(rpSendFileStruct->friendUsername, socket);
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
				 //try {
					 PrivateFile^ prvFile = (PrivateFile^)messageReceived;
					 //MessageBox::Show("debug private file");
					 Server::getObject()->sendPrivateFilePackage(prvFile->userName, prvFile->fileName, prvFile->iPackageNumber, prvFile->iTotalPackage, prvFile->bData, socket);

				// }
				 //catch (Exception^e) {
					// MessageBox::Show(e->Message, "Error Server(Private File)");
				 //}

				 break;
			 }

			 case StructClass::MessageType::UploadPublicFile:
			 {
				 UploadPublicFileClass^ pubFile = (UploadPublicFileClass^)messageReceived;
				 try {
					 //MessageBox::Show(pubFile->fileName + "\n" + Convert::ToString(pubFile->iFileSize) + "\n" + Convert::ToString(pubFile->iPackageNumber) + "\n" + Convert::ToString(pubFile->iTotalPackage));
					 //if (pubFile->isEncrypted) {
						 //pubFile->fileName = convertHexToString(pubFile->fileName);
						 //MessageBox::Show(pubFile->fileName);
						 //MessageBox::Show(convertStringToHex(BitConverter::ToString(bData)));
						 //pubFile->bData = Convert::FromBase64String(Convert::ToBase64String(pubFile->bData));

					 //}
					 if (pubFile->iPackageNumber == 1) {
						 Server::getObject()->addFileName(pubFile->fileName);
						 Server::getObject()->fileStream = gcnew System::IO::FileStream(Server::getObject()->filePath + pubFile->fileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
						 Server::getObject()->fileSize = pubFile->iFileSize;
					 }

					Server::getObject()->fileStream->Write(pubFile->bData, 0, pubFile->bData->Length);
					 //System::IO::File::WriteAllBytes(Server::getObject()->filePath + pubFile->fileName, pubFile->bData);
					
					 if (pubFile->iPackageNumber == pubFile->iTotalPackage)
					 {
						 if ((int)Server::getObject()->fileStream->Length == pubFile->iFileSize)
							 Server::getObject()->mainScreen->appendTextToChatBox("[UPLOAD] "+Server::getObject()->getUserNameBySocket(socket) + " upload " + pubFile->fileName + "(" + Convert::ToString(pubFile->iFileSize) + ")bytes successfully!");
						else
							 Server::getObject()->mainScreen->appendTextToChatBox("[UPLOAD] "+Server::getObject()->getUserNameBySocket(socket) + " upload " + pubFile->fileName + "(" + Convert::ToString((int)Server::getObject()->fileStream->Length) + ")bytes (missed "+ Convert::ToString(pubFile->iFileSize-(int)Server::getObject()->fileStream->Length) + "bytes)");
						 if (Server::getObject()->fileStream != nullptr) {
							 Server::getObject()->fileStream->Close();
							 Server::getObject()->fileStream = nullptr;
						 }
					 }
					 //ResponsePackageClass^ rpPackage = gcnew ResponsePackageClass();
					 //rpPackage->isSuccessful = true;
					 //rpPackage->iPackageNumber = pubFile->iPackageNumber;
					 ////Server::getObject()->soc
					 //array<Byte>^ data = rpPackage->pack();
					 //socket->Send(data);
					 break;
				 }
				 catch (Exception^ e) {
					 //Server::getObject()->fileStream->Close();
					 //Server::getObject()->fileStream = nullptr;
					 MessageBox::Show(e->Message, "Error server(Receive Public File)");
					 //continue;
				 }

				 break;
				
			 }
			 case StructClass::MessageType::RequestSendPublicFile:
			 {
				 try {
					 RequestSendPublicFileClass^ pubFile = (RequestSendPublicFileClass^)messageReceived;
					 Server::getObject()->sendPublicFile(pubFile->fileName,socket);
					
				 }
				 catch (Exception^ e) {
					 MessageBox::Show(e->Message, "Error server(Send Public File)");
				 }
				 break;
			 }

			 default:
				 break;
			 }
			 delete[] buffer;
		 }
		 catch (Exception^ e) {
			 MessageBox::Show(e->Message, "Error server");
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
