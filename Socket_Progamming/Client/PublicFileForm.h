#pragma once

namespace Form_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for PublicFileForm
	/// </summary>
	public ref class PublicFileForm : public System::Windows::Forms::Form
	{
	public:
		PublicFileForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			pathFileToReceiver = splitPathFileToReceiver(System::Reflection::Assembly::GetEntryAssembly()->Location);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PublicFileForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^ listBox_fileName;
	private: System::Windows::Forms::Button^ button_upFile;
	private: System::Windows::Forms::Button^ button_downFile;
	protected:

	protected:


	private: System::Windows::Forms::ProgressBar^ progressBar1;
	private: System::Windows::Forms::Label^ label_fileName;
	private: System::Windows::Forms::Label^ label_process;

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
			this->listBox_fileName = (gcnew System::Windows::Forms::ListBox());
			this->button_upFile = (gcnew System::Windows::Forms::Button());
			this->button_downFile = (gcnew System::Windows::Forms::Button());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->label_fileName = (gcnew System::Windows::Forms::Label());
			this->label_process = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// listBox_fileName
			// 
			this->listBox_fileName->FormattingEnabled = true;
			this->listBox_fileName->ItemHeight = 16;
			this->listBox_fileName->Location = System::Drawing::Point(40, 44);
			this->listBox_fileName->Name = L"listBox_fileName";
			this->listBox_fileName->Size = System::Drawing::Size(520, 244);
			this->listBox_fileName->TabIndex = 0;
			this->listBox_fileName->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &PublicFileForm::listBox_fileName_OnMouseClick);
			// 
			// button_upFile
			// 
			this->button_upFile->Location = System::Drawing::Point(79, 304);
			this->button_upFile->Name = L"button_upFile";
			this->button_upFile->Size = System::Drawing::Size(130, 34);
			this->button_upFile->TabIndex = 2;
			this->button_upFile->Text = L"UPLOAD";
			this->button_upFile->UseVisualStyleBackColor = true;
			this->button_upFile->Click += gcnew System::EventHandler(this, &PublicFileForm::button_upFile_Click);
			// 
			// button_downFile
			// 
			this->button_downFile->Location = System::Drawing::Point(365, 304);
			this->button_downFile->Name = L"button_downFile";
			this->button_downFile->Size = System::Drawing::Size(130, 34);
			this->button_downFile->TabIndex = 3;
			this->button_downFile->Text = L"DOWNLOAD";
			this->button_downFile->UseVisualStyleBackColor = true;
			this->button_downFile->Click += gcnew System::EventHandler(this, &PublicFileForm::button_downFile_Click);
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(40, 371);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(520, 23);
			this->progressBar1->TabIndex = 4;
			// 
			// label_fileName
			// 
			this->label_fileName->AutoSize = true;
			this->label_fileName->Location = System::Drawing::Point(41, 16);
			this->label_fileName->Name = L"label_fileName";
			this->label_fileName->Size = System::Drawing::Size(79, 17);
			this->label_fileName->TabIndex = 5;
			this->label_fileName->Text = L"FILE NAME";
			// 
			// label_process
			// 
			this->label_process->AutoSize = true;
			this->label_process->Location = System::Drawing::Point(41, 351);
			this->label_process->Name = L"label_process";
			this->label_process->Size = System::Drawing::Size(74, 17);
			this->label_process->TabIndex = 6;
			this->label_process->Text = L"PROCESS";
			// 
			// PublicFileForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(607, 405);
			this->Controls->Add(this->label_process);
			this->Controls->Add(this->label_fileName);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->button_downFile);
			this->Controls->Add(this->button_upFile);
			this->Controls->Add(this->listBox_fileName);
			this->Name = L"PublicFileForm";
			this->Text = L"Upload/Download File";
			this->Load += gcnew System::EventHandler(this, &PublicFileForm::PublicFileForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	public: String^ fileNameToSend = nullptr;
	public: int fileSizeToSend = 0;
	// = System::Reflection::Assembly::GetEntryAssembly()->Location;
	public: FileStream^ writerStream = nullptr;
	public: String^ filePathToSend = nullptr;

	public: String^ fileNameToReceive = nullptr;
	public: String^ pathFileToReceiver;

	public: String^ splitPathFileToReceiver(String^ pathFile);
	private: System::Void PublicFileForm_Load(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button_upFile_Click(System::Object^ sender, System::EventArgs^ e);
	public: System::Void ThreadChooseFile();
	public:void setListFileName(array<String^>^ listFileName);
	public: void setUpProcessBar(int min, int max);
	public: void resetProcessBar();
	public: void setValueOfProcessBar(int value);
	private:System::Void listBox_fileName_OnMouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void button_downFile_Click(System::Object^ sender, System::EventArgs^ e);
	//public: System::Void receiveFileFormServer(DownloadPublicFileClass^ pubFile);
	};
}
