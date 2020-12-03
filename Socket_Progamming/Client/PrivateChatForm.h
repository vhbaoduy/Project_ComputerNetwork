#pragma once
//#include "CentralController.h"

namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for PrivateChatForm
	/// </summary>
	public ref class PrivateChatForm : public System::Windows::Forms::Form
	{
	public:
		PrivateChatForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pathFileToReceiver = splitPathFileToReceiver(System::Reflection::Assembly::GetEntryAssembly()->Location);
			//addTextToDisplayChatBox(pathFileToReceiver);
		}
		PrivateChatForm(String^ myUserName, String^ friendUserName): strFriendUsername(friendUserName),strMyUsername(myUserName) {
			InitializeComponent();
			this->Text = "Private Chat With " + strFriendUsername;
			pathFileToReceiver = splitPathFileToReceiver(System::Reflection::Assembly::GetEntryAssembly()->Location);
			//addTextToDisplayChatBox(pathFileToReceiver);
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PrivateChatForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_sendMsg;
	protected:
	private: System::Windows::Forms::Label^ label_chatBox;
	private: System::Windows::Forms::TextBox^ textBox_boxChat;
	private: System::Windows::Forms::TextBox^ textBox_inputMessage;
	private: System::Windows::Forms::TextBox^ textBox_status;
	private: System::Windows::Forms::Label^ label_status;
	private: System::Windows::Forms::Button^ button_chooseFile;
	private: System::Windows::Forms::TextBox^ textBox_fileName;
	private: System::Windows::Forms::Label^ label_fileName;
	private: System::Windows::Forms::Label^ label_Path;
	private: System::Windows::Forms::TextBox^ textBox_Path;


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
			this->button_sendMsg = (gcnew System::Windows::Forms::Button());
			this->label_chatBox = (gcnew System::Windows::Forms::Label());
			this->textBox_boxChat = (gcnew System::Windows::Forms::TextBox());
			this->textBox_inputMessage = (gcnew System::Windows::Forms::TextBox());
			this->textBox_status = (gcnew System::Windows::Forms::TextBox());
			this->label_status = (gcnew System::Windows::Forms::Label());
			this->button_chooseFile = (gcnew System::Windows::Forms::Button());
			this->textBox_fileName = (gcnew System::Windows::Forms::TextBox());
			this->label_fileName = (gcnew System::Windows::Forms::Label());
			this->label_Path = (gcnew System::Windows::Forms::Label());
			this->textBox_Path = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button_sendMsg
			// 
			this->button_sendMsg->Location = System::Drawing::Point(386, 301);
			this->button_sendMsg->Name = L"button_sendMsg";
			this->button_sendMsg->Size = System::Drawing::Size(75, 53);
			this->button_sendMsg->TabIndex = 7;
			this->button_sendMsg->Text = L"Send";
			this->button_sendMsg->UseVisualStyleBackColor = true;
			this->button_sendMsg->Click += gcnew System::EventHandler(this, &PrivateChatForm::button_sendMsg_Click);
			// 
			// label_chatBox
			// 
			this->label_chatBox->AutoSize = true;
			this->label_chatBox->Location = System::Drawing::Point(22, 3);
			this->label_chatBox->Name = L"label_chatBox";
			this->label_chatBox->Size = System::Drawing::Size(64, 17);
			this->label_chatBox->TabIndex = 6;
			this->label_chatBox->Text = L"Chat Box";
			// 
			// textBox_boxChat
			// 
			this->textBox_boxChat->Location = System::Drawing::Point(25, 23);
			this->textBox_boxChat->Multiline = true;
			this->textBox_boxChat->Name = L"textBox_boxChat";
			this->textBox_boxChat->ReadOnly = true;
			this->textBox_boxChat->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_boxChat->Size = System::Drawing::Size(521, 191);
			this->textBox_boxChat->TabIndex = 5;
			// 
			// textBox_inputMessage
			// 
			this->textBox_inputMessage->Location = System::Drawing::Point(25, 294);
			this->textBox_inputMessage->Multiline = true;
			this->textBox_inputMessage->Name = L"textBox_inputMessage";
			this->textBox_inputMessage->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_inputMessage->Size = System::Drawing::Size(346, 64);
			this->textBox_inputMessage->TabIndex = 4;
			// 
			// textBox_status
			// 
			this->textBox_status->Location = System::Drawing::Point(405, 246);
			this->textBox_status->Margin = System::Windows::Forms::Padding(4);
			this->textBox_status->Name = L"textBox_status";
			this->textBox_status->ReadOnly = true;
			this->textBox_status->Size = System::Drawing::Size(141, 22);
			this->textBox_status->TabIndex = 21;
			// 
			// label_status
			// 
			this->label_status->AutoSize = true;
			this->label_status->Location = System::Drawing::Point(318, 250);
			this->label_status->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_status->Name = L"label_status";
			this->label_status->Size = System::Drawing::Size(78, 17);
			this->label_status->TabIndex = 20;
			this->label_status->Text = L"File Status:";
			// 
			// button_chooseFile
			// 
			this->button_chooseFile->Location = System::Drawing::Point(25, 242);
			this->button_chooseFile->Margin = System::Windows::Forms::Padding(4);
			this->button_chooseFile->Name = L"button_chooseFile";
			this->button_chooseFile->Size = System::Drawing::Size(200, 34);
			this->button_chooseFile->TabIndex = 22;
			this->button_chooseFile->Text = L"Choose File";
			this->button_chooseFile->UseVisualStyleBackColor = true;
			this->button_chooseFile->Click += gcnew System::EventHandler(this, &PrivateChatForm::button_chooseFile_Click);
			// 
			// textBox_fileName
			// 
			this->textBox_fileName->Location = System::Drawing::Point(85, 365);
			this->textBox_fileName->Margin = System::Windows::Forms::Padding(4);
			this->textBox_fileName->Name = L"textBox_fileName";
			this->textBox_fileName->ReadOnly = true;
			this->textBox_fileName->Size = System::Drawing::Size(140, 22);
			this->textBox_fileName->TabIndex = 28;
			// 
			// label_fileName
			// 
			this->label_fileName->AutoSize = true;
			this->label_fileName->Location = System::Drawing::Point(4, 369);
			this->label_fileName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_fileName->Name = L"label_fileName";
			this->label_fileName->Size = System::Drawing::Size(73, 17);
			this->label_fileName->TabIndex = 27;
			this->label_fileName->Text = L"File name:";
			// 
			// label_Path
			// 
			this->label_Path->AutoSize = true;
			this->label_Path->Location = System::Drawing::Point(308, 369);
			this->label_Path->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label_Path->Name = L"label_Path";
			this->label_Path->Size = System::Drawing::Size(41, 17);
			this->label_Path->TabIndex = 26;
			this->label_Path->Text = L"Path:";
			// 
			// textBox_Path
			// 
			this->textBox_Path->Location = System::Drawing::Point(359, 365);
			this->textBox_Path->Margin = System::Windows::Forms::Padding(4);
			this->textBox_Path->Name = L"textBox_Path";
			this->textBox_Path->ReadOnly = true;
			this->textBox_Path->Size = System::Drawing::Size(187, 22);
			this->textBox_Path->TabIndex = 25;
			// 
			// PrivateChatForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(573, 400);
			this->Controls->Add(this->textBox_fileName);
			this->Controls->Add(this->label_fileName);
			this->Controls->Add(this->label_Path);
			this->Controls->Add(this->textBox_Path);
			this->Controls->Add(this->button_chooseFile);
			this->Controls->Add(this->textBox_status);
			this->Controls->Add(this->label_status);
			this->Controls->Add(this->button_sendMsg);
			this->Controls->Add(this->label_chatBox);
			this->Controls->Add(this->textBox_boxChat);
			this->Controls->Add(this->textBox_inputMessage);
			this->Name = L"PrivateChatForm";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &PrivateChatForm::PrivateChatForm_FormClosing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &PrivateChatForm::PrivateChatForm_FormClosed);
			this->Load += gcnew System::EventHandler(this, &PrivateChatForm::PrivateChatForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: String^ strFriendUsername = nullptr;
	public: String^ strMyUsername = nullptr;
	public: String^ filePathToSend = nullptr;
	public: String^ fileNameToSend = nullptr;
	public: int fileSizeToSend = 0;
	public: String^ pathFileToReceiver;// = System::Reflection::Assembly::GetEntryAssembly()->Location;
	public: FileStream^ writerStream = nullptr;

	public: void setCaption(String^ txtCaption);
	public: void addTextToDisplayChatBox(String^ text);
	private: System::Void PrivateChatForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void PrivateChatForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	 private: System::Void PrivateChatForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);
	private: System::Void button_sendMsg_Click(System::Object^ sender, System::EventArgs^ e);
	public: System::Void ThreadChooseFile();
	private: System::Void button_chooseFile_Click(System::Object^ sender, System::EventArgs^ e);
	public: String^ splitPathFileToReceiver(String^ pathFile);

};
}
