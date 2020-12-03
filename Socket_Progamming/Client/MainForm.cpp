#include "pch.h"
#include "MainForm.h"
#include "CentralController.h"

System::Void Form_Client::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	this->Text = CentralController::getObject()->userName;
	this->label_userName->Text = CentralController::getObject()->userName;
	CentralController::getObject()->createThreadListenMessageFromServer();
	CentralController::getObject()->requestListOnlineUsers();
	CentralController::getObject()->requestListOnlineUsers();
}

void Form_Client::MainForm::addTextToBoxChat(String^ text) {
	this->textBox_boxChat->AppendText(text);
	this->textBox_boxChat->AppendText("\r\n");

}

void Form_Client::MainForm::addAnOnlineUser(String^ userName) {
	this->listBox_activeUser->Items->Add(userName);

}
void Form_Client::MainForm::deleteAnOnline(String^ userName) {
	for (int i = 0; i < this->listBox_activeUser->Items->Count; ++i)
		if (this->listBox_activeUser->Items[i]->ToString() == userName)
		{
			
			this->listBox_activeUser->Items->Remove(this->listBox_activeUser->Items[i]);
			break;
		}
}

void Form_Client::MainForm::setOnlineUsers(array<String^>^ listUser) {
	this->listBox_activeUser->Items->Clear();

	String^ myUserName = CentralController::getObject()->userName;
	for each (String ^ user in listUser) {
		if(user != myUserName)
			this->listBox_activeUser->Items->Add(user);
	}
}

System::Void Form_Client::MainForm::listBox_activeUser_OnMouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e)
{
	int index = this->listBox_activeUser->IndexFromPoint(e->Location);
	if (index != System::Windows::Forms::ListBox::NoMatches)
	{
		String^ friendUsername = this->listBox_activeUser->Items[index]->ToString();
		PrivateChatForm^ Prf = gcnew PrivateChatForm(CentralController::getObject()->userName, friendUsername);
		CentralController::getObject()->lstPrivateChatForm->Add(Prf);
		//Application::Run(Prf);
		Prf->Show();
	}
}


System::Void Form_Client::MainForm::button_sendMsg_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ message = this->textBox_inputMessage->Text->ToString();
	CentralController::getObject()->sendPublicMassage(message);

	this->textBox_inputMessage->Text = nullptr;
}

System::Void Form_Client::MainForm::button_logOut_Click(System::Object^ sender, System::EventArgs^ e) {
	//CentralController::getObject()->logOut();
	Application::Restart();
}


System::Void Form_Client::MainForm::MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	CentralController::getObject()->logOut();
	//CentralController::getObject()->appSocket->clientSocket->Disconnect(false);
	//CentralController::getObject()->appSocket->clientSocket = nullptr;
	//Application::ExitThread();
}
System::Void Form_Client::MainForm::MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
	//CentralController::getObject()->logOut();
	Application::Exit();

}



