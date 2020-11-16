﻿#pragma once


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
	private: System::Windows::Forms::TextBox^ textBox_IP;
	private: System::Windows::Forms::TextBox^ textBox_Port;
	private: System::Windows::Forms::ListBox^ listBox_Clients;
	private: System::Windows::Forms::Label^ label_listOfClients;
	private: System::Windows::Forms::Button^ button_RunServer;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker1;


	public:  
		Thread^ threadListenClient;




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
			this->listBox_Clients = (gcnew System::Windows::Forms::ListBox());
			this->label_listOfClients = (gcnew System::Windows::Forms::Label());
			this->button_RunServer = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// label_Top2
			// 
			this->label_Top2->AutoSize = true;
			this->label_Top2->Location = System::Drawing::Point(40, 12);
			this->label_Top2->Name = L"label_Top2";
			this->label_Top2->Size = System::Drawing::Size(76, 17);
			this->label_Top2->TabIndex = 2;
			this->label_Top2->Text = L"IP Address";
			// 
			// label_Top3
			// 
			this->label_Top3->AutoSize = true;
			this->label_Top3->Location = System::Drawing::Point(40, 46);
			this->label_Top3->Name = L"label_Top3";
			this->label_Top3->Size = System::Drawing::Size(90, 17);
			this->label_Top3->TabIndex = 3;
			this->label_Top3->Text = L"Port Address";
			// 
			// textBox_IP
			// 
			this->textBox_IP->Location = System::Drawing::Point(144, 12);
			this->textBox_IP->Name = L"textBox_IP";
			this->textBox_IP->ReadOnly = true;
			this->textBox_IP->Size = System::Drawing::Size(100, 22);
			this->textBox_IP->TabIndex = 4;
			this->textBox_IP->Text = L"192.168.0.1";
			this->textBox_IP->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox_IP_TextChanged);
			// 
			// textBox_Port
			// 
			this->textBox_Port->Location = System::Drawing::Point(144, 43);
			this->textBox_Port->Name = L"textBox_Port";
			this->textBox_Port->ReadOnly = true;
			this->textBox_Port->Size = System::Drawing::Size(100, 22);
			this->textBox_Port->TabIndex = 5;
			this->textBox_Port->Text = L"3504";
			this->textBox_Port->TextChanged += gcnew System::EventHandler(this, &MainForm::textBox_Port_TextChanged);
			// 
			// listBox_Clients
			// 
			this->listBox_Clients->FormattingEnabled = true;
			this->listBox_Clients->ItemHeight = 16;
			this->listBox_Clients->Location = System::Drawing::Point(43, 112);
			this->listBox_Clients->Name = L"listBox_Clients";
			this->listBox_Clients->Size = System::Drawing::Size(204, 244);
			this->listBox_Clients->TabIndex = 6;
			// 
			// label_listOfClients
			// 
			this->label_listOfClients->AutoSize = true;
			this->label_listOfClients->Location = System::Drawing::Point(43, 89);
			this->label_listOfClients->Name = L"label_listOfClients";
			this->label_listOfClients->Size = System::Drawing::Size(92, 17);
			this->label_listOfClients->TabIndex = 7;
			this->label_listOfClients->Text = L"List of Clients";
			// 
			// button_RunServer
			// 
			this->button_RunServer->Location = System::Drawing::Point(281, 21);
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
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(478, 368);
			this->Controls->Add(this->button_RunServer);
			this->Controls->Add(this->label_listOfClients);
			this->Controls->Add(this->listBox_Clients);
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
};

}


