#pragma once

namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ChangePasswordForm
	/// </summary>
	public ref class ChangePasswordForm : public System::Windows::Forms::Form
	{
	public:
		ChangePasswordForm(void)
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
		~ChangePasswordForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label_userName;
	private: System::Windows::Forms::TextBox^ textBox_userName;
	private: System::Windows::Forms::TextBox^ textBox_curPw;
	private: System::Windows::Forms::Label^ label_currentPw;
	private: System::Windows::Forms::TextBox^ textBox_newPw;
	private: System::Windows::Forms::Label^ label_newPw;
	private: System::Windows::Forms::TextBox^ textBox_confirmPw;

	private: System::Windows::Forms::Label^ label_confirmPw;
	private: System::Windows::Forms::Button^ button_changePw;

	protected:


	protected:

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
			this->textBox_userName = (gcnew System::Windows::Forms::TextBox());
			this->textBox_curPw = (gcnew System::Windows::Forms::TextBox());
			this->label_currentPw = (gcnew System::Windows::Forms::Label());
			this->textBox_newPw = (gcnew System::Windows::Forms::TextBox());
			this->label_newPw = (gcnew System::Windows::Forms::Label());
			this->textBox_confirmPw = (gcnew System::Windows::Forms::TextBox());
			this->label_confirmPw = (gcnew System::Windows::Forms::Label());
			this->button_changePw = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label_userName
			// 
			this->label_userName->AutoSize = true;
			this->label_userName->Location = System::Drawing::Point(35, 37);
			this->label_userName->Name = L"label_userName";
			this->label_userName->Size = System::Drawing::Size(79, 17);
			this->label_userName->TabIndex = 0;
			this->label_userName->Text = L"User Name";
			// 
			// textBox_userName
			// 
			this->textBox_userName->Location = System::Drawing::Point(173, 37);
			this->textBox_userName->Name = L"textBox_userName";
			this->textBox_userName->Size = System::Drawing::Size(168, 22);
			this->textBox_userName->TabIndex = 1;
			// 
			// textBox_curPw
			// 
			this->textBox_curPw->Location = System::Drawing::Point(173, 94);
			this->textBox_curPw->Name = L"textBox_curPw";
			this->textBox_curPw->Size = System::Drawing::Size(168, 22);
			this->textBox_curPw->TabIndex = 3;
			this->textBox_curPw->UseSystemPasswordChar = true;
			// 
			// label_currentPw
			// 
			this->label_currentPw->AutoSize = true;
			this->label_currentPw->Location = System::Drawing::Point(35, 94);
			this->label_currentPw->Name = L"label_currentPw";
			this->label_currentPw->Size = System::Drawing::Size(120, 17);
			this->label_currentPw->TabIndex = 2;
			this->label_currentPw->Text = L"Current Password";
			// 
			// textBox_newPw
			// 
			this->textBox_newPw->Location = System::Drawing::Point(173, 155);
			this->textBox_newPw->Name = L"textBox_newPw";
			this->textBox_newPw->Size = System::Drawing::Size(168, 22);
			this->textBox_newPw->TabIndex = 5;
			this->textBox_newPw->UseSystemPasswordChar = true;
			// 
			// label_newPw
			// 
			this->label_newPw->AutoSize = true;
			this->label_newPw->Location = System::Drawing::Point(35, 155);
			this->label_newPw->Name = L"label_newPw";
			this->label_newPw->Size = System::Drawing::Size(93, 17);
			this->label_newPw->TabIndex = 4;
			this->label_newPw->Text = L"New Pasword";
			// 
			// textBox_confirmPw
			// 
			this->textBox_confirmPw->Location = System::Drawing::Point(173, 214);
			this->textBox_confirmPw->Name = L"textBox_confirmPw";
			this->textBox_confirmPw->Size = System::Drawing::Size(168, 22);
			this->textBox_confirmPw->TabIndex = 7;
			this->textBox_confirmPw->UseSystemPasswordChar = true;
			// 
			// label_confirmPw
			// 
			this->label_confirmPw->AutoSize = true;
			this->label_confirmPw->Location = System::Drawing::Point(35, 214);
			this->label_confirmPw->Name = L"label_confirmPw";
			this->label_confirmPw->Size = System::Drawing::Size(121, 17);
			this->label_confirmPw->TabIndex = 6;
			this->label_confirmPw->Text = L"Confirm Password";
			// 
			// button_changePw
			// 
			this->button_changePw->Location = System::Drawing::Point(38, 277);
			this->button_changePw->Name = L"button_changePw";
			this->button_changePw->Size = System::Drawing::Size(303, 45);
			this->button_changePw->TabIndex = 8;
			this->button_changePw->Text = L"CHANGE PASSWORD";
			this->button_changePw->UseVisualStyleBackColor = true;
			this->button_changePw->Click += gcnew System::EventHandler(this, &ChangePasswordForm::button_changePw_Click);
			// 
			// ChangePasswordForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(374, 365);
			this->Controls->Add(this->button_changePw);
			this->Controls->Add(this->textBox_confirmPw);
			this->Controls->Add(this->label_confirmPw);
			this->Controls->Add(this->textBox_newPw);
			this->Controls->Add(this->label_newPw);
			this->Controls->Add(this->textBox_curPw);
			this->Controls->Add(this->label_currentPw);
			this->Controls->Add(this->textBox_userName);
			this->Controls->Add(this->label_userName);
			this->Name = L"ChangePasswordForm";
			this->Text = L"ChangePasswordForm";
			this->Load += gcnew System::EventHandler(this, &ChangePasswordForm::ChangePasswordForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ChangePasswordForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_changePw_Click(System::Object^ sender, System::EventArgs^ e);
};
}
