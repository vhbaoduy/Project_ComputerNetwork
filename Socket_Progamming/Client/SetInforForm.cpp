#include "pch.h"
#include "SetInforForm.h"
#include "CentralController.h"

System::Void Form_Client::SetInforForm::SetInforForm_Load(System::Object^ sender, System::EventArgs^ e) {
	CentralController::getObject()->createThreadListenMessageFromServer();
}
 System::Void Form_Client::SetInforForm::butSave_Click(System::Object^ sender, System::EventArgs^ e) {
	 CentralController::getObject()->setInfor(CentralController::getObject()->userName, txtBirthdate->Text);
	 butSave->Enabled = false;
}