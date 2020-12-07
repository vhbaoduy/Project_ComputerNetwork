#include "pch.h"
#include "PrivateChatForm.h"
#include "CentralController.h"

void Form_Client::PrivateChatForm::setCaption(String^ txtCaption) {
	this->Text = txtCaption;
}
void Form_Client::PrivateChatForm::addTextToDisplayChatBox(String^ text) {
		this->textBox_boxChat->AppendText(text);
		this->textBox_boxChat->AppendText("\r\n");

}
System::Void Form_Client::PrivateChatForm::PrivateChatForm_Load(System::Object^ sender, System::EventArgs^ e) {
	CentralController::getObject()->createThreadListenMessageFromServer();
}
System::Void Form_Client::PrivateChatForm::PrivateChatForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	CentralController::getObject()->lstPrivateChatForm->Remove(this);
}
System::Void Form_Client::PrivateChatForm::PrivateChatForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {

}
System::Void Form_Client::PrivateChatForm::button_sendMsg_Click(System::Object^ sender, System::EventArgs^ e) {
	CentralController::getObject()->sendPrivateMessage(strFriendUsername, textBox_inputMessage->Text);
	addTextToDisplayChatBox(strMyUsername + ": " + textBox_inputMessage->Text);
	textBox_inputMessage->Text = nullptr;
}

System::Void Form_Client::PrivateChatForm:: ThreadChooseFile() {
	OpenFileDialog^ ofd = gcnew OpenFileDialog;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ _info = ofd->SafeFileName;
		String^ info = ofd->FileName;
		this->textBox_fileName->Text = _info;
		this->textBox_Path->Text = info;
		int size = IO::FileInfo(ofd->FileName).Length;

		fileNameToSend = _info;
		filePathToSend = info;
		fileSizeToSend = size;
		CentralController::getObject()->requestSendFile(strFriendUsername, _info, size);
	}
}

System::Void Form_Client::PrivateChatForm::button_chooseFile_Click(System::Object^ sender, System::EventArgs^ e) {
	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &PrivateChatForm::ThreadChooseFile));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}

String^ Form_Client::PrivateChatForm::splitPathFileToReceiver(String^ pathFile) {
	int length = pathFile->Length;
	int i = length - 1;
	for (i; i >= 0; --i) {
		if (pathFile[i] == '\\')
			break;
	}
	pathFile = pathFile->Remove(i+1);

	return pathFile;
}

	void Form_Client::PrivateChatForm::setUpProcessBar(int min, int max) {
		this->progressBar1->Minimum = min;
		this->progressBar1->Maximum = max;
	}
	void Form_Client::PrivateChatForm::resetProcessBar() {
		this->progressBar1->Minimum = 0;
		this->progressBar1->Maximum = 0;
		this->progressBar1->Value = 0;
	}
	void Form_Client::PrivateChatForm::setValueOfProcessBar(int value) {
		this->progressBar1->Value = value;
	}