#include "pch.h"
#include "PublicFileForm.h"
#include "CentralController.h"
System::Void Form_Client::PublicFileForm::PublicFileForm_Load(System::Object^ sender, System::EventArgs^ e) {
	CentralController::getObject()->createThreadListenMessageFromServer();
	CentralController::getObject()->requestListPublicFileName();
}
String^ Form_Client::PublicFileForm::splitPathFileToReceiver(String^ pathFile) {
	int length = pathFile->Length;
	int i = length - 1;
	for (i; i >= 0; --i) {
		if (pathFile[i] == '\\')
			break;
	}
	pathFile = pathFile->Remove(i + 1);

	return pathFile;
}

System::Void Form_Client::PublicFileForm::ThreadChooseFile() {
	OpenFileDialog^ ofd = gcnew OpenFileDialog;
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ _info = ofd->SafeFileName;
		String^ info = ofd->FileName;
		//this->textBox_fileName->Text = _info;
		//this->textBox_Path->Text = info;
		int size = IO::FileInfo(ofd->FileName).Length;

		fileNameToSend = _info;
		filePathToSend = info;
		fileSizeToSend = size;

		CentralController::getObject()->uploadPublicFileToServer(info, _info);
	}
}

System::Void Form_Client::PublicFileForm::button_upFile_Click(System::Object^ sender, System::EventArgs^ e) {

	Thread^ newThread = gcnew Thread(gcnew ThreadStart(this, &PublicFileForm::ThreadChooseFile));
	newThread->SetApartmentState(ApartmentState::STA);
	newThread->Start();
}

void Form_Client::PublicFileForm::setListFileName(array<String^>^ listFileName) {
	this->listBox_fileName->Items->Clear();
	//String^ myUserName = CentralController::getObject()->userName;
	for each (String ^ fileName in listFileName) {
		this->listBox_fileName->Items->Add(fileName);
	}
}

void Form_Client::PublicFileForm::setUpProcessBar(int min, int max) {
	this->progressBar1->Minimum = min;
	this->progressBar1->Maximum = max;
}
void Form_Client::PublicFileForm::resetProcessBar() {
	this->progressBar1->Minimum = 0;
	this->progressBar1->Maximum = 0;
	this->progressBar1->Value = 0;
}
void Form_Client::PublicFileForm::setValueOfProcessBar(int value) {
	this->progressBar1->Value = value;
}

System::Void Form_Client::PublicFileForm::listBox_fileName_OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	int index = this->listBox_fileName->IndexFromPoint(e->Location);
	if (index != System::Windows::Forms::ListBox::NoMatches)
	{
		String^ fileName = this->listBox_fileName->Items[index]->ToString();
		//MessageBox::Show("|" + fileName + "|");
		fileNameToReceive = fileName;
	}
}

System::Void Form_Client::PublicFileForm::button_downFile_Click(System::Object^ sender, System::EventArgs^ e) {
	if (fileNameToReceive != nullptr) {
		//MessageBox::Show("|" + fileNameToReceive + "|");
		//CentralController::getObject()->createThreadListenMessageFromServer();
		CentralController::getObject()->requestDownloadPublicFile(fileNameToReceive);

	}
}

