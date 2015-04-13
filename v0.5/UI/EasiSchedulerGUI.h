//@author A09119454A
#include "msclr\marshal_cppstd.h"

#include "CommandExecution.h"



#include <string>

#include <algorithm>


#pragma once


namespace EasiSchedulerGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	#define MESSAGE_THANKS_FOR_USING_EASISCHEDULER "Thank you for using EasiScheduler!\r\n\r\n Enter \"help\" to view valid command. Enter \"add\" to add tasks ";
	#define REMINDER_MESSAGE_TO_ELIMINATE_EXTRA_SPACE "Thank you for using EasiScheduler!\r\n" + "Please make sure that command starts from the beginning of the line.\r\n" + "\"help\" to view valid command. Enter \"add\" to add tasks ";
	#define MESSAGE_FOR_HELP_GUIDE "A list of available command " + "\r\n\r\n  \"add\" for adding a task" + "\r\n  \"delete\" for delete a task" + "\r\n  \"search\" for searching a task" + "\r\n  \"update\" for updating a task" + "\r\n  \"mark\" for marking a task as done" + "\r\n  \"unmark\" for unmarking a done" + "\r\n  \"undo\" for undoing the last action" + "\r\n  \"redo\" for redoing the last action" + "\r\n  \"track\" for tracking past tasks" + "\r\n  \"location\" for changing location of task file""\r\n\r\n For complete User Guide, please refer to user manual" + "\r\n\r\n Enjoy using EasiScheduler!";			
	#define MESSAGE_FOR_ADD_GUIDE "Please follow the format to add new task" + "\r\n\r\n\t add [EVENT] -st [START_TIME] -et [END_TIME]" + "\r\n\r\nExample:" + "\r\n\t add task -st 2015 July 7 1000am -et July 7 1200PM" + "\r\n\r\n For missing information, EasiScheduler will append it as time now";
	#define MESSAGE_FOR_UPDATE_GUIDE "Please follow the format to add new task" + "\r\n\r\n\t update [INDEX] [EVENT] -st [START_TIME] -et [END_TIME]"+"\r\n\r\nExample:"+"\r\n\t update 1 task -st 2015 July 7 1000am -et July 7 1200PM" + "\r\n\r\nTo check index of the task, type \"search\"to search for the task you want to update" + "\r\n For missing information, EasiScheduler will append it as time now";
	#define MESSAGE_FOR_REDO_UNDO_TRACK_DISPLAY_GUIDE "To Redo, Undo, Track or Display" + "\r\n\r\n\t Press Enter to continue;";
	#define MESSAGE_FOR_MARK_UNMARK_DELETE_GUIDE "To Mark, Unmark or delete a certain task, type" + "\r\n\r\n\t mark/unmark/delete [INDEX]"+"\r\n\r\nTo check the index of the task, type \"display\" if the task is not due, \"track\" otherwise";
	#define MESSAGE_FOR_SEARCH_GUIDE "To search for a certain task" + "\r\n\r\n\t search [KEY_WORD]";
	#define MESSAGE_FOR_LOCATION_GUIDE "To change the location to save location" + "\r\n\r\n\t location [directory]"+"\r\nExample: \r\n             location C:\\Users\\UserName\\Desktop ";

	/// <summary>

	/// Summary for EasiScheduler

	/// </summary>

	public ref class EasiScheduler : public System::Windows::Forms::Form {
	private:
			CommandExecution *executor;
	//@author generated
	public:
		EasiScheduler(void){

			InitializeComponent();
			//
			executor= new CommandExecution();//TODO: Add the constructor code here
			//
		}
		protected:

		/// <summary>

		/// Clean up any resources being used.

		/// </summary>

		~EasiScheduler() {
			if (components) {
				delete components;
			}
		}

		private: System::Windows::Forms::TextBox^  outputWindow;
		private: System::Windows::Forms::TextBox^  inputBox;
		private: System::Windows::Forms::MonthCalendar^  monthCalendar1;
		private: System::Windows::Forms::TextBox^  notificationPanel;
		private: System::Windows::Forms::Label^  label1;
		private: System::Windows::Forms::TextBox^  textBox2;
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

			void InitializeComponent(void) {
			this->outputWindow = (gcnew System::Windows::Forms::TextBox());
			this->inputBox = (gcnew System::Windows::Forms::TextBox());
			this->monthCalendar1 = (gcnew System::Windows::Forms::MonthCalendar());
			this->notificationPanel = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// outputWindow
			// 
			this->outputWindow->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(229)), static_cast<System::Int32>(static_cast<System::Byte>(187)), 
				static_cast<System::Int32>(static_cast<System::Byte>(129)));
			this->outputWindow->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outputWindow->Font = (gcnew System::Drawing::Font(L"Times New Roman", 13.94764F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->outputWindow->ForeColor = System::Drawing::Color::MidnightBlue;
			this->outputWindow->Location = System::Drawing::Point(13, 12);
			this->outputWindow->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->outputWindow->Multiline = true;
			this->outputWindow->Name = L"outputWindow";
			this->outputWindow->ReadOnly = true;
			this->outputWindow->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->outputWindow->Size = System::Drawing::Size(786, 288);
			this->outputWindow->TabIndex = 3;
			//@author A09119454A
			this->outputWindow->Text = L"Welcom to EasiScheduler!\r\n Press any key to continue...";
			this->outputWindow->TextChanged += gcnew System::EventHandler(this, &EasiScheduler::outputWindow_TextChanged);
			// 
			// inputBox
			// 
			//@author generated
			this->inputBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(34)), static_cast<System::Int32>(static_cast<System::Byte>(8)), 
				static_cast<System::Int32>(static_cast<System::Byte>(7)));
			this->inputBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->inputBox->Font = (gcnew System::Drawing::Font(L"Cambria", 18.09424F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->inputBox->ForeColor = System::Drawing::Color::Transparent;
			this->inputBox->Location = System::Drawing::Point(12, 328);
			this->inputBox->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->inputBox->Name = L"inputBox";
			this->inputBox->Size = System::Drawing::Size(786, 29);
			this->inputBox->TabIndex = 1;
			this->inputBox->TextChanged += gcnew System::EventHandler(this, &EasiScheduler::inputBox_TextChanged);
			this->inputBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EasiScheduler::inputBox_KeyDown);
			// 
			// monthCalendar1
			// 
			this->monthCalendar1->BackColor = System::Drawing::Color::CadetBlue;
			this->monthCalendar1->Font = (gcnew System::Drawing::Font(L"Segoe Marker", 4.900524F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->monthCalendar1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->monthCalendar1->Location = System::Drawing::Point(52, 365);
			this->monthCalendar1->Margin = System::Windows::Forms::Padding(4);
			this->monthCalendar1->Name = L"monthCalendar1";
			this->monthCalendar1->TabIndex = 4;
			this->monthCalendar1->TitleForeColor = System::Drawing::Color::Chocolate;
			// 
			// notificationPanel
			// 
			this->notificationPanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(118)), 
				static_cast<System::Int32>(static_cast<System::Byte>(77)), static_cast<System::Int32>(static_cast<System::Byte>(57)));
			this->notificationPanel->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->notificationPanel->Font = (gcnew System::Drawing::Font(L"Calibri", 15.83246F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->notificationPanel->ForeColor = System::Drawing::Color::Moccasin;
			this->notificationPanel->Location = System::Drawing::Point(359, 381);
			this->notificationPanel->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->notificationPanel->Multiline = true;
			this->notificationPanel->Name = L"notificationPanel";
			this->notificationPanel->Size = System::Drawing::Size(375, 128);
			this->notificationPanel->TabIndex = 6;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 15.83246F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(420, 355);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(107, 27);
			this->label1->TabIndex = 7;
			this->label1->Text = L"What\'s Up";
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(118)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(57)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 15.83246F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->textBox2->ForeColor = System::Drawing::Color::GhostWhite;
			this->textBox2->Location = System::Drawing::Point(13, 302);
			this->textBox2->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(642, 26);
			this->textBox2->TabIndex = 8;
			//@author A09119454A
			this->textBox2->Text = L"Enter command here:";
			// 
			//@author generated

			// EasiScheduler
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(118)), static_cast<System::Int32>(static_cast<System::Byte>(77)), 
				static_cast<System::Int32>(static_cast<System::Byte>(57)));
			this->ClientSize = System::Drawing::Size(809, 531);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->notificationPanel);
			this->Controls->Add(this->monthCalendar1);
			this->Controls->Add(this->inputBox);
			this->Controls->Add(this->outputWindow);
			this->ForeColor = System::Drawing::Color::White;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Margin = System::Windows::Forms::Padding(2, 1, 2, 1);
			this->MaximizeBox = false;
			this->Name = L"EasiScheduler";
			this->Opacity = 0.94;
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Show;
			this->Text = L" ";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		#pragma endregion
		//@author A0108457B
		private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
					 System::String^ cmd_systemString = inputBox->Text;
					 std::string input = msclr::interop::marshal_as<std::string>(cmd_systemString);
					 std::string output = executor->readCommand(input);
					 String^ MyString = gcnew String(output.c_str());
					 outputWindow->Text = MyString;
					 inputBox->Text = "";
		}

		private: System::Void inputBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {	
					inputBox->ForeColor = System::Drawing::Color::White;
					String^ MyRecentTask;
					for (int i = 1;i <= 5; i++){
					  MyRecentTask += gcnew String(executor->readRecentTask(i).c_str());
					}
					notificationPanel->Text = MyRecentTask;
			
					if(e->KeyCode == Keys::Enter){
						if(inputBox->Text == ""){
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;

						 outputWindow->Text = MESSAGE_THANKS_FOR_USING_EASISCHEDULER;

						 } else {
						 button1_Click(sender, e);
						 }
					}
				 
					if (e->KeyCode == Keys::Down) {				
						int position = 0;				
						outputWindow->SelectionStart = outputWindow->TextLength;				
						outputWindow->ScrollToCaret();			
					} 
					 
					if (e->KeyCode == Keys::Up){
						int position = 0;			
						outputWindow->SelectionStart = 0;			
						outputWindow->ScrollToCaret();
					}

		}

		private: System::Void inputBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
					 outputWindow->ForeColor = System::Drawing::Color::MidnightBlue;

					 System::String^ cmd_systemString = inputBox->Text;
					 std::string input = msclr::interop::marshal_as<std::string>(cmd_systemString);
					 transform(input.begin(), input.end(), input.begin(), ::tolower);
			 
					 if(input.substr(0, 1) == " "){
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;

						 outputWindow->Text = REMINDER_MESSAGE_TO_ELIMINATE_EXTRA_SPACE
					 }
			 
					 if (input.substr(0, 4) =="help"){  
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;

						 outputWindow->Text = MESSAGE_FOR_HELP_GUIDE;		 
						 inputBox->Text = "";
					 }
			 
					if (input.substr(0, 3) == "add"){
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;
						 outputWindow->Text =MESSAGE_FOR_ADD_GUIDE;
					}

					if (input.substr(0, 6) == "update"){
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;
						 outputWindow->Text = MESSAGE_FOR_UPDATE_GUIDE;
					}

					if (input.substr(0, 4) == "redo" || input.substr(0, 4) == "undo" || input.substr(0, 5) == "track" || input.substr(0, 7) == "display"){
						 outputWindow->ForeColor = System::Drawing::Color::Maroon;
						 outputWindow->Text = MESSAGE_FOR_REDO_UNDO_TRACK_DISPLAY_GUIDE;
					
					}

					if (input.substr(0, 4) == "mark" || input.substr(0, 4) == "unmark" || input.substr(0, 6) == "delete"){
						outputWindow->ForeColor = System::Drawing::Color::Maroon;
						outputWindow->Text = MESSAGE_FOR_MARK_UNMARK_DELETE_GUIDE;
					}
			
					if (input.substr(0, 6) == "search"){
						outputWindow->ForeColor = System::Drawing::Color::Maroon;
						outputWindow->Text = MESSAGE_FOR_SEARCH_GUIDE;	
					}

					if (input.substr(0, 8) == "location"){
						outputWindow->ForeColor = System::Drawing::Color::Maroon;
						outputWindow->Text = MESSAGE_FOR_LOCATION_GUIDE;
					}

		}

		private: System::Void outputWindow_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		}

	};

};
