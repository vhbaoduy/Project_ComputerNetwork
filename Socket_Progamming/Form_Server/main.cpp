#include "pch.h"

using namespace System;

#include "Server.h"


using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	
	Server::getObject()->mainScreen = gcnew Form_Server::MainForm;
	Application::Run(Server::getObject()->mainScreen);
	
	return 0;
}