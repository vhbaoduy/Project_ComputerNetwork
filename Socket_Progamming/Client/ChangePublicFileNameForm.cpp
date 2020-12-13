#include "pch.h"
#include "ChangePublicFileNameForm.h"
#include "CentralController.h"


System::Void Form_Client::ChangePublicFileNameForm::ChangePublicFileNameForm_Load(System::Object^ sender, System::EventArgs^ e) {
	//CentralController::getObject()->createThreadListenMessageFromServer();
}
String^ Form_Client::ChangePublicFileNameForm::stringOfNewFileName() {
	return this->fileName;
}
System::Void Form_Client::ChangePublicFileNameForm::button_OK_Click(System::Object^ sender, System::EventArgs^ e) {
	this->fileName = this->textBox1->Text->ToString();
	this->button_OK->Enabled = false;
	CentralController::getObject()->publicFileForm->fileName = this->fileName + CentralController::getObject()->publicFileForm->fileFormat;
	CentralController::getObject()->publicFileForm->setFileNameChosen(this->fileName + CentralController::getObject()->publicFileForm->fileFormat);
	this->Close();
}
System::Void  Form_Client::ChangePublicFileNameForm::Form_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
	//CentralController::getObject()->uploadPublicFileToServer(this->filePathToSend, this->fileName + this->fileFormat);
}

System::Void  Form_Client::ChangePublicFileNameForm::Form_Closed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {

}

