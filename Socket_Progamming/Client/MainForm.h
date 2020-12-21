#pragma once


namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox_inputMessage;
	protected:
	private: System::Windows::Forms::TextBox^ textBox_boxChat;
	private: System::Windows::Forms::Label^ label_chatBox;

	private: System::Windows::Forms::Button^ button_sendMsg;
	private: System::Windows::Forms::Button^ button_changePassword;

	private: System::Windows::Forms::Button^ button_logOut;


	private: System::Windows::Forms::Label^ label_online;



		   //private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::ListBox^ listBox_activeUser;

	private: System::Windows::Forms::Button^ butSetInfor;
	private: System::Windows::Forms::Button^ button_myInfor;
	private: System::Windows::Forms::Button^ button_publicFile;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox_inputMessage = (gcnew System::Windows::Forms::TextBox());
			this->textBox_boxChat = (gcnew System::Windows::Forms::TextBox());
			this->label_chatBox = (gcnew System::Windows::Forms::Label());
			this->button_sendMsg = (gcnew System::Windows::Forms::Button());
			this->button_changePassword = (gcnew System::Windows::Forms::Button());
			this->button_logOut = (gcnew System::Windows::Forms::Button());
			this->label_online = (gcnew System::Windows::Forms::Label());
			this->listBox_activeUser = (gcnew System::Windows::Forms::ListBox());
			this->butSetInfor = (gcnew System::Windows::Forms::Button());
			this->button_myInfor = (gcnew System::Windows::Forms::Button());
			this->button_publicFile = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox_inputMessage
			// 
			this->textBox_inputMessage->Location = System::Drawing::Point(12, 380);
			this->textBox_inputMessage->Multiline = true;
			this->textBox_inputMessage->Name = L"textBox_inputMessage";
			this->textBox_inputMessage->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_inputMessage->Size = System::Drawing::Size(346, 64);
			this->textBox_inputMessage->TabIndex = 0;
			// 
			// textBox_boxChat
			// 
			this->textBox_boxChat->Location = System::Drawing::Point(12, 51);
			this->textBox_boxChat->Multiline = true;
			this->textBox_boxChat->Name = L"textBox_boxChat";
			this->textBox_boxChat->ReadOnly = true;
			this->textBox_boxChat->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_boxChat->Size = System::Drawing::Size(436, 271);
			this->textBox_boxChat->TabIndex = 1;
			// 
			// label_chatBox
			// 
			this->label_chatBox->AutoSize = true;
			this->label_chatBox->Location = System::Drawing::Point(9, 31);
			this->label_chatBox->Name = L"label_chatBox";
			this->label_chatBox->Size = System::Drawing::Size(64, 17);
			this->label_chatBox->TabIndex = 2;
			this->label_chatBox->Text = L"Chat Box";
			// 
			// button_sendMsg
			// 
			this->button_sendMsg->Location = System::Drawing::Point(373, 387);
			this->button_sendMsg->Name = L"button_sendMsg";
			this->button_sendMsg->Size = System::Drawing::Size(75, 53);
			this->button_sendMsg->TabIndex = 1;
			this->button_sendMsg->Text = L"Send";
			this->button_sendMsg->UseVisualStyleBackColor = true;
			this->button_sendMsg->Click += gcnew System::EventHandler(this, &MainForm::button_sendMsg_Click);
			// 
			// button_changePassword
			// 
			this->button_changePassword->Location = System::Drawing::Point(524, 344);
			this->button_changePassword->Name = L"button_changePassword";
			this->button_changePassword->Size = System::Drawing::Size(139, 34);
			this->button_changePassword->TabIndex = 4;
			this->button_changePassword->Text = L"Change Password";
			this->button_changePassword->UseVisualStyleBackColor = true;
			this->button_changePassword->Click += gcnew System::EventHandler(this, &MainForm::button_changePassword_Click);
			// 
			// button_logOut
			// 
			this->button_logOut->Location = System::Drawing::Point(524, 394);
			this->button_logOut->Name = L"button_logOut";
			this->button_logOut->Size = System::Drawing::Size(139, 34);
			this->button_logOut->TabIndex = 5;
			this->button_logOut->Text = L"Log Out";
			this->button_logOut->UseVisualStyleBackColor = true;
			this->button_logOut->Click += gcnew System::EventHandler(this, &MainForm::button_logOut_Click);
			// 
			// label_online
			// 
			this->label_online->AutoSize = true;
			this->label_online->Location = System::Drawing::Point(517, 31);
			this->label_online->Name = L"label_online";
			this->label_online->Size = System::Drawing::Size(49, 17);
			this->label_online->TabIndex = 7;
			this->label_online->Text = L"Online";
			// 
			// listBox_activeUser
			// 
			this->listBox_activeUser->FormattingEnabled = true;
			this->listBox_activeUser->ItemHeight = 16;
			this->listBox_activeUser->Location = System::Drawing::Point(520, 51);
			this->listBox_activeUser->Name = L"listBox_activeUser";
			this->listBox_activeUser->ScrollAlwaysVisible = true;
			this->listBox_activeUser->Size = System::Drawing::Size(139, 132);
			this->listBox_activeUser->TabIndex = 12;
			this->listBox_activeUser->MouseDoubleClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::listBox_activeUser_OnMouseDoubleClick);
			// 
			// butSetInfor
			// 
			this->butSetInfor->Location = System::Drawing::Point(524, 290);
			this->butSetInfor->Margin = System::Windows::Forms::Padding(4);
			this->butSetInfor->Name = L"butSetInfor";
			this->butSetInfor->Size = System::Drawing::Size(143, 33);
			this->butSetInfor->TabIndex = 24;
			this->butSetInfor->Text = L"Set Information";
			this->butSetInfor->UseVisualStyleBackColor = true;
			this->butSetInfor->Click += gcnew System::EventHandler(this, &MainForm::butSetInfor_Click);
			// 
			// button_myInfor
			// 
			this->button_myInfor->Location = System::Drawing::Point(520, 235);
			this->button_myInfor->Margin = System::Windows::Forms::Padding(4);
			this->button_myInfor->Name = L"button_myInfor";
			this->button_myInfor->Size = System::Drawing::Size(143, 38);
			this->button_myInfor->TabIndex = 25;
			this->button_myInfor->Text = L"View My Infor";
			this->button_myInfor->UseVisualStyleBackColor = true;
			this->button_myInfor->Click += gcnew System::EventHandler(this, &MainForm::button_myInfor_Click);
			// 
			// button_publicFile
			// 
			this->button_publicFile->Location = System::Drawing::Point(12, 333);
			this->button_publicFile->Name = L"button_publicFile";
			this->button_publicFile->Size = System::Drawing::Size(216, 39);
			this->button_publicFile->TabIndex = 26;
			this->button_publicFile->Text = L"Upload/Download File";
			this->button_publicFile->UseVisualStyleBackColor = true;
			this->button_publicFile->Click += gcnew System::EventHandler(this, &MainForm::button_publicFile_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(706, 477);
			this->Controls->Add(this->button_publicFile);
			this->Controls->Add(this->button_myInfor);
			this->Controls->Add(this->butSetInfor);
			this->Controls->Add(this->listBox_activeUser);
			this->Controls->Add(this->label_online);
			this->Controls->Add(this->button_logOut);
			this->Controls->Add(this->button_changePassword);
			this->Controls->Add(this->button_sendMsg);
			this->Controls->Add(this->label_chatBox);
			this->Controls->Add(this->textBox_boxChat);
			this->Controls->Add(this->textBox_inputMessage);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->Name = L"MainForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &MainForm::MainForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	  private: System::Void MainForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	public: void addTextToBoxChat(String^ text);
	public: void addAnOnlineUser(String^ userName);
	public: void deleteAnOnline(String^ userName);
	public: void setOnlineUsers(array<String^>^ listUser);
	private: System::Void button_sendMsg_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_logOut_Click(System::Object^ sender, System::EventArgs^ e);

	private: System::Void listBox_activeUser_OnMouseDoubleClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void button_changePassword_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butSetInfor_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_myInfor_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_publicFile_Click(System::Object^ sender, System::EventArgs^ e);
};
}


