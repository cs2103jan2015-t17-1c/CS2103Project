#include "stdafx.h"
#include "CppUnitTest.h"
#include "commandExecution.cpp"
#include "interpreter0.2-HZJ.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLogic
{		
	TEST_CLASS(UnitTestPerformAdd)
	{
	public:
		TEST_METHOD(TestAddWrongInput) {
			CommandExecution test;
			string expected = "Wrong error format, plesae refer to user guide\r\n";
			string actual = test.readCommand("add");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestAddNormalTask) {
			// TODO: Your test code here
			CommandExecution test;
			string expected = "Successfully added 'on July 10 from 1400 to 1600 play basketball' to the schedule\r\n";
			string actual = test.readCommand("add July 10 -s 1400 -e 1600 play basketball");
			Assert::AreEqual(expected, actual);
		}
	};

	TEST_CLASS(UnitTestPerformDelete)
	{
	public:
		
		TEST_METHOD(TestPerformDelete1) {
			//This is a boundary case for the 'value < 1' partition 
			CommandExecution test;
			string expected = "Invalid index!\r\n";
			string actual = test.readCommand("delete 0");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestPerformDelete2) {
			//this is a boundary case for the 'value > size' partition
			CommandExecution test;
			string expected = "Invalid index!\r\n";
			string actual = test.readCommand("delete 1");
			Assert::AreEqual(expected, actual);
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

		TEST_METHOD(TestPerformDelete2) {
			//this is a boundary case for the 'value > size' partition
			CommandExecution test;
			string expected = "Invalid index!\r\n";
			string actual = test.readCommand("delete 1");
			Assert::AreEqual(expected, actual);
		}

	};

}