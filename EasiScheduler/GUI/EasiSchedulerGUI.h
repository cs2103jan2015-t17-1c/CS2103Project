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



private: System::Windows::Forms::TextBox^  outputBox;





private: System::Windows::Forms::TextBox^  inputBox;
private: System::Windows::Forms::MonthCalendar^  monthCalendar1;






private: System::ComponentModel::IContainer^  components;







protected: 



private:

/// <summary>

/// Required designer variable.

/// </summary>





#pragma region Windows Form Designer generated code

/// <summary>

/// Required method for Designer support - do not modify

/// the contents of this method with the code editor.

/// </summary>

void InitializeComponent(void)

{
	this->outputBox = (gcnew System::Windows::Forms::TextBox());
	this->inputBox = (gcnew System::Windows::Forms::TextBox());
	this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
	this->SuspendLayout();
	// 
	// outputBox
	// 
	this->outputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(229)), static_cast<System::Int32>(static_cast<System::Byte>(187)), 
		static_cast<System::Int32>(static_cast<System::Byte>(129)));
	this->outputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->outputBox->Font = (gcnew System::Drawing::Font(L"Times New Roman", 10.17801F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->outputBox->ForeColor = System::Drawing::Color::Black;
	this->outputBox->Location = System::Drawing::Point(12, 12);
	this->outputBox->Multiline = true;
	this->outputBox->Name = L"outputBox";
	this->outputBox->ReadOnly = true;
	this->outputBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	this->outputBox->Size = System::Drawing::Size(1177, 365);
	this->outputBox->TabIndex = 1;
	this->outputBox->Text = L"Welcom to EasiScheduler! Press enter to continue";
	this->outputBox->TextChanged += gcnew System::EventHandler(this, &EasiScheduler::outputBox_TextChanged);
	// 
	// inputBox
	// 
	this->inputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(8)), 
		static_cast<System::Int32>(static_cast<System::Byte>(7)));
	this->inputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->inputBox->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12.06283F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->inputBox->ForeColor = System::Drawing::Color::Transparent;
	this->inputBox->Location = System::Drawing::Point(12, 383);
	this->inputBox->Name = L"inputBox";
	this->inputBox->Size = System::Drawing::Size(1177, 38);
	this->inputBox->TabIndex = 3;
	this->inputBox->Text = L"Enter your command here";
	this->inputBox->TextChanged += gcnew System::EventHandler(this, &EasiScheduler::inputBox_TextChanged);
	this->inputBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EasiScheduler::inputBox_KeyDown);
	// 
	// monthCalendar1
	// 
	this->monthCalendar1->BackColor = System::Drawing::Color::CadetBlue;
	this->monthCalendar1->Font = (gcnew System::Drawing::Font(L"Segoe Marker", 4.900524F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->monthCalendar1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
	this->monthCalendar1->Location = System::Drawing::Point(12, 433);
	this->monthCalendar1->Name = L"monthCalendar1";
	this->monthCalendar1->TabIndex = 4;
	this->monthCalendar1->TitleForeColor = System::Drawing::Color::Chocolate;
	// 
	// EasiScheduler
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(118)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
		static_cast<System::Int32>(static_cast<System::Byte>(57)));
	this->ClientSize = System::Drawing::Size(1197, 792);
	this->Controls->Add(this->monthCalendar1);
	this->Controls->Add(this->inputBox);
	this->Controls->Add(this->outputBox);
	this->ForeColor = System::Drawing::Color::White;
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->Name = L"EasiScheduler";
	this->Opacity = 0.94;
	this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
	this->Text = L" ";
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

private: System::Void inputBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			inputBox->ForeColor = System::Drawing::Color::White;
			
			if(e->KeyCode==Keys::Enter){
				 button1_Click(sender,e);
			 }
		 }



private: System::Void inputBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (inputBox->Text=="help")
			 { 
				 outputBox->Text="Are you looking for some help? (y/n)";
				 inputBox->Text="";
			 }
			 if(inputBox->Text=="y")
			 {
					 outputBox->Text="Below are some basic syntax"+
						 "\r\n [ADD\tsyntax]\tadd MONTH DATE -s START_TIME -e END_TIME EVENT"+
						 "\r\n\t e.g. add July 7 -s 1200 -e 1400 Lunch with Mary"+
						 "\r\n [DISPLAY\tsyntax]\tdisplay"+
						 "\r\n [UPDATE\tsyntax]\tupdate INDEX MONTH DATE -S START_TIME -e END_TIME EVENT"+
						 "\r\n [SEARCH\tsyntax]\tsearch KEY_WORD"+
						 "\r\n [DELETE\tsyntax]\tdelete INDEX"+
						 "\r\n\t $$Sticknote$$ :) You may need to display first before update or delete to check index"+
						 "\r\n\r\n For complete User Guide, please check #########(user manual directory)";
			 }
			if(inputBox->Text=="n")
			{
				outputBox->Text="Sorry for troubling you, please proceed to enter your command";
			}
		 }
private: System::Void outputBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 if		(outputBox->Text=="")
			 {
					 outputBox->Text="Please make sure:"+
									"\r\n 1. Your command is entered from the start line of the cell"+
									"\r\n 2. Your command is in the correct format."+
									"\r\n To see a brief syntax guide, enter \"help\"";
			 }
		 }
};

}

