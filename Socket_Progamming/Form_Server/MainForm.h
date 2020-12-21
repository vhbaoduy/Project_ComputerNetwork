#pragma once

#include"..\Struct\Struct.h"


namespace Form_Server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm()
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

	protected:

	private: System::Windows::Forms::Label^ label_Top2;
	private: System::Windows::Forms::Label^ label_Top3;
	public: System::Windows::Forms::TextBox^ textBox_IP;
	public: System::Windows::Forms::TextBox^ textBox_Port;

	private: System::Windows::Forms::Label^ label_listOfClients;
	private: System::Windows::Forms::Button^ button_RunServer;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;



	private: System::Windows::Forms::TextBox^ textBox_listClients;
	private: System::Windows::Forms::TextBox^ textBox_chatBox;

	private: System::Windows::Forms::Label^ label_chatBox;





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
			this->label_Top2 = (gcnew System::Windows::Forms::Label());
			this->label_Top3 = (gcnew System::Windows::Forms::Label());
			this->textBox_IP = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Port = (gcnew System::Windows::Forms::TextBox());
			this->label_listOfClients = (gcnew System::Windows::Forms::Label());
			this->button_RunServer = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->textBox_listClients = (gcnew System::Windows::Forms::TextBox());
			this->textBox_chatBox = (gcnew System::Windows::Forms::TextBox());
			this->label_chatBox = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// label_Top2
			// 
			this->label_Top2->AutoSize = true;
			this->label_Top2->Location = System::Drawing::Point(113, 12);
			this->label_Top2->Name = L"label_Top2";
			this->label_Top2->Size = System::Drawing::Size(76, 17);
			this->label_Top2->TabIndex = 2;
			this->label_Top2->Text = L"IP Address";
			// 
			// label_Top3
			// 
			this->label_Top3->AutoSize = true;
			this->label_Top3->Location = System::Drawing::Point(113, 46);
			this->label_Top3->Name = L"label_Top3";
			this->label_Top3->Size = System::Drawing::Size(90, 17);
			this->label_Top3->TabIndex = 3;
			this->label_Top3->Text = L"Port Address";
			// 
			// textBox_IP
			// 
			this->textBox_IP->Location = System::Drawing::Point(217, 12);
			this->textBox_IP->Name = L"textBox_IP";
			this->textBox_IP->Size = System::Drawing::Size(157, 22);
			this->textBox_IP->TabIndex = 4;
			this->textBox_IP->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox_IP_TextChanged);
			// 
			// textBox_Port
			// 
			this->textBox_Port->Location = System::Drawing::Point(217, 43);
			this->textBox_Port->Name = L"textBox_Port";
			this->textBox_Port->Size = System::Drawing::Size(157, 22);
			this->textBox_Port->TabIndex = 5;
			this->textBox_Port->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox_Port_TextChanged);
			// 
			// label_listOfClients
			// 
			this->label_listOfClients->AutoSize = true;
			this->label_listOfClients->Location = System::Drawing::Point(9, 89);
			this->label_listOfClients->Name = L"label_listOfClients";
			this->label_listOfClients->Size = System::Drawing::Size(76, 17);
			this->label_listOfClients->TabIndex = 7;
			this->label_listOfClients->Text = L"Connected";
			// 
			// button_RunServer
			// 
			this->button_RunServer->Location = System::Drawing::Point(393, 22);
			this->button_RunServer->Name = L"button_RunServer";
			this->button_RunServer->Size = System::Drawing::Size(118, 36);
			this->button_RunServer->TabIndex = 8;
			this->button_RunServer->Text = L"Run Server";
			this->button_RunServer->UseVisualStyleBackColor = true;
			this->button_RunServer->Click += gcnew System::EventHandler(this, &MainForm::button_RunServer_Click);
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &MainForm::backgroundWorker1_DoWork);
			// 
			// textBox_listClients
			// 
			this->textBox_listClients->Location = System::Drawing::Point(12, 110);
			this->textBox_listClients->Multiline = true;
			this->textBox_listClients->Name = L"textBox_listClients";
			this->textBox_listClients->ReadOnly = true;
			this->textBox_listClients->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_listClients->Size = System::Drawing::Size(198, 115);
			this->textBox_listClients->TabIndex = 9;
			// 
			// textBox_chatBox
			// 
			this->textBox_chatBox->Location = System::Drawing::Point(240, 110);
			this->textBox_chatBox->Multiline = true;
			this->textBox_chatBox->Name = L"textBox_chatBox";
			this->textBox_chatBox->ReadOnly = true;
			this->textBox_chatBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox_chatBox->Size = System::Drawing::Size(349, 228);
			this->textBox_chatBox->TabIndex = 10;
			// 
			// label_chatBox
			// 
			this->label_chatBox->AutoSize = true;
			this->label_chatBox->Location = System::Drawing::Point(237, 90);
			this->label_chatBox->Name = L"label_chatBox";
			this->label_chatBox->Size = System::Drawing::Size(64, 17);
			this->label_chatBox->TabIndex = 11;
			this->label_chatBox->Text = L"Chat Box";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(613, 368);
			this->Controls->Add(this->label_chatBox);
			this->Controls->Add(this->textBox_chatBox);
			this->Controls->Add(this->textBox_listClients);
			this->Controls->Add(this->button_RunServer);
			this->Controls->Add(this->label_listOfClients);
			this->Controls->Add(this->textBox_Port);
			this->Controls->Add(this->textBox_IP);
			this->Controls->Add(this->label_Top3);
			this->Controls->Add(this->label_Top2);
			this->Name = L"MainForm";
			this->Text = L"Server";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox_IP_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void textBox_Port_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_RunServer_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void backgroundWorker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e);
	public: static void listenMessage(Object^ obj);

	public: Thread^ threadListenClient;
	public: void updateConnectedClient(List<String^>^ clients);
	public: void appendTextToChatBox(String^ text);
	public:static String^ convertStringToHex(String^ input);
	public:static String^ convertHexToString(String^ hexInput);

};

}



