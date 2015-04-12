#include "EasiSchedulerGUI.h"
#include "CommandExecution.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThread]



void main(array<String^>^ args) {

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	EasiSchedulerGUI::EasiScheduler mainWindow;

	Application::Run(%mainWindow);

}