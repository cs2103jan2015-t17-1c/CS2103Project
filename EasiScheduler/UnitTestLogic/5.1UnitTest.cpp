#include "stdafx.h"
#include "CppUnitTest.h"
#include "CommandExecution.cpp"
#include "SmartAdder.cpp"
#include "CommandChecker.cpp"
#include "Storage.cpp"
#include "Task.cpp"
#include "CurrentTime.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLogic {	

	TEST_CLASS(UnitTestReadCommand)
	{
	public:
		TEST_METHOD(TestGetCommand) {
			CommandExecution test;
			size_t endExpected;
			size_t endActual;
			string expected;
			string actual;

			expected = "add";
			endExpected = 3;
			actual = test.getCommand("add something", endActual);
			Assert::AreEqual(expected, actual);
			Assert::AreEqual(endExpected, endActual);
		}	

		TEST_METHOD(TestIsExit) {
			CommandExecution test;
			Assert::AreEqual(true, test.isExit("exit"));
	//		Assert::AreEqual(true, test.isExit("EXIT"));
			Assert::AreNotEqual(true, test.isExit("notExit"));
		}

		//should be all in lower form. 
		/*TEST_METHOD(TestIsSingleWordCommand) {
			CommandExecution test;
			Assert::AreEqual(true, test.isSingleWordCommand("display"));
			Assert::AreEqual(true, test.isSingleWordCommand("TRACK"));
			Assert::AreEqual(true, test.isSingleWordCommand("Undo"));
			Assert::AreEqual(true, test.isSingleWordCommand("REDo"));
			Assert::AreNotEqual(true, test.isExit("add"));
		}*/

		TEST_METHOD(TestIsInvalidFormat) {
			CommandExecution test;
			size_t end = string::npos;
			//test end == npos which is valid format condition 
			Assert::AreEqual(false, test.isInvalidFormat("display", end));
			//test end != npos, but find_first_not_of(" ") == npos which is valid format condition 
			Assert::AreEqual(false, test.isInvalidFormat("display    ", 7));
			//test satisfy both  invalid condtions
			Assert::AreEqual(true, test.isInvalidFormat("display 1", 7));
		}


		TEST_METHOD(TestDetermineCommandType) {
			CommandExecution test;
			bool actual = false;
			//test enum
			if(test.determineCommandType("add") == test.ADD) {
				actual = true;
			}
			Assert::AreEqual(true, actual);

			actual = false;
			if(test.determineCommandType("haha") == test.INVALID) {
				actual = true;
			}
			Assert::AreEqual(true, actual);
		}

	/*	TEST_METHOD(TestRetrieveContent) {
			CommandExecution test;
			string dummy;
			string expected = "test case 1 -st 1000am -et 0300pm";
			test.retrieveContent("add test case 1 -st 1000am -et 0300pm", 3);
			string actual = test.retrieveContent();
			Assert::AreEqual(expected, actual);

			expected = "   ";
			test.retrieveContent("add    ", 3);
			actual = test.retrieveContent();
			Assert::AreEqual(expected, actual);


			expected = "12";
			test.retrieveContent("delete 12", 6);
			actual = test.retrieveContent();
			Assert::AreEqual(expected, actual);
		} */


		TEST_METHOD(TestIsEmptyContent) {
			CommandExecution test;
			Assert::AreEqual(true, test.isEmptyContent("    "));
			Assert::AreNotEqual(true, test.isEmptyContent("   a "));
		}


		TEST_METHOD(TestWrongCommandFormat) {
			CommandExecution test;
			string expected = "Wrong command format, plesae refer to user guide\r\n";
			string actual = test.readCommand("add");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("display 1");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("plus hello");
			Assert::AreEqual(expected, actual);
			
		}

		TEST_METHOD(TestEmptyContentMessage) {
			CommandExecution test;
			string expected = "Don't be lazy, please type something\r\n";
			string actual = test.readCommand("add ");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("delete    ");
			Assert::AreEqual(expected, actual);
		}

		
	};
	

	TEST_CLASS(UnitTestPerformAdd) {
	public:
		TEST_METHOD(TestInvalidAdd) {
			CommandExecution test;
			string expected = "Invalid ADD Input\r\n";
			string actual = test.readCommand("add test case -st 2015 April 15 1100am");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st April 15 1100am");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 15 1100am");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 2015 1100");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100");
			Assert::AreEqual(expected, actual);

			//more aggressive cases
			test.performAdd(actual, "test case -st -st -st");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am -et 1100pm -st 1100am ");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am -et 1100pm -st 1100am ");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "add test case -et 1100am -et 1100pm -st 1100am ");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "add test case -st1100am -et1100pm");
			Assert::AreEqual(expected, actual);


		}

		TEST_METHOD(TestIsScheduleTask) {
			CommandExecution test;
			//-1 means no year entered by user
			Assert::AreEqual(true, test.isScheduleTask(2015, 2015));
			Assert::AreNotEqual(true, test.isScheduleTask(2015, -1));
			Assert::AreNotEqual(true, test.isScheduleTask(-1, 2015));
			Assert::AreNotEqual(true, test.isScheduleTask(-1, -1));
		}

		TEST_METHOD(TestIsDeadlineTask) {
			CommandExecution test;
			//-1 means no year entered by user
			Assert::AreEqual(true, test.isDeadlineTask(-1, 2015));
			Assert::AreNotEqual(true, test.isDeadlineTask(2015, -1));
			Assert::AreNotEqual(true, test.isDeadlineTask(-1, -1));
			Assert::AreNotEqual(true, test.isDeadlineTask(2015, 2015));
		}

		TEST_METHOD(TestGetAddResult) {
			CommandExecution test;
			//Schedule tasks
			string expected = "Successfully added (Schedule Task) 'Schedule test case' to the schedule\r\n";
			string actual = test.getAddResult(2015, 2016, "Schedule test case");
			Assert::AreEqual(expected, actual);
			
			//deadline tasks
			expected = "Successfully added (Deadline Task) 'deadline test case' to the schedule\r\n";
			actual = test.getAddResult(2015, -1, "deadline test case");

			//floating tasks
			expected = "Successfully added (Floating Task) 'floating test case' to the schedule\r\n";
			actual = test.getAddResult(-1, -1, "floating test case");
		}

		TEST_METHOD(TestTaskAdded) {
			CommandExecution test;
			string expected = "Successfully added (Schedule Task) 'test case' to the schedule\r\n";;
			string actual;

			//Schedule tasks
			test.performAdd(actual, "test case -st 2015 April 16 1100am -et 2015 April 17 0400pm");
			Assert::AreEqual(expected, actual);
			
			test.performAdd(actual, "test case -st 2015 April 16 1100am -et 2015 April 17 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st April 16 1100am -et 2015 April 17 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 16 1100am -et 2015 April 17 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am -et April 14 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -st 1100am -et 0400pm");
			Assert::AreEqual(expected, actual);

			//Deadline tasks
			expected = "Successfully added (Deadline Task) 'test case' to the schedule\r\n";

			test.performAdd(actual, "test case -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -et April 14 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -et 14 0400pm");
			Assert::AreEqual(expected, actual);

			test.performAdd(actual, "test case -et 0400pm");
			Assert::AreEqual(expected, actual);

			//floating tasks
			expected = "Successfully added (Floating Task) 'test case' to the schedule\r\n";
			test.performAdd(actual, "test case");
			Assert::AreEqual(expected, actual);
			
		}

	};

	TEST_CLASS(UnitTestPerformDelete) {
	public:
		
		TEST_METHOD(TestDeleteInvalidIndex) {
			remove("Easicalendar.txt"); 
			CommandExecution test;
			string dummy;
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");
			
			//This is a boundary case for the 'value < 1' partition 
			string expected = "Invalid index\r\n";
			string actual;
			test.performDelete(actual, "0");
			Assert::AreEqual(expected, actual);

			//This is a boundary case for the 'value > size' partition 
			test.performDelete(actual, "3");
			Assert::AreEqual(expected, actual);
			test.performDelete(actual, "4");
			Assert::AreEqual(expected, actual);
			
			//after one successful deletion
			test.performDelete(actual, "1");
			Assert::AreNotEqual(expected, actual);
			test.performDelete(actual, "1");
			Assert::AreEqual(expected, actual);

			//other cases
			test.performDelete(actual, "a");
			Assert::AreEqual(expected, actual);
			test.performDelete(actual, "a1");
			Assert::AreEqual(expected, actual);
			test.performDelete(actual, "@@");
			Assert::AreEqual(expected, actual);
			test.performDelete(actual, "1a");
			Assert::AreEqual(expected, actual);
	
		}

		TEST_METHOD(TestSuccessfulDeletion) {
			CommandExecution test;
			string dummy;
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");

			string expected = "Successfully deleted\r\n";
			string actual;
			test.performDelete(actual, "1");
			Assert::AreEqual(expected, actual);
			test.performDelete(actual, "2");
			Assert::AreEqual(expected, actual);
		} 
	};

	TEST_CLASS(UnitTestPerformUpdate)
	{
	public:
		
		TEST_METHOD(TestInvalidUpdate) {
			CommandExecution test;
			string expected = "Invalid index\r\n";
			string actual;
			
			//This is a boundary case for the 'value < 1' partition 
			test.performUpdate(actual, "0 testing");
			Assert::AreEqual(expected, actual);

			//This is a boundary case for the 'value > size' partition 
			string dummy;
			
			test.performAdd(dummy, "test case 1");
			test.performUpdate(actual, "    2     testing");
			Assert::AreEqual(expected, actual);

			//other cases
			test.performUpdate(actual, "a testing");
			Assert::AreEqual(expected, actual);
			test.performUpdate(actual, "a1 testing");
			Assert::AreEqual(expected, actual);
			test.performUpdate(actual, "@@ testing");
			Assert::AreEqual(expected, actual);
		

			//cases when unit no is deleted
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");
			test.performAdd(dummy, "test case 3");
			test.performDelete(dummy, "1");
			test.performDelete(dummy, "3");
			test.performUpdate(actual, "1 testing");
			Assert::AreEqual(expected, actual);
			test.performUpdate(actual, "3 testing");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSeperateInputForUpdate) {
			CommandExecution test;
			int expectedIndex = 2;
			string expected = "test case -st 2015 -et 2016";
			int actualIndex;
			string actual;
			test.seperateInputForUpdate("2 test case -st 2015 -et 2016", actualIndex, actual);
			Assert::AreEqual(expectedIndex, actualIndex);
			Assert::AreEqual(expected, actual);

			expectedIndex = 5;
			expected = "test case -st 2015 -et 2016";
			test.seperateInputForUpdate("    5       test case -st 2015 -et 2016", actualIndex, actual);
			Assert::AreEqual(expectedIndex, actualIndex);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestSuccessfulUpdate) {
		    
			CommandExecution test;
			string expected = "The event is updated\r\n";
			string actual;
			string dummy;
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");

			test.performUpdate(actual, "1 testing");
			Assert::AreEqual(expected, actual);
			test.performUpdate(actual, "2 testing");
			Assert::AreEqual(expected, actual);
		}
		
	};
	

	TEST_CLASS(UnitTestPerformDisplay)
	{
	public:
		TEST_METHOD(TestEmptyDisplayEmptySchedule) {
			CommandExecution test;
			string expected = "Schedule is empty\r\n";
			string actual;
			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);

			//after add and delete
			string dummy;
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");
			test.performDelete(dummy, "1");
			test.performDelete(dummy, "2");
			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);

			//after mark 
			test.performAdd(dummy, "test case 1");
			test.performAdd(dummy, "test case 2");
			test.performMark(dummy, "3");
			test.performMark(dummy, "4");
			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);
		}

/*		TEST_METHOD(TestDisplayResult) {
			CommandExecution test;
			
			string expected = "Displaying:\r\nUnit No.0001 2015/04/16/0800 - 2015/04/17/2200[Overdue] Event: test case 1\r\nUnit No.0002 ----/--/--/---- - 2016/12/08/1300          Event: test case 2\r\nUnit No.0003 ----/--/--/---- - ----/--/--/----          Event: test case 3\r\n";
			string actual;
			string dummy;
			test.performAdd(dummy, "test case 1 -st 2015 April 16 0800am -et 2015 April 17 1000pm");
			test.performAdd(dummy, "test case 2 -et 2016 December 8 0100pm");
			test.performAdd(dummy, "test case 3");

			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);
		}*/

		
	};




	TEST_CLASS(UnitTestPerformSearch)
	{
	public:
		
		TEST_METHOD(TestSearchNoMatch) {
			CommandExecution test;
			string expected = "no match!\r\n";
			string actual;
			test.performSearch(actual, "no matach");
			Assert::AreEqual(expected, actual);

			string dummy;
			test.performAdd(dummy, "test 1");
			test.performAdd(dummy, "test case 2");
			test.performAdd(dummy, "testing 3");
			test.performSearch(actual, "4");
			Assert::AreEqual(expected, actual);

			test.performDelete(dummy, "2");
			test.performSearch(actual, "case");
			Assert::AreEqual(expected, actual);

			//if a task is marked, can we still search for it? if yes, do we need to tell user its marked?
			//if this is ok just help me delete this part
			//help me write down whats the correct format for a successful search,in this case eg search testing
		//	test.performMark(dummy, "1");
		//	test.performSearch(actual, "test");
		//	Assert::AreEqual(expected, actual);
	   //since the testing also cover test
		}
	};

	TEST_CLASS(UnitTestPerformUndoRedo)
	{
	public:
		TEST_METHOD(TestUndoAndRedoFunctionality) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Schedule is empty\r\n";
			test.performAdd(dummy, "test case");
			test.performDisplay(actual);
			//since add a task, schedule is not empty
			Assert::AreNotEqual(expected, actual);
			//undo
			test.performUndo(dummy);
			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);
			//redo
			test.performRedo(dummy);
			test.performDisplay(actual);
			Assert::AreNotEqual(expected, actual);
		}

		TEST_METHOD(TestUndoMessage) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Undo is successful\r\n";
			test.performAdd(dummy, "test case");
			test.performUndo(actual);
			Assert::AreEqual(expected, actual);
		}
		
		TEST_METHOD(TestInvalidUndoMessage) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Cannot undo twice\r\n";
			test.performAdd(dummy, "test case");
			test.performUndo(dummy);
			test.performUndo(actual);
			Assert::AreEqual(expected, actual);
		}


		TEST_METHOD(TestRedoMessage) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Redo is successful\r\n";
			test.performAdd(dummy, "test case");
			test.performUndo(dummy);
			test.performRedo(actual);
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestInvalidRedoMessage) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Cannot redo because no UNDO command has been done\r\n";
			test.performAdd(dummy, "test case");
			test.performRedo(actual);
			Assert::AreEqual(expected, actual);

			//redo is performed twice is invalid
			test.performUndo(dummy);
			test.performRedo(dummy);
			test.performRedo(actual);
			Assert::AreEqual(expected, actual);
		}
	};

	TEST_CLASS(UnitTestPerformMarkUnmark)
	{
	public:
		TEST_METHOD(TestInvalidMark) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Invalid index\r\n";

			test.performAdd(dummy, "test case");
			//This is a boundary case for the 'value < 1' partition 
			test.performMark(actual, "0");
			Assert::AreEqual(expected, actual);
			
			//This is a boundary case for the 'value > size' partition 
			test.performMark(actual, "2");
			Assert::AreEqual(expected, actual);

			//other cases
			test.performMark(actual, "a");
			Assert::AreEqual(expected, actual);
			test.performMark(actual, "a1");
			Assert::AreEqual(expected, actual);
			test.performMark(actual, "@@");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestInvalidUnmark) {
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Invalid index\r\n";

			test.performAdd(dummy, "test case");
			//This is a boundary case for the 'value < 1' partition 
			test.performMark(dummy, "1");

			test.performUnmark(actual, "0");
			Assert::AreEqual(expected, actual);
			
			//This is a boundary case for the 'value > size' partition 
			test.performUnmark(actual, "2");
			Assert::AreEqual(expected, actual);


			//other cases
			test.performUnmark(actual, "a");
			Assert::AreEqual(expected, actual);
			test.performUnmark(actual, "a1");
			Assert::AreEqual(expected, actual);
			test.performUnmark(actual, "@@");
			Assert::AreEqual(expected, actual);
			
		}

		TEST_METHOD(TestValidMarkAndUnmark) {
			CommandExecution test;
			string dummy;
			string actual;
			string expectedMark = "Event marked done\r\n";
			string expectedUnmark = "Event unmarked done\r\n";

			test.performAdd(dummy, "test case");
			test.performMark(actual, "1");
			Assert::AreEqual(expectedMark, actual);
			
			test.performUnmark(actual, "1");
			Assert::AreEqual(expectedUnmark, actual);
		}

		TEST_METHOD(TestMarkAndUnmarkFunctionality) {
			
			CommandExecution test;
			string dummy;
			string actual;
			string expected = "Schedule is empty\r\n";

			test.performAdd(dummy, "test case");
			test.performDisplay(actual);

			//since added a task, schedule is displaying the task 'test case'
			Assert::AreNotEqual(expected, actual);

			//mark and the marked event will go to track list, so there is nothing to display
			test.performMark(dummy, "1");
			test.performDisplay(actual);
			Assert::AreEqual(expected, actual);
			
			//unmark and the event will come back showing in display mode
			test.performUnmark(dummy, "1");
			test.performDisplay(actual);
			Assert::AreNotEqual(expected, actual);
		
		}
	};


	TEST_CLASS(UnitTestPerformTrack)
	{
	public:
		
		TEST_METHOD(TestTrackingFunctionality) {
			CommandExecution test;
			string expected = "Tracking:\r\n";
			string dummy;
			string actual;
			test.performAdd(dummy, "test case 1 -st 2015 April 16 0800am -et 2015 April 17 1000pm");
			test.performAdd(dummy, "test case 2 -et 2016 December 8 0100pm");
			test.performAdd(dummy, "test case 3");

			//initially no tasks in tracking list
			test.performTrack(actual);
			Assert::AreEqual(expected, actual);

			//mark events
			expected = "Tracking:\r\nUnit No.0001 2015/04/16/0800 - 2015/04/17/2200   Event: test case 1\r\nUnit No.0002 ----/--/--/---- - 2016/12/08/1300   Event: test case 2\r\nUnit No.0003 ----/--/--/---- - ----/--/--/----   Event: test case 3\r\n";
			test.performMark(dummy, "1");
			test.performMark(dummy, "2");
			test.performMark(dummy, "3");
			test.performTrack(actual);
			Assert::AreEqual(expected, actual);

			//unmark events
			test.performUnmark(dummy, "1");
			test.performUnmark(dummy, "2");
			test.performUnmark(dummy, "3");
			expected = "Tracking:\r\n";
			test.performTrack(actual);
			Assert::AreEqual(expected, actual);
		}
	};

	TEST_CLASS(UnitTestPerformLocation)
	{
	public:
		
		TEST_METHOD(TestLocationResult) {
			CommandExecution test;
			string expected = "Changed File Location to C:\\Users\\user\\Documents\\Visual Studio 2012\\MySchedule.txt\r\n";
			string actual;
			test.performLocation(actual, "C:\\Users\\user\\Documents\\Visual Studio 2012\\MySchedule.txt");
			Assert::AreEqual(expected, actual);

		}
	};
}