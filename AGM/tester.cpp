/*****************************************************************************
 * -- AGM SAR --
 * --------------------------------------------------------------------
 * Copyright (C) 2001-2008 AGM, a team comprising Andre Oboler, Gareth
 * Thompson and Michael Eldridge.
 * --------------------------------------------------------------------
 * This file is part of AGM SAR.
 *
 * AGM SAR is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation. However, this
 * notice must be retained.
 *
 * AGM SAR uses the SORAL library, available separately under the GNU
 * General Public License, and distributed here in compliance with
 * that license.
 *
 * AGM SAR is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. Use is at your
 * own risk. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with AGM SAR (see license.txt). If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * We are willing to offer alternative licensing arrangements if
 * necessary.  Our contact details are in readme.txt.
 * --------------------------------------------------------------------
 * --------------------------------------------------------------------
 * tester.cpp
 *
 * Test program for testing classes and functions used in the
 * Search and Rescue Program.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 09/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 21/04/01 |  2  | Updated.  Additional testing functions added to test
 *     |          |     | new classes and functions.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  3  | Updated.  Additional testing functions added to test
 *     |          |     | new classes and functions.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  5  | Updated.  Additional testing functions added to test
 *     |          |     | new classes and functions.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 5.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <string>
#include <strstream>
#include <climits>
#include <cfloat>
#include <cerrno>
#include "Err_mngr.h"
#include "InputFil.h"
#include "global.h"
#include "Resource.h"
#include "Assignmt.h"
#include "Srchman.h"
#include "DataLimt.h"
#include "Srchman.h"
using namespace std;
/*
 * Functions used for testing classes and functions in
 * the Search and Rescue Program.
 */
void InputFile_tester(void);
void Input_tester(void);
void Resources_autotester(void);
void Resources_intertester(void);
void Tokenise_tester(void);
void StripWhite_tester(void);
void ResizeString_tester(void);
void Assignment_tester(void);
void FloatCmp_tester(void);
void ChkType_tester(void);
void Output_tester(void);
void DataLimt_tester(void);
void ConToStr_tester(void);
void Srchman_tester(void);
// Should use ifdef here... only define this if we're runinng in test mode
// bool testmode = false; /* Is program running in verbose test mode? */

/******************************************************************************
 * main()
 *
 * Testing menu which allows the user to select which
 * classes and functions they wish to test.
 *
 * Author : Gareth Thompson
 */
// renamed to stop linker errors in Visual C++
//(rather than removing it from the build and then adding again later)
int TestMain(void)
{
	int choice;
	const int maxchoice = 14;
	do
	{
		cout << "\n";
		cout << "******************\n";
		cout << "** Testing Menu **\n";
		cout << "******************\n";
		cout << "1. InputFile class\n";
		cout << "2. Input functions\n";
		cout << "3. Resources class (automated tests)\n";
		cout << "4. Resources class (interactive tests)\n";
		cout << "5. Tokenise function\n";
		cout << "6. StripWhite functions\n";
		cout << "7. string resizing function\n";
		cout << "8. Assignment class\n";
		cout << "9. Floating Point comparison functions\n";
		cout << "10. ChkType function\n";
		cout << "11. Output functions\n";
		cout << "12. DataLimt class\n";
		cout << "13. ConToStr function\n";
		cout << "14. SearchManager functions\n";
		cout << "0. Quit" << endl;
		do
		{
			cout << "\nEnter the number of the thing you wish to test: ";
			cin >> choice;
			if (choice < 0 || choice > maxchoice)
			{
				cout << "Invalid choice!" << endl;
			}
		} while (choice < 0 || choice > maxchoice);

		if (choice == 1)
		{
			InputFile_tester();
		}
		else if (choice == 2)
		{
			Input_tester();
		}
		else if (choice == 3)
		{
			Resources_autotester();
		}
		else if (choice == 4)
		{
			Resources_intertester();
		}
		else if (choice == 5)
		{
			Tokenise_tester();
		}
		else if (choice == 6)
		{
			StripWhite_tester();
		}
		else if (choice == 7)
		{
			ResizeString_tester();
		}
		else if (choice == 8)
		{
			Assignment_tester();
		}
		else if (choice == 9)
		{
			FloatCmp_tester();
		}
		else if (choice == 10)
		{
			ChkType_tester();
		}
		else if (choice == 11)
		{
			Output_tester();
		}
		else if (choice == 12)
		{
			DataLimt_tester();
		}
		else if (choice == 13)
		{
			ConToStr_tester();
		}
		else if (choice == 14)
		{
			Srchman_tester();
		}
	} while (choice != 0);
	return 0;
}

/******************************************************************************
 * InputFile_tester()
 *
 * Function for testing class InputFile.
 *
 * Author : Gareth Thompson
 */
void InputFile_tester(void)
{
	if (testmode) cout << "entering InputFile_tester()\n";
	InputFile in1, in2, in3, in4, in5, in6, in7;
	string line;
	int num;
	cout << "Can I open a file that does not exist?...";
	if(in1.open("nonexistentfile.dat"))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	in1.close();
	cout << "Can I open a file that does exist?...";
	if (in2.open("test_if1.dat"))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Can I open a second file when one is already open?...";
	if (in2.open("test_if2.dat"))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	in2.close();
	cout << "Can I open one file, close it and then open another?...";
	in3.open("test_if1.dat");
	in3.close();
	if (in3.open("test_if2.dat"))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	in3.close();
	in4.open("test_if2.dat");
	cout << "Can I obtain a record from a file?...";
	if (in4.getRecord(line))
	{
		cout << "\nYes - record is: " << line << "\n" << "SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	in5.open("test_if1.dat");
	cout << "Can I correctly obtain records from the file and count lines?..." << endl;
	cout << "First record should be:\nFirst record | on line 1\n";
	in5.getRecord(line);
	num = in5.lastRecLine();
	cout << "First record is:\n" << line << " | on line " << num << endl;
	cout << "Second record should be:\nSecond record | on line 2\n";
	in5.getRecord(line);
	num = in5.lastRecLine();
	cout << "Second record is:\n" << line << " | on line " << num << endl;
	cout << "Third record should be:\n	   3rd record | on line 3\n";
	in5.getRecord(line);
	num = in5.lastRecLine();
	cout << "Third record is:\n" << line << " | on line " << num << endl;
	cout << "Fourth record should be:\n1, 5850, 8450, 1.0, 85, 4, 30, 3 | on line 4\n";
	in5.getRecord(line);
	num = in5.lastRecLine();
	cout << "Fourth record is:\n" << line << " | on line " << num << endl;
	cout << "Fifth record should be:\nFifth record | on line 12\n";
	in5.getRecord(line);
	num = in5.lastRecLine();
	cout << "Fifth record is:\n" << line << " | on line " << num << endl;
	cout << "Can I obtain records from the file when there are no more?...";
	if (in5.getRecord(line))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	cout << "Can I obtain a record when a file is not open?...";
	if (in6.getRecord(line))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}
	/* Test private functions */
	in7.test();
}

/******************************************************************************
 * Input_tester()
 *
 * Function for testing global input functions.
 *
 * Author : Gareth Thompson
 */
void Input_tester(void)
{
	if (testmode) cout << "entering Input_tester()\n";
	int choice;
	const int maxchoice = 5;
	do
	{
		cout << "\n";
		cout << "**********************************\n";
		cout << "** Input Functions Testing Menu **\n";
		cout << "**********************************\n";
		cout << "1. GetInputString\n";
		cout << "2. GetInputInteger\n";
		cout << "3. GetValidInputInteger\n";
		cout << "4. GetInputFloat\n";
		cout << "5. GetValidInputFloat\n";
		cout << "0. Quit" << endl;
		do
		{
			cout << "\nEnter the number of the thing you wish to test: ";
			cin >> choice;
			if (choice < 0 || choice > maxchoice)
			{
				cout << "Invalid choice!" << endl;
			}
		} while (choice < 0 || choice > maxchoice);

		if (choice == 1)
		{
			string inString;
			cout << "Enter a string:\n";
			inString = GetInputString(cin);
			cout << "The string with leading and trailing whitespace removed is:\n";
			cout << "(The string is placed between |)\n";
			cout << "|" << inString << "|" << endl;
		}
		else if (choice == 2)
		{
			int inInt;
			cout << "Enter an integer:\n";
			bool success = GetInputInteger(cin, inInt);
			if (success)
			{
				cout << "You have entered a valid integer: " << inInt << "\n";
			}
			else
			{
				cout << "You have entered an invalid integer\n";
			}
		}
		else if (choice == 3)
		{
			int min, max;
			string prompt, errorMsg;
			ostrstream os1, os2, os3, os4;
			cout << "MIN: ";
			cin >> min;
			cout << "MAX: ";
			cin >> max;
			prompt = "Enter an integer from ";
			os1 << min << '\0';
			prompt += os1.str();
			prompt += " to ";
			os2 << max << '\0';
			prompt += os2.str();
			prompt += ": ";
			errorMsg = "Invalid entry!";
			int i = GetValidInputInteger(prompt, errorMsg, min, max);
			cout << "Entered integer is: " << i << "\n";
			min = INT_MIN;
			max = INT_MAX;
			prompt = "Enter an integer from ";
			os3 << min << '\0';
			prompt += os3.str();
			prompt += " to ";
			os4 << max << '\0';
			prompt += os4.str();
			prompt += ": ";
			errorMsg = "Invalid entry!";
			i = GetValidInputInteger(prompt, errorMsg, min, max);
			cout << "Entered integer is: " << i << "\n";
		}
		else if (choice == 4)
		{
			double inFloat;
			cout << "Enter a floating-point number:\n";
			bool success = GetInputFloat(cin, inFloat);
			if (success)
			{
				cout << "You have entered a valid floating-point number: " << inFloat << "\n";
			}
			else
			{
				cout << "You have entered an invalid floating-point number\n";
			}
		}
		else if (choice == 5)
		{
			double min, max;
			string prompt, errorMsg;
			ostrstream os1, os2, os3, os4;
			cout << "MIN: ";
			cin >> min;
			cout << "MAX: ";
			cin >> max;
			prompt = "Enter a floating point number from ";
			os1 << min << "\0";
			prompt += os1.str();
			prompt += " to ";
			os2 << max << "\0";
			prompt += os2.str();
			prompt += ": ";
			errorMsg = "Invalid entry!";
			double d = GetValidInputFloat(prompt, errorMsg, min, max);
			cout << "Entered float is: " << d << "\n";
			min = FLOATMINVAL;
			max = FLOATMAXVAL;
			prompt = "Enter an integer from ";
			os3 << min << "\0";
			prompt += os3.str();
			prompt += " to ";
			os4 << max << "\0";
			prompt += os4.str();
			prompt += ": ";
			errorMsg = "Invalid entry!";
			d = GetValidInputFloat(prompt, errorMsg, min, max);
			cout << "Entered float is: " << d << "\n";
		}
	} while (choice != 0);

}
/******************************************************************************
 * Resources_autotester()
 *
 * Function for testing the parts of class Resources that
 * run automatically (without interacting with users).
 * Hardcoded test cases are run on these functions.
 *
 * Author : Gareth Thompson
 */
void Resources_autotester(void)
{
	if (testmode) cout << "entering Resources_autotester()\n";
	cout << "\n\n";
	/* Testing getResourceNumList() */
	cout << "Does resourceNumList correctly return a list of Resource Numbers in ascending order?...";
	Resources resources11;
	resources11.loadSRUs("test_rs9.dat");
	vector<int> list = resources11.getResourceNumList();
	if (list.size() == 4 && list[0] == 1 && list[1] == 2 &&
	    list[2] == 9 && list[3] == 50)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	/* Testing Resources::addAssignment() and Resources::getAssignments()*/
	cout << "Can I add and get Assignments correctly?...";
	Resources resources1;
	resources1.loadSRUs("test_rsA.dat");
	resources1.addAssignment(1, Assignment(50,70.5));
	resources1.addAssignment(1, Assignment(80,40.2));
	resources1.addAssignment(1, Assignment(500,1000.1));
	vector<Assignment> assignments1 = resources1.getAssignments(1);
	if (testmode) PrintAssignmentVector(assignments1);
	if (assignments1.size() == 3 &&
	    assignments1[0].getAreaNum() == 50 &&
	    FloatEqual(assignments1[0].getResourceHours(), 70.5) &&
	    assignments1[1].getAreaNum() == 80 &&
	    FloatEqual(assignments1[1].getResourceHours(), 40.2) &&
	    assignments1[2].getAreaNum() == 500 &&
	    FloatEqual(assignments1[2].getResourceHours(), 1000.1) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does addAssignment() correctly add an assignment if sufficient resource hours are available?...";
	resources1.loadSRUs("test_rsB.dat");
	resources1.addAssignment(2, Assignment(1,4.5));
	resources1.addAssignment(2, Assignment(2,3.5));
	/*
	 * Select a number of resource-hours that exceeds that available
	 * by less than the floating-point precision (0.0001)
	 */
	bool success1 = resources1.addAssignment(2, Assignment(3, 2.0 + 0.5 * 0.0001));
	vector<Assignment> assignments2 = resources1.getAssignments(2);
	if (testmode) PrintAssignmentVector(assignments2);
	if (success1 == true &&
	    assignments2.size() == 3 &&
	    assignments2[0].getAreaNum() == 1 &&
	    FloatEqual(assignments2[0].getResourceHours(), 4.5) &&
	    assignments2[1].getAreaNum() == 2 &&
	    FloatEqual(assignments2[1].getResourceHours(), 3.5) &&
	    assignments2[2].getAreaNum() == 3 &&
	    FloatEqual(assignments2[2].getResourceHours(), 2.0) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does addAssignment() add an assignment if insufficient resource hours are available?...";
	resources1.loadSRUs("test_rsC.dat");
	resources1.addAssignment(3, Assignment(1,4.5));
	resources1.addAssignment(3, Assignment(2,3.5));
	/*
	 * Select a number of resource-hours that exceeds that available
	 * by more than the floating-point precision (0.0001)
	 */
	bool success2 = resources1.addAssignment(3, Assignment(3, 2.0 + 1.5 * 0.0001));
	vector<Assignment> assignments3 = resources1.getAssignments(3);
	if (testmode) PrintAssignmentVector(assignments3);
	if (success2 == false &&
	    assignments3.size() == 2 &&
	    assignments3[0].getAreaNum() == 1 &&
	    FloatEqual(assignments3[0].getResourceHours(), 4.5) &&
	    assignments3[1].getAreaNum() == 2 &&
	    FloatEqual(assignments3[1].getResourceHours(), 3.5) )
	{
		cout << "No.  SUCCESS." << endl;
	}
	else
	{
		cout << "Yes.  FAILURE." << endl;
	}

	cout << "Does addAssignment() return false if the specified SRU does not exist?...";
	if (resources1.addAssignment(4, Assignment(1, 3)))
	{
		cout << "No.  Failure." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	cout << "Does getAssignments() return successfully (with undefined value) if the specified SRU does not exist?...\n";
	Resources resources14;
	resources14.getAssignments(1);
	cout << "Yes.  SUCCESS" << endl;
	cout << "Does addAssignment() alter the data stored when adding an Assignment with Resource Hours equal to 0?...";
	resources1.loadSRUs("test_rsD.dat");
	resources1.addAssignment(4, Assignment(1, 4.5));
	resources1.addAssignment(4, Assignment(2, 3.5));
	/*
	 * Select a number of resource-hours that exceeds 0
	 * by less than the floating-point precision (0.0001)
	 */
	bool success5 = resources1.addAssignment(4, Assignment(3, 0.5 * 0.0001));
	vector<Assignment> assignments11 = resources1.getAssignments(4);
	if (testmode) PrintAssignmentVector(assignments11);
	if (success5 == true &&
	    assignments11.size() == 2 &&
	    assignments11[0].getAreaNum() == 1 &&
	    FloatEqual(assignments11[0].getResourceHours(), 4.5) &&
	    assignments11[1].getAreaNum() == 2 &&
	    FloatEqual(assignments11[1].getResourceHours(), 3.5) )
	{
		cout << "No.  SUCCESS." << endl;
	}
	else
	{
		cout << "Yes.  FAILURE." << endl;
	}
	cout << "Does addAssignment() add the Resource Hours of two Assignments with equal Area Numbers?...";
	resources1.loadSRUs("test_rsE.dat");
	resources1.addAssignment(4, Assignment(1, 4.5));
	resources1.addAssignment(4, Assignment(2, 3.5));
	bool success6 = resources1.addAssignment(4, Assignment(2, 1.5));
	vector<Assignment> assignments12 = resources1.getAssignments(4);
	if (testmode) PrintAssignmentVector(assignments12);
	if (success6 == true &&
	    assignments12.size() == 2 &&
	    assignments12[0].getAreaNum() == 1 &&
	    FloatEqual(assignments12[0].getResourceHours(), 4.5) &&
	    assignments12[1].getAreaNum() == 2 &&
	    FloatEqual(assignments12[1].getResourceHours(), 5.0) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does addAssignment fail to add an Assignment with negative Resource-hours?...";
	resources1.loadSRUs("test_rsP.dat");
	resources1.addAssignment(50, Assignment(1, 5));
	bool success10 = resources1.addAssignment(50, Assignment(5, -5));
	vector<Assignment> assignments15 = resources1.getAssignments(50);
	if (testmode) PrintAssignmentVector(assignments15);
	if (success10 == false &&
	    assignments15.size() == 1 &&
	    assignments15[0].getAreaNum() == 1 &&
	    FloatEqual(assignments15[0].getResourceHours(), 5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing deleteAssignment() */
	cout << "Does deleteAssignment() delete an assignment with a specified area number?...";
	resources1.loadSRUs("test_rsF.dat");
	resources1.addAssignment(6, Assignment(1, 4.5));
	resources1.addAssignment(6, Assignment(2, 3.5));
	bool success7 = resources1.deleteAssignment(6, 2);
	vector<Assignment> assignments13 = resources1.getAssignments(6);
	if (testmode) PrintAssignmentVector(assignments13);
	if (success7 == true &&
	    assignments13.size() == 1 &&
	    assignments13[0].getAreaNum() == 1 &&
	    FloatEqual(assignments13[0].getResourceHours(), 4.5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does deleteAssignment fail to delete an assignment if there is none with the specified area number?...";
	bool success8 = resources1.deleteAssignment(6, 5);
	vector<Assignment> assignments14 = resources1.getAssignments(6);
	if (testmode) PrintAssignmentVector(assignments14);
	if (success8 == false &&
	    assignments14.size() == 1 &&
	    assignments14[0].getAreaNum() == 1 &&
	    FloatEqual(assignments14[0].getResourceHours(), 4.5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does deleteAssignment return false if there is no SRU with the specified Resource Number?...";
	Resources resources20;
	bool success9 = resources20.deleteAssignment(1, 1);
	if (success9 == false)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	/* Testing deleteAssignments() */
	cout << "Can I delete Assignments correctly?...";
	Resources resources6;
	resources6.loadSRUs("test_rsG.dat");
	resources6.addAssignment(1, Assignment(1, 10.5));
	resources6.addAssignment(1, Assignment(3, 10.3));
	resources6.addAssignment(1, Assignment(2, 20.2));
	vector<Assignment> assignments5 = resources6.getAssignments(1);
	bool success4 = resources6.deleteAssignments(1);
	vector<Assignment> assignments6 = resources6.getAssignments(1);
	if (success4 == true &&
	    assignments5.size() == 3 &&
	    assignments5[0].getAreaNum() == 1 &&
	    FloatEqual(assignments5[0].getResourceHours(), 10.5) &&
	    assignments5[1].getAreaNum() == 3 &&
	    FloatEqual(assignments5[1].getResourceHours(), 10.3) &&
	    assignments5[2].getAreaNum() == 2 &&
	    FloatEqual(assignments5[2].getResourceHours(), 20.2) &&
	    assignments6.size() == 0)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does deleteAssignments() return false if the specified SRU does not exist?...";
	vector<Assignment> assignments7;
	if (resources6.deleteAssignments(2))
	{
		cout << "No.  Failure." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	/* Testing deleteAllAssignments() */
	cout << "Does deleteAllAssignments() delete the assignments for all SRUs?...";
	Resources resources7;
	resources7.loadSRUs("test_rsH.dat");
	resources7.addAssignment(1, Assignment(1, 10.1));
	resources7.addAssignment(1, Assignment(3, 10.5));
	resources7.addAssignment(1, Assignment(2, 20.4));
	resources7.addAssignment(1000, Assignment(1000, 100000.5));
	resources7.addAssignment(1000, Assignment(2000, 200000.5));
	resources7.deleteAllAssignments();
	vector<Assignment> assignments8 =  resources7.getAssignments(1);
	vector<Assignment> assignments9 =  resources7.getAssignments(40);
	vector<Assignment> assignments10 =  resources7.getAssignments(1000);
	if (assignments8.size() == 0 && assignments9.size() == 0 &&
	    assignments10.size() == 0)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing getHoursRemaining() */
	cout << "Does getHoursRemaining() correctly give the number of resource hours still to be allocated for an SRU?...";
	Resources resources8;
	resources8.loadSRUs("test_rsI.dat");
	resources8.addAssignment(1, Assignment(50, 10.1));
	resources8.addAssignment(1, Assignment(80, 35.0));
	resources8.addAssignment(1, Assignment(500, 11.6));
	if (FloatEqual(resources8.getHoursRemaining(1), 88.3))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getHoursRemaining() return successfully (with undefined value) if the specified SRU does not exist?...\n";
	resources8.getHoursRemaining(2);
	cout << "Yes.  SUCCESS" << endl;

	/* Testing getESW() */
	cout << "Does getESW() correctly give the ESW for an SRU?...";
	Resources resources12;
	resources12.loadSRUs("test_rsN.dat");
	if (FloatEqual(resources12.getESW(1), 10.0))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does getESW() return successfully (with undefined value) if the specified SRU does not exist?...\n";
	resources12.getESW(2);
	cout << "Yes.  SUCCESS" << endl;

	/* Testing getSpeed() */
	cout << "Does getSpeed() correctly give the Speed for an SRU?...";
	Resources resources13;
	resources13.loadSRUs("test_rsN.dat");
	if (FloatEqual(resources13.getSpeed(1), 20.0))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does getSpeed() return successfully (with undefined value) if the specified SRU does not exist?...\n";
	resources13.getESW(2);
	cout << "Yes.  SUCCESS" << endl;

	/* Testing getCorrectionFactor() */
	cout << "Does getCorrectionFactor() correctly give a specified correction factor for an SRU?...";
	Resources resources19;
	resources19.loadSRUs("test_rs7.dat");
	if (FloatEqual(resources19.getCorrectionFactor(5, 1, 2), 2.5))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getCorrectionFactor return correction factor 1.0 if none is specified?...";
	if (FloatEqual(resources19.getCorrectionFactor(5, 50, 1), 1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getCorrectionFactor return successfully (with undefined return value) if the specified SRU does not exist, or the terrain or vegetation values are invalid?...";
	resources19.getCorrectionFactor(1, 1, 1);
	resources19.getCorrectionFactor(0, 1, 1);
	resources19.getCorrectionFactor(101, 1, 1);
	resources19.getCorrectionFactor(1, 0, 1);
	resources19.getCorrectionFactor(1, 3, 1);
	cout << "Yes.  SUCCESS." << endl;

	/* Testing getEffectiveSweepRate() */
	cout << "Does getEffectiveSweepRate() correctly give the Effective Sweep Rate for an SRU when no terrain or vegetation values are specified?...";
	Resources resources17;
	resources17.loadSRUs("test_rs7.dat");
	if (FloatEqual(resources17.getEffectiveSweepRate(5), 6.25625))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getEffectiveSweepRate() correctly give the Effective Sweep Rate for the SRU when invalid terrain or vegetation values are specified?...";
	if (FloatEqual(resources17.getEffectiveSweepRate(5, 0, 1), 6.25625) &&
	    FloatEqual(resources17.getEffectiveSweepRate(5, 101, 1), 6.25625) &&
	    FloatEqual(resources17.getEffectiveSweepRate(5, 1, 0), 6.25625) &&
	    FloatEqual(resources17.getEffectiveSweepRate(5, 1, 4), 6.25625))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getEffectiveSweepRate() correctly give the EffectiveSweepRate when valid terrain and vegetation values are given and a correction factor is defined?...";
	if (FloatEqual(resources17.getEffectiveSweepRate(5,2,2), 62.5625))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getEffectiveSweepRate give the default Effective Sweep Rate if terrain and vegetation values are specified, but there is no correction factor for that combination?...";
	if (FloatEqual(resources17.getEffectiveSweepRate(5,50,1), 6.25625))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does getEffectiveSweepRate() return successfully (with undefined value) if the specified SRU does not exist?...\n";
	resources17.getEffectiveSweepRate(2);
	cout << "Yes.  SUCCESS" << endl;

	/* Testing hoursRemaining() */
	cout << "Does hoursRemaining() return true if the specified SRU has Resource-hours remaining to be assigned for searching?...";
	Resources resources15;
	resources15.loadSRUs("test_rsJ.dat");
	resources15.addAssignment(1, Assignment(1, 30.0));
	resources15.addAssignment(1, Assignment(2, 10.0));
	resources15.addAssignment(1, Assignment(3, 10.0 - 1.5 * 0.0001));
	if (resources15.hoursRemaining(1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does hoursRemaining() return false if the specified SRU does not have Resource-hours remaining to be assigned for searching?...";
	resources15.addAssignment(2, Assignment(1, 30.0));
	resources15.addAssignment(2, Assignment(2, 10.0));
	resources15.addAssignment(2, Assignment(3, 10.0 - 0.5 * 0.0001));
	if (resources15.hoursRemaining(2))
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	cout << "Does hoursRemaining() return false if an SRU with the specified Resource Number does not exist?...";
	if (resources15.hoursRemaining(3))
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	/* Testing anyHoursRemaining() */
	cout << "Does anyHoursRemaining() return true if there are SRUs with Resource-hours left to be assigned?...";
	Resources resources9;
	resources9.loadSRUs("test_rsK.dat");
	resources9.addAssignment(1, Assignment(1, 20.0));
	resources9.addAssignment(1, Assignment(3, 20.0));
	resources9.addAssignment(1, Assignment(2, 10.0));
	resources9.addAssignment(40, Assignment(2, 9.8));
	resources9.addAssignment(1000, Assignment(1000, 100000.0));
	resources9.addAssignment(1000, Assignment(2000, 200000.0));
	if (resources9.anyHoursRemaining())
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does anyHoursRemaining() return false if there are no SRUs with Resource-hours left to be assigned?...";
	resources9.addAssignment(40, Assignment(4, 0.2));
	if (resources9.anyHoursRemaining())
	{
		cout << "No.  FAILURE" << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	/* Testing viewAssignments() */
	cout << "Does viewAssignments correctly display assignments for a given SRU?...";
	cout << "Output should be:\n\n";
	cout << "AREA NUMBER:    1      RESOURCE HOURS:     10.50\n";
	cout << "AREA NUMBER:    5      RESOURCE HOURS:    150.75\n";
	cout << "AREA NUMBER: 1000      RESOURCE HOURS: 450000.00\n";
	cout << "Output is:\n\n";
	Resources resources10;
	resources10.loadSRUs("test_rsL.dat");
	resources10.addAssignment(1, Assignment(1, 10.50));
	resources10.addAssignment(1, Assignment(1000, 450000.00));
	resources10.addAssignment(1, Assignment(5, 150.75));
	resources10.viewAssignments(1);
	cout << "Does view Assignments correctly display an error message if the specified SRU does not exist?...\n";
	cout << "An error message should be printed because SRU 2 does not exist.\n";
	cerr << "An error message should be printed because SRU 2 does not exist.\n";
	resources10.viewAssignments(2);

	/* Test viewAllAssignments() */
	cout << "Does viewAllAssignments correctly display assignments data?";
	cout << "Output should be:\n\n";
	cout << " Res     Hours       Hours     Area          Hours\n";
	cout << " Num     Avail        Used      Num       Assigned\n";
	cout << "==================================================\n";
	cout << "   1        50       40.50        1          10.10\n";
	cout << "                                  2          20.05\n";
	cout << "                                  3          10.35\n";
	cout << "==================================================\n";
	cout << "  40         0        0.00        -            -\n";
	cout << "==================================================\n";
	cout << "1000    400000   300000.00     1000      100000.00\n";
	cout << "                               2000      200000.00\n";
	cout << "==================================================\n";
	cout << "Output is:\n\n";
	Resources resources5;
	resources5.loadSRUs("test_rsM.dat");
	resources5.addAssignment(1000, Assignment(1000, 100000.00));
	resources5.addAssignment(1000, Assignment(2000, 200000.00));
	resources5.addAssignment(1, Assignment(3, 10.35));
	resources5.addAssignment(1, Assignment(1, 10.1));
	resources5.addAssignment(1, Assignment(2, 20.05));
	resources5.viewAllAssignments();

	/* Test outputAllAssignments() */
	cout << "Does outputAllAssignments correctly display assignments data?...";
	cout << "Output should be:\n\n";
	cout << "1, 1, 10.10\n";
	cout << "1, 2, 20.05\n";
	cout << "1, 3, 10.35\n";
	cout << "1000, 1000, 100000.00\n";
	cout << "1000, 2000, 200000.00\n";
	cout << "Output is:\n\n";
	Resources resources16;
	resources16.loadSRUs("test_rsM.dat");
	resources16.addAssignment(1000, Assignment(1000, 100000.00));
	resources16.addAssignment(1000, Assignment(2000, 200000.00));
	resources16.addAssignment(1, Assignment(3, 10.35));
	resources16.addAssignment(1, Assignment(1, 10.1));
	resources16.addAssignment(1, Assignment(2, 20.05));
	resources16.outputAllAssignments(cout);
	cout << "Does outputAllAssignments correctly output assignments data to a file?...";
	ofstream out("tester_out.txt");
	resources16.outputAllAssignments(out);
	cout << "This data should also be output to \"tester_out.txt\"";

	/* Test loadSRUs */
	cout << "\nTesting loadSRUs...\n\n";
	Resources resources2;
	cout << "Is data correctly loaded from a data file?...\n";
	resources2.loadSRUs("test_rs1.dat");
	cout << "\nSRU1 should have details: \n";
	cout << "Resource Type:  Hasty\n";
	cout << "POD:  50.55%\n";
	cout << "ESW:  10.10m\n";
	cout << "Speed:  6.50km/h\n";
	cout << "Resource-hours Available:  3\n";
	cout << "Details of SRU1 are: \n";
	resources2.viewSRU(1);
	cout << "\nSRU2 should have details: \n";
	cout << "Resource Type:  Efficient\n";
	cout << "POD:  70.52%\n";
	cout << "ESW:  20.90m\n";
	cout << "Speed:  4.20km/h\n";
	cout << "Resource-hours Available:  6\n";
	cout << "Details of SRU2 are: \n";
	resources2.viewSRU(2);
	cout << "\nSRU3 should have details: \n";
	cout << "Resource Type:  Thorough\n";
	cout << "POD:  80.80%\n";
	cout << "ESW:  40.00m\n";
	cout << "Speed:  2.00km/h\n";
	cout << "Resource-Hours Available:  8\n";
	cout << "Details of SRU3 are: \n";
	resources2.viewSRU(3);
	cout << "\nSRU4 should have details: \n";
	cout << "Resource Type:  DumbGrid\n";
	cout << "POD:  90.00%\n";
	cout << "ESW:  60.50m\n";
	cout << "Speed:  1.10km/h\n";
	cout << "Resource-Hours Available:  20\n";
	cout << "Details of SRU4 are: \n";
	resources2.viewSRU(4);
	cout << "\nSRU5 should not exist (no details) \n";
	cout << "Details of SRU5 are: \n";
	resources2.viewSRU(5);
	cout << "Is further data correctly loaded from a data file?...\n";
	resources2.loadSRUs("test_rs2.dat");
	cout << "\nSRU1 should have details: \n";
	cout << "Resource Type:  Hasty\n";
	cout << "POD:  50.55%\n";
	cout << "ESW:  10.10m\n";
	cout << "Speed:  6.50km/h\n";
	cout << "Resource-Hours Available:  3\n";
	cout << "Details of SRU1 are: \n";
	resources2.viewSRU(1);
	cout << "\nSRU2 should have details: \n";
	cout << "Resource Type:  Efficient\n";
	cout << "POD:  70.52%\n";
	cout << "ESW:  20.90m\n";
	cout << "Speed:  4.20km/h\n";
	cout << "Resource-Hours Available:  6\n";
	cout << "Details of SRU2 are: \n";
	resources2.viewSRU(2);
	cout << "\nSRU3 should have details: \n";
	cout << "Resource Type:  Thorough\n";
	cout << "POD:  80.80%\n";
	cout << "ESW:  40.00m\n";
	cout << "Speed:  2.00km/h\n";
	cout << "Resource-Hours Available:  8\n";
	cout << "Details of SRU3 are: \n";
	resources2.viewSRU(3);
	cout << "\nSRU4 should have details: \n";
	cout << "Resource Type:  DumbGrid\n";
	cout << "POD:  90.00%\n";
	cout << "ESW:  60.50m\n";
	cout << "Speed:  1.10km/h\n";
	cout << "Resource-Hours Available:  20\n";
	cout << "Details of SRU4 are: \n";
	resources2.viewSRU(4);
	cout << "\nSRU5 should have details: \n";
	cout << "Resource Type:  Excellent\n";
	cout << "POD:  80.00%\n";
	cout << "ESW:  100.10m\n";
	cout << "Speed:  62.50km/h\n";
	cout << "Resource-Hours Available:  2\n";
	cout << "Details of SRU5 are: \n";
	resources2.viewSRU(5);
	cout << "\nSRU6 should have details: \n";
	cout << "Resource Type:  Hopeless\n";
	cout << "POD:  20.00%\n";
	cout << "ESW:  1.50m\n";
	cout << "Speed:  2.00km/h\n";
	cout << "Resource-Hours Available:  20\n";
	cout << "Details of SRU6 are: \n";
	resources2.viewSRU(6);
	cout << "\nSRU7 should not exist (no details) \n";
	cout << "Details of SRU7 are: \n";
	resources2.viewSRU(7);
	cout << "Are new Resources ignored if Resources with those Resource numbers already exist?...\n";
	cout << "Errors should occur because Resources 1 and 4 already exist\n";
	resources2.loadSRUs("test_rs3.dat");
	cout << "\nSRU1 should have details: \n";
	cout << "Resource Type:  Hasty\n";
	cout << "POD:  50.55%\n";
	cout << "ESW:  10.10m\n";
	cout << "Speed:  6.50km/h\n";
	cout << "Resource-Hours Available:  3\n";
	cout << "Details of SRU1 are: \n";
	resources2.viewSRU(1);
	cout << "\nSRU2 should have details: \n";
	cout << "Resource Type:  Efficient\n";
	cout << "POD:  70.52%\n";
	cout << "ESW:  20.90m\n";
	cout << "Speed:  4.20km/h\n";
	cout << "Resource-Hours Available:  6\n";
	cout << "Details of SRU2 are: \n";
	resources2.viewSRU(2);
	cout << "\nSRU3 should have details: \n";
	cout << "Resource Type:  Thorough\n";
	cout << "POD:  80.80%\n";
	cout << "ESW:  40.00m\n";
	cout << "Speed:  2.00km/h\n";
	cout << "Resource-Hours Available:  8\n";
	cout << "Details of SRU3 are: \n";
	resources2.viewSRU(3);
	cout << "\nSRU4 should have details: \n";
	cout << "Resource Type:  DumbGrid\n";
	cout << "POD:  90.00%\n";
	cout << "ESW:  60.50m\n";
	cout << "Speed:  1.10km/h\n";
	cout << "Resource-Hours Available:  20\n";
	cout << "Details of SRU4 are: \n";
	resources2.viewSRU(4);
	cout << "\nSRU5 should have details: \n";
	cout << "Resource Type:  Excellent\n";
	cout << "POD:  80.00%\n";
	cout << "ESW:  100.10m\n";
	cout << "Speed:  62.50km/h\n";
	cout << "Resource-Hours Available:  2\n";
	cout << "Details of SRU5 are: \n";
	resources2.viewSRU(5);
	cout << "\nSRU6 should have details: \n";
	cout << "Resource Type:  Hopeless\n";
	cout << "POD:  20.00%\n";
	cout << "ESW:  1.50m\n";
	cout << "Speed:  2.00km/h\n";
	cout << "Resource-Hours Available:  20\n";
	cout << "Details of SRU6 are: \n";
	resources2.viewSRU(6);
	cout << "\nSRU7 should have details: \n";
	cout << "Resource Type:  Average\n";
	cout << "POD:  50.00%\n";
	cout << "ESW:  3.00m\n";
	cout << "Speed:  2.50km/h\n";
	cout << "Resource-Hours Available:  10\n";
	cout << "Details of SRU7 are: \n";
	resources2.viewSRU(7);
	cout << "\nSRU8 should not exist (no details) \n";
	cout << "Details of SRU8 are: \n";
	resources2.viewSRU(8);
	cout << "Are Records in file ignored if in incorrect format?...\n";
	cout << "Errors should occur because data is incorrectly read at lines 2, 4 and 5 and 7-16\n";
	Resources resources3;
	resources3.loadSRUs("test_rs4.dat");
	cout << "\nSRU1 should have details: \n";
	cout << "Resource Type:  Efficient\n";
	cout << "POD:  50.00%\n";
	cout << "ESW:  30.50m\n";
	cout << "Speed:  10.50km/h\n";
	cout << "Resource-Hours Available:  10\n";
	cout << "Details of SRU1 are: \n";
	resources3.viewSRU(1);
	cout << "\nSRU2 should not exist (no details) \n";
	cout << "Details of SRU2 are: \n";
	resources3.viewSRU(2);
	cout << "\nSRU3 should have details: \n";
	cout << "Resource Type:  DumbGrid\n";
	cout << "POD:  30.00%\n";
	cout << "ESW:  10.50m\n";
	cout << "Speed:  11.50km/h\n";
	cout << "Resource-Hours Available:  5\n";
	cout << "Details of SRU3 are: \n";
	resources3.viewSRU(3);
	cout << "\nSRU4 should not exist (no details) \n";
	cout << "Details of SRU4 are: \n";
	resources3.viewSRU(4);
	cout << "\nSRU5 should not exist (no details) \n";
	cout << "Details of SRU5 are: \n";
	resources3.viewSRU(5);
	cout << "\nSRU6 should have details: \n";
	cout << "Resource Type:  Average\n";
	cout << "POD:  50.00%\n";
	cout << "ESW:  3.00m\n";
	cout << "Speed:  2.50km/h\n";
	cout << "Resource-Hours Available:  10\n";
	cout << "Details of SRU6 are: \n";
	resources3.viewSRU(6);
	/* Test outputAllSRUs() */
	cout << "Does outputAllSRUs() work correctly?...";
	cout << "Output should be: \n";
	cout << "1, NumberOne, 1.00, 1.10, 1.10, 1, ( (1/1/1.000) (50/2/0.500) )\n";
	cout << "4, NumberFour, 4.00, 4.40, 4.40, 4, ()\n";
	cout << "7, Average, 50.00, 3.00, 2.50, 10, ( (1/1/4.000) (1/3/3.600) (4/2/9.000) (5/1/0.050) )\n";
	cout << "Output is:\n";
	Resources resources18;
	resources18.loadSRUs("test_rs8.dat");
	resources18.outputAllSRUs(cout);
	/* test private functions */
	Resources resources4;
	resources4.test();
}
/******************************************************************************
 * Resources_intertester()
 *
 * Function for testing the parts of class Resources that
 * interact with users.
 * A menu allows users to use these classes in order to
 * manually test them.
 *
 * Author : Gareth Thompson
 */
void Resources_intertester(void)
{
	if (testmode) cout << "entering Resources_intertester()\n";
	Resources resources1;
	int choice;
	const int maxchoice = 1;
	do
	{
		cout << "\n";
		cout << "****************************\n";
		cout << "** Resources Testing Menu **\n";
		cout << "****************************\n";
		cout << "1. Test Resources menu() function\n";
		cout << "0. Quit" << endl;
		do
		{
			cout << "\nEnter choice: ";
			cin >> choice;
			if (choice < 0 || choice > maxchoice)
			{
				cout << "Invalid choice!" << endl;
			}
		} while (choice < 0 || choice > maxchoice);

		if (choice == 1)
		{
			resources1.menu();
		}
	} while (choice != 0);
}

/******************************************************************************
 * Tokenise_tester()
 *
 * Function for testing global function Tokenise().
 *
 * Author : Gareth Thompson
 */
void Tokenise_tester(void)
{
	if (testmode) cout << "entering Tokenise_tester()\n";
	cout << "Does Tokenise correctly split a string into a number of strings?...";
	string str1 = "string 1+string 2+string 3+string 4";
	vector<string> data1 = Tokenise(str1, '+');
	if (data1.size()==4 && data1[0] == "string 1" &&
	    data1[1] == "string 2" && data1[2] == "string 3" &&
	    data1[3] == "string 4")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does Tokensise NOT split a string when the specified character is not contained in the string?..." << endl;
	string str2 = "  This is a string which does not contain plus  ";
	vector<string> data2 = Tokenise(str2, '+');
	if (data2.size() == 1 && data2[0] == str2)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does Tokenise correctly split a string when the specified character occurs at the beginning of the string?...";
	string str3 = "+This string+contains plus at+the start";
	vector<string> data3 = Tokenise(str3, '+');
	if (data3.size() == 4 && data3[0] == "" &&
	    data3[1] == "This string" && data3[2] == "contains plus at" &&
	    data3[3] == "the start")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does Tokenise correctly split a string when the specified character is at the end of the string?..." << endl;
	string str4 = "This string contains+plus at the+end+";
	vector<string> data4 = Tokenise(str4, '+');
	if (data4.size() == 4 && data4[0] == "This string contains" &&
	    data4[1] == "plus at the" && data4[2] == "end" &&
	    data4[3] == "")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does Tokenise return a single string of length 0 if given a string of length 0?..." << endl;
	string str5 = "";
	vector<string> data5 = Tokenise(str5, '+');
	if (data5.size() == 1 && data5[0] == "")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does Tokenise correctly split strings on different tokens?...";
	string str6 = "AAA+AAA,BBB+BBB,CCC+CCC";
	vector<string> data6a = Tokenise(str6, '+');
	bool correct6a = (data6a.size() == 4 && data6a[0] == "AAA" && data6a[1] == "AAA,BBB" && data6a[2] == "BBB,CCC" && data6a[3] == "CCC");
	vector<string> data6b = Tokenise(str6, ',');
	bool correct6b = (data6b.size() == 3 && data6b[0] == "AAA+AAA" && data6b[1] == "BBB+BBB" && data6b[2] == "CCC+CCC");
	if (correct6a && correct6b)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

}

/******************************************************************************
 * StripWhite_tester()
 *
 * Function for testing global functions StripWhite(string)
 * and StripWhite(vector<string>).
 *
 * Author : Gareth Thompson
 */
void StripWhite_tester(void)
{
	if (testmode) cout << "entering StripWhite_tester()\n";
	cout << "Does StripWhite() correctly remove whitespace from the beginning and end of strings?...\n";
	string str1 = "String with spaces and stuff between words";
	string str2 = str1;
	str2 = "\t \n" + str1 + "\t \n";
	cout << "Original string: |" << str2 << "|\n";
	cout << "Stripped string: |" << StripWhite(str2) << "|\n";
	cout << "...";
	if (StripWhite(str2) == str1)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does StripWhite() correctly remove whitespace from the beginning and end of all strings in a vector?...\n";
	vector<string> data;
	data.push_back("String #1, with spaces and stuff");
	data.push_back("String #2, with spaces and stuff");
	data.push_back("String #3, with spaces and stuff");
	data.push_back("String #4, with spaces and stuff");
	vector<string> data2 = data;
	data2[0] = "\t \n" + data2[0] + "\t \n";
	data2[1] = "\t\t\t " + data2[1] + "\t\t\t ";
	data2[2] = "  \n  \n" + data2[2] + "  \n  \n";
	data2[3] = "        " + data2[3] + "        ";
	vector<string> data3 = StripWhite(data2);
	cout << "Comparing original and stripped strings...\n";
	for (int i=0; i<4; i++)
	{
		cout << "Original string #" << i+1 << ":\n|";
		cout << data2[i] << "|\n";
		cout << "Stripped string #" << i+1 << ":\n|";
		cout << data3[i] << "|\n";
	}
	if ( (data3.size() == 4) && (data3[0] == data[0]) &&
	     (data3[1] == data[1]) && (data3[2] == data[2]) &&
	     (data3[3] == data[3]) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

}

/******************************************************************************
 * ResizeString_tester()
 *
 * Function for testing global functions TruncateString(),
 * ExpandString() and ResizeString().
 *
 * Author : Gareth Thompson
 */
void ResizeString_tester(void)
{
	if (testmode) cout << "entering ResizeString_tester()\n";
	cout << "Does TruncateString correctly chop a string at the desired length?...\n";
	string str1 = "abcdefghijklmnopqrstuvwxyz";
	cout << "STRING: |" << str1 << "|\n";
	cout << "Chopped at 4: |" << TruncateString(str1, 4) << "|\n";
	cout << "Chopped at 25: |" << TruncateString(str1, 25) << "|\n";
	if (TruncateString(str1, 4) == "a..." &&
	    TruncateString(str1, 25) == "abcdefghijklmnopqrstuv...")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does TruncateString avoid chopping a string that is less than or equal to the desired length?...\n";
	string str2 = "abcdefghijklmnopqrstuvwxyz";
	cout << "STRING: |" << str2 << "|\n";
	cout << "Chopped at 40: |" << TruncateString(str2, 40) << "|\n";
	cout << "Chopped at 26: |" << TruncateString(str2, 26) << "|\n";
	if (TruncateString(str2, 40) == "abcdefghijklmnopqrstuvwxyz" &&
	    TruncateString(str2, 26) == "abcdefghijklmnopqrstuvwxyz")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does TruncateString return a blank string if the maximum length specified is less than 4?...\n";
	string str5 = "abcdefghij";
	if (TruncateString(str5, 3) == "" &&
	    TruncateString(str5, 0) == "")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ExpandString expand a string to the required length?...\n";
	string str3 = "abcde";
	cout << "STRING: |" << str3 << "|\n";
	cout << "Expanded to 6: |" << ExpandString(str3, 6) << "|\n";
	cout << "Expanded to 10: |" << ExpandString(str3, 10) << "|\n";
	if (ExpandString(str3, 6) == "abcde " &&
	    ExpandString(str3, 10) == "abcde     ")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ExpandString leave a string if it is already of the desired length?...\n";
	string str4 = "abcdefghij";
	cout << "STRING: |" << str4 << "|\n";
	cout << "Expanded to 5: |" << ExpandString(str4, 5) << "|\n";
	cout << "Expanded to 10: |" << ExpandString(str4, 10) << "|\n";
	if (ExpandString(str4, 5) == "abcdefghij" &&
	    ExpandString(str4, 10) == "abcdefghij")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ResizeString return a blank string if min > max?...\n";
	string str6 = "abcdefghij";
	if (ResizeString(str6, 7, 6) == "")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ResizeString return a blank string if max <= 3?...\n";
	if (ResizeString(str6, 1, 3) == "" &&
	    ResizeString(str6, 1, 2) == "")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ResizeString correctly expand strings shorter than min and chop strings longer than max?...\n";
	string str7 = "abcdefghijklmnopqrstuvwxyz";
	cout << "STRING: |" << str7 << "|\n";
	cout << "Min 4, Max 4: |" << ResizeString(str7, 4, 4) << "| -- ";
	if (ResizeString(str7, 4, 4) == "a...")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Min 25, Max 25: |" << ResizeString(str7, 25, 25) << "| -- ";
	if (ResizeString(str7, 25, 25) == "abcdefghijklmnopqrstuv...")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Min 27, Max 27: |" << ResizeString(str7, 27, 27) << "| -- ";
	if (ResizeString(str7, 27, 27) == "abcdefghijklmnopqrstuvwxyz ")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Min 40, Max 40: |" << ResizeString(str7, 40, 40) << "| -- ";
	if (ResizeString(str7, 40, 40) == "abcdefghijklmnopqrstuvwxyz              ")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does ResizeString leave a string with length greater than or equal to min and less than or equal to max?...\n";
	cout << "Min 10, Max 40: |" << ResizeString(str7, 10, 40) << "| -- ";
	if (ResizeString(str7, 10, 40) == "abcdefghijklmnopqrstuvwxyz")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Min 26, Max 26: |" << ResizeString(str7, 26, 26) << "| -- ";
	if (ResizeString(str7, 26, 26) == "abcdefghijklmnopqrstuvwxyz")
	{
		cout << "Correct.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
}

/******************************************************************************
 * Assignment_tester()
 *
 * Function for testing Assignment class.
 *
 * Author : Gareth Thompson
 */
void Assignment_tester(void)
{
	if (testmode) cout << "entering Assignment_tester()\n";
	cout << "Does constructor with arguments correctly set data values?...\n";
	Assignment assign1(20, 60.5);
	if (assign1.getAreaNum() == 20 &&
	    assign1.getResourceHours() == 60.5)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does default constructor initialise data values to 0?...\n";
	Assignment assign2;
	if (assign2.getAreaNum() == 0 &&
	    assign2.getResourceHours() == 0.0)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Can Area Numbers be set and get correctly?...\n";
	Assignment assign3(50, 90);
	assign3.setAreaNum(10);
	if (assign3.getAreaNum() == 10)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Can Resource Hours be set and get correctly?...\n";
	Assignment assign4(50, 90.0);
	assign4.setResourceHours(200.45);
	if (assign4.getResourceHours() == 200.45)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

}


/******************************************************************************
 * FloatCmp_tester()
 *
 * Function for testing FloatCmp functions.
 *
 * Author : Gareth Thompson
 */
void FloatCmp_tester(void)
{
	if (testmode) cout << "entering FloatCmp_tester()\n";
	cout << "Does FloatEqual return true if two floating point numbers differ by less than 0.0001?...";
	double numA1 = 2.0;
	double numA2 = numA1 + 0.5 * 0.0001;
	if (FloatEqual(numA1, numA2))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}
	cout << "Does FloatEqual return false if two floating point numbers differ by more than 0.0001?...";
	double numB1 = 2.0;
	double numB2 = numB1 + 1.5 * 0.0001;
	if (FloatEqual(numB1, numB2))
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	cout << "Does FloatLess return true if the first argument is less than the second by more than PRECISION?...";
	double numC1 = 2.0;
	double numC2 = numC1 -  1.5 * 0.0001;
	if (FloatLess(numC2, numC1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does FloatLess return false if the first argument is greater than the second?...";
	double numD1 = 2.0;
	double numD2 = 3.0;
	if (FloatLess(numD2, numD1))
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}

	cout << "Does FloatLess return false if the first argument is less than the second by less than PRECISION?...";
	double numE1 = 2.0;
	double numE2 = numE1 -  0.5 * 0.0001;
	if (FloatLess(numE2, numE1))
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}
}

/******************************************************************************
 * ChkType_tester()
 *
 * Function for testing ChkType functions.
 *
 * Author : Gareth Thompson
 */
void ChkType_tester(void)
{
	if (testmode) cout << "entering ChkType_tester()\n";
	/* Testing IsInt */
	cout << "Does IsInt return true for strings which are valid integers?...";
	if (testmode) cout << "LONG MIN: " << LONG_MIN << "\n";
	if (testmode) cout << "ULONG MAX: " << ULONG_MAX << "\n";
	ostrstream os1A;
	int minA = INT_MIN;
	os1A << minA << "\0";
	string minimumA = os1A.str();
	ostrstream os2A;
	int maxA = INT_MAX;
	os2A << maxA << "\0";
	string maximumA = os2A.str();
	ostrstream os3A;
	unsigned long negMinMinus1A = 0;
	negMinMinus1A -= INT_MIN;
	negMinMinus1A++;
	os3A << "-" << negMinMinus1A << "\0";
	string tooSmallA = os3A.str();
	ostrstream os4A;
	unsigned long maxPlus1A = INT_MAX;
	maxPlus1A++;
	os4A << maxPlus1A << "\0";
	string tooLargeA = os4A.str();
	if (IsInt("0") && IsInt("1045") && IsInt("-109") && IsInt("+165") && IsInt("-0") && IsInt("+0") && IsInt(minimumA) && IsInt(maximumA))
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}
	cout << "Does IsInt return false for strings which are not valid integers?...";
	if (!IsInt("--0") && !IsInt("++0") && !IsInt("a1034") && !IsInt("100.0") && !IsInt("1000 ") && !IsInt("1000g") && !IsInt("100-") &&
	    !IsInt(tooSmallA) && !IsInt(tooLargeA))
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}
	/* Testing IsFloat */
	string limitB1 = "-99999999999999";
	string limitB2 = "999999999999999";
	string limitB3 = ".00000000000001";
	string limitB4 = "-.0000000000001";
	string beyondLimitB1 = "-999999999999999";
	string beyondLimitB2 = "9999999999999999";
	string beyondLimitB3 = ".000000000000001";
	string beyondLimitB4 = "-.00000000000001";
	cout << "Does IsFloat return true for strings which are valid floating point numbers?...";
	if (IsFloat("0") && IsFloat("0.0") &&IsFloat("-0.0") &&
	    IsFloat("+0.0") && IsFloat("-.0") &&IsFloat("+.0") &&
	    IsFloat("0.") &&IsFloat("-0.") &&IsFloat("+0.") &&
	    IsFloat("1285.7500") &&IsFloat("1000.0000") &&
	    IsFloat("10.0001") &&IsFloat("000.6510") &&
	    IsFloat(limitB1) && IsFloat(limitB2) && IsFloat(limitB3) &&
	    IsFloat(limitB4) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}
	cout << "Does IsFloat return false for strings which are not valid floating point numbers?...";
	if (!IsFloat("--0") && !IsFloat("++0") && !IsFloat("0+") &&
	    !IsFloat("0-") && !IsFloat("0..0") && !IsFloat("-.0.0") &&
	    !IsFloat("+.0.0") && !IsFloat("+-0.0") && !IsFloat(" 0.0") &&
	    !IsFloat("a0.0") && !IsFloat("10.00g") && !IsFloat("\0.00") &&
	    !IsFloat(beyondLimitB1) && !IsFloat(beyondLimitB2) &&
	    !IsFloat(beyondLimitB3) && !IsFloat(beyondLimitB4) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}
}


/******************************************************************************
 * Output_tester()
 *
 * Function for testing Output functions.
 *
 * Author : Gareth Thompson
 */
void Output_tester(void)
{
	if (testmode) cout << "entering Output_tester()\n";
	/* Testing PrintAssignmentVector() */
	cout << "Does PrintAssignmentVector correctly print output?...\n";
	cout << "Output should be:\n";
	cout << "AREA NUMBER:   10      RESOURCE HOURS:    100.50\n";
	cout << "AREA NUMBER: 2000      RESOURCE HOURS: 550500.05\n";
	cout << "AREA NUMBER:    3      RESOURCE HOURS:      5.00\n";
	cout << "Output is:\n";
	vector<Assignment> assignments;
	assignments.push_back(Assignment(10, 100.50));
	assignments.push_back(Assignment(2000, 550500.05));
	assignments.push_back(Assignment(3, 5.0));
	PrintAssignmentVector(assignments);

	/* Testing PrintIntVector */
	cout << "Does PrintIntVector correctly print output?...\n";
	cout << "Output should be:\n";
	cout << "150*5*-30*10*1009*4*0*0*5*\n";
	cout << "Output is:\n";
	vector<int> integers;
	integers.push_back(150);
	integers.push_back(5);
	integers.push_back(-30);
	integers.push_back(10);
	integers.push_back(1009);
	integers.push_back(4);
	integers.push_back(0);
	integers.push_back(0);
	integers.push_back(5);
	PrintIntVector(integers);
	cout << "\n";
	/* Testing PrintStringVector */
	cout << "Does PrintStringVector correctly print output?...\n";
	cout << "Output should be:\n";
	cout << "Hello*This is a long string*  String with spaces  *Yum*\tString\twith\ttabs*Yeehah*\nString\nwith\nnewlines*\n";
	cout << "Output is:\n";
	vector<string> strings;
	strings.push_back("Hello");
	strings.push_back("This is a long string");
	strings.push_back("  String with spaces  ");
	strings.push_back("Yum");
	strings.push_back("\tString\twith\ttabs");
	strings.push_back("Yeehah");
	strings.push_back("\nString\nwith\nnewlines");
	PrintStringVector(strings);
	cout << "\n";
}

/******************************************************************************
 * DataLimt_tester()
 *
 * Function for testing DataLimits class.
 *
 * Author : Gareth Thompson
 */
void DataLimt_tester(void)
{
	if (testmode) cout << "entering DataLimt_tester()\n";
	cout << "Does isValidTerrain() return true for valid terrain values?...";
	if (DataLimits::isValidTerrain(1) &&
	    DataLimits::isValidTerrain(100) &&
	    DataLimits::isValidTerrain(50) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}

	cout << "Does isValidTerrain() return false for invalid terrain values?...";
	if (!DataLimits::isValidTerrain(0) &&
	    !DataLimits::isValidTerrain(101) &&
	    !DataLimits::isValidTerrain(-10) &&
	    !DataLimits::isValidTerrain(500) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}

	cout << "Does isValidVegetation() return true for valid vegetation values?...";
	if (DataLimits::isValidVegetation(1) &&
	    DataLimits::isValidVegetation(2) &&
	    DataLimits::isValidVegetation(3) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}

	cout << "Does isValidVegetation() return false for invalid vegetation values?...";
	if (!DataLimits::isValidVegetation(0) &&
	    !DataLimits::isValidVegetation(4) &&
	    !DataLimits::isValidVegetation(-10) &&
	    !DataLimits::isValidVegetation(100) )
	{
		cout << "Yes.  SUCCESS\n";
	}
	else
	{
		cout << "No.  FAILURE\n";
	}
}

/******************************************************************************
 * ConToStr_tester()
 *
 * Function for testing ConToStr function.
 *
 * Author : Gareth Thompson
 */
void ConToStr_tester(void)
{
	if (testmode) cout << "entering ConToStr_tester()\n";
	cout << "Does ConToStr() correctly convert various types to strings?...\n";
	cout << "Converting integer to string:\n";
	cout << "Integer: 5\t";
	string str1 = ConvertToStr(5);
	cout << "String: " << str1 << endl;
	cout << "Converting double to string:\n";
	cout << "Double: 3.14159\t";
	string str2 = ConvertToStr(3.14159);
	cout << "String: " << str2 << endl;
	cout << "Converting large double to string:\n";
	cout << "Double: 123456789012345\t";
	string str3 = ConvertToStr((double) 123456789012345.00);
	cout << "String: " << str3 << endl;
//	cout << "Converting large double to string:\n";
//	cout << "Double: 1234567890.34\t";
//	string str4 = ConvertToStr(1234567890.34);
//	cout << "String: " << str4 << endl;
//
//	cout << "Converting large double to string:\n";
//	cout << "Double: 1234567890123456789.34\t";
//	string str5 = ConvertToStr(1234567890123456789.34);
//	cout << "String: " << str5 << endl;
//
//	cout << "Converting large double to string:\n";
//	cout <<
//"Double: 123456789012345678901234567890.34\t";
//	string str6 =
//ConvertToStr(123456789012345678901234567890.34);
//	cout << "String: " << str6 << endl;
}

/******************************************************************************
 * Srchman_tester()
 *
 * Function for testing SearchManager class.
 *
 * Author : Gareth Thompson
 */
void Srchman_tester(void)
{
	if (testmode) cout << "entering Srchman_tester()\n";
	SearchManager searchMan;
	searchMan.test();
}
