#pragma once
#include "AppSocket.h"

namespace Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LogIn
	/// </summary>
	public ref class LogIn : public System::Windows::Forms::Form
	{
	public:
		LogIn(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~LogIn()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label_userName;
	protected:
	private: System::Windows::Forms::Label^ label_Password;
	private: System::Windows::Forms::TextBox^ textBox_UserName;
	private: System::Windows::Forms::TextBox^ textBox_Password;
	private: System::Windows::Forms::Button^ button_SignUp;
	private: System::Windows::Forms::Button^ button_LogIn;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label_userName = (gcnew System::Windows::Forms::Label());
			this->label_Password = (gcnew System::Windows::Forms::Label());
			this->textBox_UserName = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Password = (gcnew System::Windows::Forms::TextBox());
			this->button_SignUp = (gcnew System::Windows::Forms::Button());
			this->button_LogIn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label_userName
			// 
			this->label_userName->AutoSize = true;
			this->label_userName->Location = System::Drawing::Point(44, 63);
			this->label_userName->Name = L"label_userName";
			this->label_userName->Size = System::Drawing::Size(79, 17);
			this->label_userName->TabIndex = 0;
			this->label_userName->Text = L"User Name";
			// 
			// label_Password
			// 
			this->label_Password->AutoSize = true;
			this->label_Password->Location = System::Drawing::Point(44, 125);
			this->label_Password->Name = L"label_Password";
			this->label_Password->Size = System::Drawing::Size(77, 17);
			this->label_Password->TabIndex = 1;
			this->label_Password->Text = L"Pass Word";
			// 
			// textBox_UserName
			// 
			this->textBox_UserName->Location = System::Drawing::Point(161, 63);
			this->textBox_UserName->Name = L"textBox_UserName";
			this->textBox_UserName->Size = System::Drawing::Size(167, 22);
			this->textBox_UserName->TabIndex = 2;
			// 
			// textBox_Password
			// 
			this->textBox_Password->Location = System::Drawing::Point(161, 122);
			this->textBox_Password->Name = L"textBox_Password";
			this->textBox_Password->Size = System::Drawing::Size(167, 22);
			this->textBox_Password->TabIndex = 3;
			this->textBox_Password->UseSystemPasswordChar = true;
			// 
			// button_SignUp
			// 
			this->button_SignUp->Location = System::Drawing::Point(58, 226);
			this->button_SignUp->Name = L"button_SignUp";
			this->button_SignUp->Size = System::Drawing::Size(97, 30);
			this->button_SignUp->TabIndex = 4;
			this->button_SignUp->Text = L"Sign Up";
			this->button_SignUp->UseVisualStyleBackColor = true;
			// 
			// button_LogIn
			// 
			this->button_LogIn->Location = System::Drawing::Point(209, 226);
			this->button_LogIn->Name = L"button_LogIn";
			this->button_LogIn->Size = System::Drawing::Size(97, 30);
			this->button_LogIn->TabIndex = 5;
			this->button_LogIn->Text = L"Log In";
			this->button_LogIn->UseVisualStyleBackColor = true;
			this->button_LogIn->Click += gcnew System::EventHandler(this, &LogIn::button_LogIn_Click);
			// 
			// LogIn
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(391, 332);
			this->Controls->Add(this->button_LogIn);
			this->Controls->Add(this->button_SignUp);
			this->Controls->Add(this->textBox_Password);
			this->Controls->Add(this->textBox_UserName);
			this->Controls->Add(this->label_Password);
			this->Controls->Add(this->label_userName);
			this->Name = L"LogIn";
			this->Text = L"Client";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_LogIn_Click(System::Object^ sender, System::EventArgs^ e) {
		AppSocket test;
		array<unsigned char>^ tesst = gcnew array<unsigned char>(10);
		for (int i = 0; i < 10; i++)
			tesst[i] = 'a';

		test.initializeSocket();
		if (!test.connectToServer()) {
			MessageBox::Show("Connect successfuly", "Notification", MessageBoxButtons::OKCancel);
			test.clientSocket->Send(tesst, tesst->Length, SocketFlags::None);
		}

	}
};
}
