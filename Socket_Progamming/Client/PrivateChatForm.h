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


	private: System::Windows::Forms::Button^ button_chooseFile;




	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button_viewInfor;

	public:


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
			this->button_chooseFile = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_viewInfor = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button_sendMsg
			// 
			this->button_sendMsg->Location = System::Drawing::Point(471, 321);
			this->button_sendMsg->Name = L"button_sendMsg";
			this->button_sendMsg->Size = System::Drawing::Size(75, 53);
			this->button_sendMsg->TabIndex = 1;
			this->button_sendMsg->Text = L"Send";
			this->button_sendMsg->UseVisualStyleBackColor = true;
			this->button_sendMsg->Click += gcnew System::EventHandler(this, &PrivateChatForm::button_sendMsg_Click);
			// 
			// label_chatBox
			// 
			this->label_chatBox->AutoSize = true;
			this->label_chatBox->Location = System::Drawing::Point(22, 22);
			this->label_chatBox->Name = L"label_chatBox";
			this->label_chatBox->Size = System::Drawing::Size(78, 17);
			this->label_chatBox->TabIndex = 6;
			this->label_chatBox->Text = L"CHAT BOX";
			// 
			// textBox_boxChat
			// 
			this->textBox_boxChat->Location = System::Drawing::Point(25, 45);
			this->textBox_boxChat->Multiline = true;
			this->textBox_boxChat->Name = L"textBox_boxChat";
			this->textBox_boxChat->ReadOnly = true;
			this->textBox_boxChat->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_boxChat->Size = System::Drawing::Size(521, 191);
			this->textBox_boxChat->TabIndex = 5;
			// 
			// textBox_inputMessage
			// 
			this->textBox_inputMessage->Location = System::Drawing::Point(25, 316);
			this->textBox_inputMessage->Multiline = true;
			this->textBox_inputMessage->Name = L"textBox_inputMessage";
			this->textBox_inputMessage->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_inputMessage->Size = System::Drawing::Size(423, 64);
			this->textBox_inputMessage->TabIndex = 4;
			// 
			// button_chooseFile
			// 
			this->button_chooseFile->Location = System::Drawing::Point(25, 254);
			this->button_chooseFile->Margin = System::Windows::Forms::Padding(4);
			this->button_chooseFile->Name = L"button_chooseFile";
			this->button_chooseFile->Size = System::Drawing::Size(200, 44);
			this->button_chooseFile->TabIndex = 22;
			this->button_chooseFile->Text = L"Choose File";
			this->button_chooseFile->UseVisualStyleBackColor = true;
			this->button_chooseFile->Click += gcnew System::EventHandler(this, &PrivateChatForm::button_chooseFile_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(259, 276);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(287, 22);
			this->progressBar1->TabIndex = 29;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(259, 253);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(59, 17);
			this->label1->TabIndex = 30;
			this->label1->Text = L"Process";
			// 
			// button_viewInfor
			// 
			this->button_viewInfor->Location = System::Drawing::Point(430, 12);
			this->button_viewInfor->Name = L"button_viewInfor";
			this->button_viewInfor->Size = System::Drawing::Size(116, 27);
			this->button_viewInfor->TabIndex = 31;
			this->button_viewInfor->Text = L"View Infor";
			this->button_viewInfor->UseVisualStyleBackColor = true;
			this->button_viewInfor->Click += gcnew System::EventHandler(this, &PrivateChatForm::button_viewInfor_Click);
			// 
			// PrivateChatForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(565, 394);
			this->Controls->Add(this->button_viewInfor);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button_chooseFile);
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
	public: void setUpProcessBar(int min, int max);
	public: void resetProcessBar();
	public: void setValueOfProcessBar(int value);
	private: System::Void button_viewInfor_Click(System::Object^ sender, System::EventArgs^ e);
};
}
