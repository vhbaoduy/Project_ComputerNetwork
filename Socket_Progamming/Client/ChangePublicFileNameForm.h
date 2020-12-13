#pragma once

namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	

	/// <summary>
	/// Summary for ChangePublicFileNameForm
	/// </summary>
	public ref class ChangePublicFileNameForm : public System::Windows::Forms::Form
	{
	public:
		ChangePublicFileNameForm(void)
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
		~ChangePublicFileNameForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label_newName;
	protected:
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button_OK;

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
			this->label_newName = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button_OK = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label_newName
			// 
			this->label_newName->AutoSize = true;
			this->label_newName->Location = System::Drawing::Point(24, 34);
			this->label_newName->Name = L"label_newName";
			this->label_newName->Size = System::Drawing::Size(102, 17);
			this->label_newName->TabIndex = 0;
			this->label_newName->Text = L"New File Name";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(151, 34);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(249, 22);
			this->textBox1->TabIndex = 1;
			// 
			// button_OK
			// 
			this->button_OK->Location = System::Drawing::Point(103, 80);
			this->button_OK->Name = L"button_OK";
			this->button_OK->Size = System::Drawing::Size(236, 42);
			this->button_OK->TabIndex = 2;
			this->button_OK->Text = L"OK";
			this->button_OK->UseVisualStyleBackColor = true;
			this->button_OK->Click += gcnew System::EventHandler(this, &ChangePublicFileNameForm::button_OK_Click);
			// 
			// ChangePublicFileNameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(441, 134);
			this->Controls->Add(this->button_OK);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label_newName);
			this->Name = L"ChangePublicFileNameForm";
			this->Text = L"Change File Name";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &ChangePublicFileNameForm::Form_Closing);
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &ChangePublicFileNameForm::Form_Closed);
			this->Load += gcnew System::EventHandler(this, &ChangePublicFileNameForm::ChangePublicFileNameForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: String^ fileName = nullptr;
	private: System::Void button_OK_Click(System::Object^ sender, System::EventArgs^ e);
	public: String^ stringOfNewFileName();
	private: System::Void Form_Closing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e);
	private: System::Void Form_Closed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e);

	private: System::Void ChangePublicFileNameForm_Load(System::Object^ sender, System::EventArgs^ e);
	};
}
