#include "EasiScheduler.h"
#include "interpreter.h"
#include "Storage.h"
#include "Task.h"
#include "commandExecution.h"


using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args) {
Application::EnableVisualStyles();
Application::SetCompatibleTextRenderingDefault(false);


UI::EasiScheduler mainWindow;
Application::Run(%mainWindow);
}