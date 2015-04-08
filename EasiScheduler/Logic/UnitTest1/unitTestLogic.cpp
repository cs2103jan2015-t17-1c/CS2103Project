#include "stdafx.h"
#include "CppUnitTest.h"
#include "commandExecution.cpp"
#include "interpreter0.2-HZJ.cpp"
#include "Storage.cpp"
#include "Task.cpp"
#include "CurrentTime.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLogic
{		
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
			Assert::AreNotEqual(true, test.isExit("notExit"));
		}

		TEST_METHOD(TestIsSingleWordCommand) {
			CommandExecution test;
			Assert::AreEqual(true, test.isSingleWordCommand("display"));
			Assert::AreEqual(true, test.isSingleWordCommand("track"));
			Assert::AreNotEqual(true, test.isExit("add"));
		}

		TEST_METHOD(TestIsInvalidFormat) {
			CommandExecution test;
			size_t end = string::npos;
			//test end == npos which is valid format condition 
			Assert::AreEqual(false, test.isInvalidFormat(end, "display"));
			//test end != npos, but find_first_not_of(" ") == npos which is valid format condition 
			Assert::AreEqual(false, test.isInvalidFormat(7, "display    "));
			//test satisfy both  invalid condtions
			Assert::AreEqual(true, test.isInvalidFormat(7, "display 1"));
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

		TEST_METHOD(TestRetrieveContent) {
			CommandExecution test;

			string expected = "hello -st 1000am -et 0300pm";
			test.retrieveContent("add hello -st 1000am -et 0300pm", 3);
			string actual = test.getContent();
			Assert::AreEqual(expected, actual);

			expected = "   ";
			test.retrieveContent("add    ", 3);
			actual = test.getContent();
			Assert::AreEqual(expected, actual);

			expected = "12";
			test.retrieveContent("delete 12", 6);
			actual = test.getContent();
			Assert::AreEqual(expected, actual);
		}


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

		TEST_METHOD(TestEmptyContent) {
			CommandExecution test;
			string expected = "Don't be lazy, please type something\r\n";
			string actual = test.readCommand("add ");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("delete  ");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestTaskAdded) {
			CommandExecution test;
			string expected = "Successfully added 'test case' to the schedule\r\n";;
			string actual;
			//normal tasks

			actual = test.readCommand("add test case -st 2015 April 16 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 2015 April 16 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st April 16 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 16 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 1100am -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 1100am -et April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 1100am -et 0400pm");
			Assert::AreEqual(expected, actual);

			//Deadline tasks
			actual = test.readCommand("add test case -et 2015 April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -et April 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -et 14 0400pm");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -et 0400pm");
			Assert::AreEqual(expected, actual);

			//floating tasks
			actual = test.readCommand("add test case");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestInvalidAdd) {
			CommandExecution test;
			string expected = "Invalid ADD Input\r\n";
			string actual = test.readCommand("add test case -st 2015 April 15 1100am");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st April 15 1100am");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 15 1100am");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 1100am");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 2015 1100");
			Assert::AreEqual(expected, actual);

			actual = test.readCommand("add test case -st 1100");
			Assert::AreEqual(expected, actual);
		}
	};



	TEST_CLASS(UnitTestPerformDelete)
	{
	public:
		
		TEST_METHOD(TestDeleteInvalidIndex) {
			//This is a boundary case for the 'value < 1' partition 
			CommandExecution test;
			string expected = "Invalid index!\r\n";
			string actual = test.readCommand("delete 0");
			Assert::AreEqual(expected, actual);

			//This is a boundary case for the 'value > size' partition 
			string dummy = test.readCommand("add test case");
			cout<<test.getSize();
			Assert::AreEqual(0, test.getSize());
		}

	};

	TEST_CLASS(UnitTestPerformDisplay)
	{
	public:
		
		TEST_METHOD(TestDisplayWrongFormat) {
			CommandExecution test;
			string expected = "Wrong error format, plesae refer to user guide\r\n";
			string actual = test.readCommand("display 1");
			Assert::AreEqual(expected, actual);
		}

	};

}
