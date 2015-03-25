#include "stdafx.h"
#include "CppUnitTest.h"
#include "commandExecution.cpp"
#include "interpreter0.1-HZJ.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLogic {		

	TEST_CLASS(UnitTestLogic) {
	public:
		
		TEST_METHOD(TestPerformAdd) {
			// TODO: Your test code here
			CommandExecution test;
			string expected = "Successfully added ¡°on July 10 from 1400 to 1600 play basketball¡± to the schedule\n";
			string actual = test.readCommand("add July 10 -s 1400 -e 1600 play basketball");
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestPerformDelete) {
			//This is a boundary case for the 'value < 1' partition 
			CommandExecution test;
			string expected = "Invalid index!\n";
			string actual = test.readCommand("delete 0");
			Assert::AreEqual(expected, actual);
		}

	};
}