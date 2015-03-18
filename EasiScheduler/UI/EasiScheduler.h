#include "interpreter.h"
#include "Storage.h"
#include "Task.h"
#include "commandExecution.h"
#include "msclr\marshal_cppstd.h"
#pragma once

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EasiScheduler
	/// </summary>
	public ref class EasiScheduler : public System::Windows::Forms::Form
	{
	private:
		CommandExecution *executor;
	public:
		EasiScheduler(void)
		{
			InitializeComponent();
			//
			executor= new CommandExecution();//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EasiScheduler()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  outputBox;

	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  inputBox;

	private: System::Windows::Forms::Button^  EnterButton;

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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->outputBox = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->inputBox = (gcnew System::Windows::Forms::TextBox());
			this->EnterButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(31, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(115, 26);
			this->label1->TabIndex = 0;
			this->label1->Text = L"OutputBox";
			this->label1->Click += gcnew System::EventHandler(this, &EasiScheduler::button1_Click);
			// 
			// outputBox
			// 
			this->outputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->outputBox->ForeColor = System::Drawing::SystemColors::WindowFrame;
			this->outputBox->Location = System::Drawing::Point(36, 50);
			this->outputBox->Multiline = true;
			this->outputBox->Name = L"outputBox";
			this->outputBox->ReadOnly = true;
			this->outputBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->outputBox->Size = System::Drawing::Size(810, 207);
			this->outputBox->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(31, 260);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(98, 26);
			this->label2->TabIndex = 2;
			this->label2->Text = L"InputBox";
			this->label2->Click += gcnew System::EventHandler(this, &EasiScheduler::button1_Click);
			// 
			// inputBox
			// 
			this->inputBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->inputBox->Location = System::Drawing::Point(36, 289);
			this->inputBox->Multiline = true;
			this->inputBox->Name = L"inputBox";
			this->inputBox->Size = System::Drawing::Size(665, 56);
			this->inputBox->TabIndex = 3;
			// 
			// EnterButton
			// 
			this->EnterButton->Location = System::Drawing::Point(758, 289);
			this->EnterButton->Name = L"EnterButton";
			this->EnterButton->Size = System::Drawing::Size(88, 52);
			this->EnterButton->TabIndex = 4;
			this->EnterButton->Text = L"Enter";
			this->EnterButton->UseVisualStyleBackColor = true;
			this->EnterButton->Click += gcnew System::EventHandler(this, &EasiScheduler::button1_Click);
			// 
			// EasiScheduler
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Info;
			this->ClientSize = System::Drawing::Size(896, 390);
			this->Controls->Add(this->EnterButton);
			this->Controls->Add(this->inputBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->outputBox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"EasiScheduler";
			this->Text = L"EasiScheduler";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 System::String^ cmd_systemString = inputBox->Text;
			 std::string input = msclr::interop::marshal_as<std::string>(cmd_systemString);
			 std::string output=executor->readCommand(input);
			 String^ MyString = gcnew String(output.c_str());
			  outputBox->Text=MyString;
			  inputBox->Text="";
			  
			 
		 }
};
}
