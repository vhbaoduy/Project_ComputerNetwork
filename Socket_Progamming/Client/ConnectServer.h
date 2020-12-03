#pragma once


namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	/// <summary>
	/// Summary for ConnectServer
	/// </summary>
	public ref class ConnectServer : public System::Windows::Forms::Form
	{
	public:
		ConnectServer(void)
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
		~ConnectServer()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox_Port;
	protected:
	private: System::Windows::Forms::TextBox^ textBox_IP;
	private: System::Windows::Forms::Label^ label_portAddr;
	private: System::Windows::Forms::Label^ label_IPaddr;
	private: System::Windows::Forms::Button^ button_connect;

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
			this->textBox_Port = (gcnew System::Windows::Forms::TextBox());
			this->textBox_IP = (gcnew System::Windows::Forms::TextBox());
			this->label_portAddr = (gcnew System::Windows::Forms::Label());
			this->label_IPaddr = (gcnew System::Windows::Forms::Label());
			this->button_connect = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// textBox_Port
			// 
			this->textBox_Port->Location = System::Drawing::Point(134, 104);
			this->textBox_Port->Name = L"textBox_Port";
			this->textBox_Port->Size = System::Drawing::Size(152, 22);
			this->textBox_Port->TabIndex = 9;
			// 
			// textBox_IP
			// 
			this->textBox_IP->Location = System::Drawing::Point(134, 50);
			this->textBox_IP->Name = L"textBox_IP";
			this->textBox_IP->Size = System::Drawing::Size(152, 22);
			this->textBox_IP->TabIndex = 8;
			// 
			// label_portAddr
			// 
			this->label_portAddr->AutoSize = true;
			this->label_portAddr->Location = System::Drawing::Point(30, 107);
			this->label_portAddr->Name = L"label_portAddr";
			this->label_portAddr->Size = System::Drawing::Size(90, 17);
			this->label_portAddr->TabIndex = 7;
			this->label_portAddr->Text = L"Port Address";
			// 
			// label_IPaddr
			// 
			this->label_IPaddr->AutoSize = true;
			this->label_IPaddr->Location = System::Drawing::Point(30, 50);
			this->label_IPaddr->Name = L"label_IPaddr";
			this->label_IPaddr->Size = System::Drawing::Size(76, 17);
			this->label_IPaddr->TabIndex = 6;
			this->label_IPaddr->Text = L"IP Address";
			// 
			// button_connect
			// 
			this->button_connect->Location = System::Drawing::Point(91, 189);
			this->button_connect->Name = L"button_connect";
			this->button_connect->Size = System::Drawing::Size(151, 39);
			this->button_connect->TabIndex = 10;
			this->button_connect->Text = L"Connect to Server";
			this->button_connect->UseVisualStyleBackColor = true;
			this->button_connect->Click += gcnew System::EventHandler(this, &ConnectServer::button_connect_Click);
			// 
			// ConnectServer
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(335, 300);
			this->Controls->Add(this->button_connect);
			this->Controls->Add(this->textBox_Port);
			this->Controls->Add(this->textBox_IP);
			this->Controls->Add(this->label_portAddr);
			this->Controls->Add(this->label_IPaddr);
			this->Name = L"ConnectServer";
			this->Text = L"ConnectServer";
			this->Load += gcnew System::EventHandler(this, &ConnectServer::ConnectServer_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ConnectServer_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button_connect_Click(System::Object^ sender, System::EventArgs^ e);
};
}
