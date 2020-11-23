#include "pch.h"

using namespace System;

//int main(array<System::String ^> ^args)
//{
//    return 0;
//}


using namespace System::Windows::Forms; 

#include "ConnectServer.h"
#include "CentralController.h"
using namespace Form_Client;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	CentralController::getObject()->connectScreen = gcnew Form_Client::ConnectServer;
	Application::Run(CentralController::getObject()->connectScreen);
	return 0;
}