#include "pch.h"
#include "ChangePasswordForm.h"
#include "CentralController.h"
System::Void Form_Client::ChangePasswordForm::ChangePasswordForm_Load(System::Object^ sender, System::EventArgs^ e) {
	CentralController::getObject()->createThreadListenMessageFromServer();
}

System::Void Form_Client::ChangePasswordForm::button_changePw_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ user = this->textBox_userName->Text->ToString();
	String^ oldPw = this->textBox_curPw->Text->ToString();
	String^ newPw = this->textBox_newPw->Text->ToString();
	String^ confirmPw = this->textBox_confirmPw->Text->ToString();

	CentralController::getObject()->changePassword(user, oldPw, newPw, confirmPw);
}