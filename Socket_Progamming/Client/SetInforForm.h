#pragma once

namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SetInforForm
	/// </summary>
	public ref class SetInforForm : public System::Windows::Forms::Form
	{
	public:
		SetInforForm(void)
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
		~SetInforForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ butSave;
	protected:
	private: System::Windows::Forms::TextBox^ txtBirthdate;
	private: System::Windows::Forms::Label^ labBirthdate;

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
			this->butSave = (gcnew System::Windows::Forms::Button());
			this->txtBirthdate = (gcnew System::Windows::Forms::TextBox());
			this->labBirthdate = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// butSave
			// 
			this->butSave->Location = System::Drawing::Point(94, 78);
			this->butSave->Margin = System::Windows::Forms::Padding(4);
			this->butSave->Name = L"butSave";
			this->butSave->Size = System::Drawing::Size(100, 28);
			this->butSave->TabIndex = 5;
			this->butSave->Text = L"Save";
			this->butSave->UseVisualStyleBackColor = true;
			this->butSave->Click += gcnew System::EventHandler(this, &SetInforForm::butSave_Click);
			// 
			// txtBirthdate
			// 
			this->txtBirthdate->Location = System::Drawing::Point(107, 27);
			this->txtBirthdate->Margin = System::Windows::Forms::Padding(4);
			this->txtBirthdate->Name = L"txtBirthdate";
			this->txtBirthdate->Size = System::Drawing::Size(132, 22);
			this->txtBirthdate->TabIndex = 4;
			// 
			// labBirthdate
			// 
			this->labBirthdate->AutoSize = true;
			this->labBirthdate->Location = System::Drawing::Point(30, 31);
			this->labBirthdate->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->labBirthdate->Name = L"labBirthdate";
			this->labBirthdate->Size = System::Drawing::Size(69, 17);
			this->labBirthdate->TabIndex = 3;
			this->labBirthdate->Text = L"Birthdate:";
			// 
			// SetInforForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(276, 119);
			this->Controls->Add(this->butSave);
			this->Controls->Add(this->txtBirthdate);
			this->Controls->Add(this->labBirthdate);
			this->Name = L"SetInforForm";
			this->Text = L"Set Information";
			this->Load += gcnew System::EventHandler(this, &SetInforForm::SetInforForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void SetInforForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void butSave_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
