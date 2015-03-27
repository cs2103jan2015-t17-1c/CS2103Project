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


private: System::Windows::Forms::HelpProvider^  helpProvider1;
private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
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
	this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
	this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
	this->SuspendLayout();
	// 
	// outputBox
	// 
	this->outputBox->BackColor = System::Drawing::Color::CadetBlue;
	this->outputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->outputBox->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12.06283F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->outputBox->ForeColor = System::Drawing::Color::LemonChiffon;
	this->outputBox->Location = System::Drawing::Point(12, 26);
	this->outputBox->Multiline = true;
	this->outputBox->Name = L"outputBox";
	this->outputBox->ReadOnly = true;
	this->outputBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
	this->outputBox->Size = System::Drawing::Size(1178, 472);
	this->outputBox->TabIndex = 1;
	this->outputBox->Text = L"Welcome to EasiScheduler!";
	// 
	// inputBox
	// 
	this->inputBox->BackColor = System::Drawing::Color::Thistle;
	this->inputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
	this->inputBox->Font = (gcnew System::Drawing::Font(L"Trebuchet MS", 12.06283F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
		static_cast<System::Byte>(0)));
	this->inputBox->ForeColor = System::Drawing::Color::Black;
	this->inputBox->Location = System::Drawing::Point(12, 526);
	this->inputBox->Multiline = true;
	this->inputBox->Name = L"inputBox";
	this->inputBox->Size = System::Drawing::Size(1163, 57);
	this->inputBox->TabIndex = 3;
	this->inputBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EasiScheduler::inputBox_KeyDown);
	this->outputBox->Text = L"Enter your command here";
	// 
	// monthCalendar1
	// 
	this->monthCalendar1->Location = System::Drawing::Point(1203, 26);
	this->monthCalendar1->Name = L"monthCalendar1";
	this->monthCalendar1->TabIndex = 4;
	// 
	// EasiScheduler
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->BackColor = System::Drawing::Color::Linen;
	this->ClientSize = System::Drawing::Size(1621, 639);
	this->Controls->Add(this->monthCalendar1);
	this->Controls->Add(this->inputBox);
	this->Controls->Add(this->outputBox);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
	this->MaximumSize = System::Drawing::Size(1670, 708);
	this->MinimumSize = System::Drawing::Size(1640, 708);
	this->Name = L"EasiScheduler";
	this->Opacity = 0.94;
	this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
	this->Text = L"EasiScheduler";
	this->Load += gcnew System::EventHandler(this, &EasiScheduler::EasiScheduler_Load);
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
  inputBox->ForeColor = System::Drawing::Color::Gray;
  inputBox->Text="Enter your command here";
   
 

 

}

private: System::Void inputBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			inputBox->ForeColor = System::Drawing::Color::Black;
			if(inputBox->Text=="[DELETE THIS]Enter your command here")
			{inputBox->Text=="";
			}
			if(e->KeyCode==Keys::Enter){
				 button1_Click(sender,e);
			 }
		 }

private: System::Void EasiScheduler_Load(System::Object^  sender, System::EventArgs^  e) {
		 }
};

}

