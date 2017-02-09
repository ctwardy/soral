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
 * test_res.cpp
 *
 * test() function for testing Resources's private functions
 *
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 08/04/01 |  1  | Created.
 *----------------------------------------------------------------------------
 * GT  | 21/04/01 |  2  | Updated.  Tests changed functions in Resources.
 *----------------------------------------------------------------------------
 * GT  | 07/05/01 |  3  | Updated.  Tests changed functions in Resources.
 *----------------------------------------------------------------------------
 * GT  | 25/05/01 |  5  | Updated.  Tests changed functions in Resources.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 5.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include <iostream>
#include <string>
#include "Resource.h"
#include "Assignmt.h"
#include "global.h"
//#include "DataLimt.h"
using namespace std;

/******************************************************************************
 * test()
 *
 * Tests functions of Resources that are not
 * externally accessible.
 *
 * Author : Gareth Thompson
 */

void Resources::test(void)
{
        if (testmode) cout << "entering Resources::test()\n";

	/* Testing SRU() */
	SRU sru1;

	cout << "Are all values set correctly by constructor?...";

	/* Check that all correction factors are not initially set */
	int terrain1, vegetation1;
	bool correctionFactorSet1 = false;
	for (terrain1=1; terrain1<=100; terrain1++)
	{
		for (vegetation1=1; vegetation1<=3; vegetation1++)
		{
			if (sru1.isCorrectionFactorSet(terrain1, vegetation1))
			{
				correctionFactorSet1 = true;
			}
		}
	}

	if (sru1.getResourceNum() == DataLimits::resourceNum_min && sru1.getResourceType() == "" &&
	    sru1.getPOD() == DataLimits::POD_min && sru1.getESW() == DataLimits::ESW_min &&
	    sru1.getSpeed() == DataLimits::speed_min && sru1.getHoursAvail() == DataLimits::hoursAvailable_min &&
	    sru1.getAssignments().size() == 0 && correctionFactorSet1 == false)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing setResourceNum() and getResourceNum() */
	SRU sru3;

	cout << "Can I set and get Resource Numbers correctly?...";
	sru3.setResourceNum(5);
	if (sru3.getResourceNum() == 5)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setResourceNum() set the ResourceNumber if given valid data?...";
	if (sru3.setResourceNum(0) && (sru3.getResourceNum() == 0) &&
	    sru3.setResourceNum(5000) && (sru3.getResourceNum() == 5000) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setResourceNum() fail to set the ResourceNumber if given invalid data?...";
	sru3.setResourceNum(10);
	if (!sru3.setResourceNum(-1) && (sru3.getResourceNum() == 10) &&
	    !sru3.setResourceNum(-1000) && (sru3.getResourceNum() == 10) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing setResourceType() and getResourceType() */
	cout << "Can I set and get Resource Types correctly?...";
	sru3.setResourceType("Type XXX");
	if (sru3.getResourceType() == "Type XXX")
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing setPOD() and getPOD() */
	cout << "Can I set and get PODs correctly?...";
	sru3.setPOD(20.55);
	if (sru3.getPOD() == 20.55)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setPOD() set the POD if given valid data?...";
	if (sru3.setPOD(0) && (sru3.getPOD() == 0) &&
	    sru3.setPOD(100) && (sru3.getPOD() == 100) &&
	    sru3.setPOD(50) && (sru3.getPOD() == 50) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setPOD() fail to set the POD if given invalid data?...";
	sru3.setPOD(20);
	if (!sru3.setPOD(-0.05) && (sru3.getPOD() == 20) &&
	    !sru3.setPOD(100.05) && (sru3.getPOD() == 20) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}




	/* Testing setESW() and getESW() */
	cout << "Can I set and get ESWs correctly?...";
	sru3.setESW(40.64);
	if (sru3.getESW() == 40.64)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setESW() set the ESW if given valid data?...";
	if (sru3.setESW(0) && (sru3.getESW() == 0) &&
	    sru3.setESW(FLOATMAXVAL) && (sru3.getESW() == FLOATMAXVAL) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setESW() fail to set the ESW if given invalid data?...";
	sru3.setESW(20);
	if (!sru3.setESW(-0.05) && (sru3.getESW() == 20) &&
	    !sru3.setESW(FLOATMAXVAL*1.1) && (sru3.getESW() == 20) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}



	/* Testing setSpeed() and getSpeed() */
	cout << "Can I set and get Speeds correctly?...";
	sru3.setSpeed(53.54);
	if (sru3.getSpeed() == 53.54)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setSpeed() set the speed if given valid data?...";
	if (sru3.setSpeed(0) && (sru3.getSpeed() == 0) &&
	    sru3.setSpeed(FLOATMAXVAL) && (sru3.getSpeed() == FLOATMAXVAL) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setSpeed() fail to set the Speed if given invalid data?...";
	sru3.setSpeed(20);
	if (!sru3.setSpeed(-0.05) && (sru3.getSpeed() == 20) &&
	    !sru3.setSpeed(FLOATMAXVAL*1.1) && (sru3.getSpeed() == 20) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing setHoursAvail() and getHoursAvail() */
	cout << "Can I set and get hours available correctly?...";
	sru3.setHoursAvail(60);
	if (sru3.getHoursAvail() == 60)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setHoursAvail() set the hours available if given valid data?...";
	if (sru3.setHoursAvail(0) && (sru3.getHoursAvail() == 0) &&
	    sru3.setHoursAvail(5000) && (sru3.getHoursAvail() == 5000) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setHoursAvail() fail to set the Hours Available if given invalid data?...";
	sru3.setHoursAvail(10);
	if (!sru3.setHoursAvail(-1) && (sru3.getHoursAvail() == 10) &&
	    !sru3.setHoursAvail(-5000) && (sru3.getHoursAvail() == 10) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing isCorrectionFactorSet() */
	sru3.deleteCorrectionFactor(1,1);
	sru3.setCorrectionFactor(1,2,5.0);
	sru3.setCorrectionFactor(1,3,1.0);

	cout << "Does isCorrectionFactorSet() return false if the terrain or vegetation values are invalid?...";
	if (!sru3.isCorrectionFactorSet(0,1) && !sru3.isCorrectionFactorSet(101,1) &&
	    !sru3.isCorrectionFactorSet(1,0) && !sru3.isCorrectionFactorSet(1,4))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does isCorrectionFactorSet() return false if no correction factor is set?...";
	if (!sru3.isCorrectionFactorSet(1,1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does isCorrectionFactorSet() return true if a correction factor is set?...";
	if (sru3.isCorrectionFactorSet(1,2) && sru3.isCorrectionFactorSet(1,3))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing setCorrectionFactor() and getCorrectionFactor() */
	cout << "Does setCorrectionFactor() return false if the terrain or vegetation values are invalid?...";
	if (!sru3.setCorrectionFactor(0,1, 2.0) &&
	    !sru3.setCorrectionFactor(101,1, 2.0) &&
	    !sru3.setCorrectionFactor(1,0, 2.0) &&
	    !sru3.setCorrectionFactor(1,4, 2.0))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does setCorrectionFactor() ignore the specified correction factor if it is invalid?...";

	sru3.setCorrectionFactor(2,1,2.0);
	sru3.setCorrectionFactor(2,2,3.0);

	if (!sru3.setCorrectionFactor(2,1,-0.0000001) &&
	    FloatEqual(sru3.getCorrectionFactor(2,1), 2.0) &&
	    !sru3.setCorrectionFactor(2,2,10+1.5*0.0001) &&
	    FloatEqual(sru3.getCorrectionFactor(2,2), 3.0))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Do setCorrectionFactor() and getCorrectionFactor work correctly if the terrain/vegetation and correction factor values are all valid?...";
	sru3.setCorrectionFactor(3,1,0.0);
	sru3.setCorrectionFactor(3,2,10.0);
	sru3.setCorrectionFactor(3,3,1.0);
	sru3.setCorrectionFactor(100,3, 3.5);

	if (FloatEqual(sru3.getCorrectionFactor(3,1), 0) &&
	    FloatEqual(sru3.getCorrectionFactor(3,2), 10) &&
	    FloatEqual(sru3.getCorrectionFactor(3,3), 1.0) &&
	    FloatEqual(sru3.getCorrectionFactor(100,3), 3.5))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does getCorrectionFactor return 1.0 if no correction factor has been defined?...";
	sru3.deleteCorrectionFactor(4,1);

	if (FloatEqual(sru3.getCorrectionFactor(4,1), 1.0))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does getCorrectionFactor return successfully (with undefined return value) if the terrain or vegetation values are invalid?...";
	sru3.getCorrectionFactor(0,1);
	sru3.getCorrectionFactor(101,1);
	sru3.getCorrectionFactor(1,0);
	sru3.getCorrectionFactor(1,4);
	cout << "Yes.  SUCCESS." << endl;

	/* Testing deleteCorrectionFactor() */
	cout << "Does deleteCorrectionFactor() return false if the terrain or vegetation values are invalid?...";
	if (!sru3.deleteCorrectionFactor(0,1) &&
	    !sru3.deleteCorrectionFactor(101,1) &&
	    !sru3.deleteCorrectionFactor(1,0) &&
	    !sru3.deleteCorrectionFactor(1,4))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does deleteCorrectionFactor return false if no correction factor has been set?...";
	sru3.deleteCorrectionFactor(5,1);

	if (!sru3.deleteCorrectionFactor(5,1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does deleteCorrectionFactor delete the correction factor if a correction factor has been set?...";
	sru3.setCorrectionFactor(6,1,5.0);

	if (sru3.isCorrectionFactorSet(6,1) &&
	    sru3.deleteCorrectionFactor(6,1) &&
	    !sru3.isCorrectionFactorSet(6,1))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing deleteCorrectionFactors() */
	cout << "Does deleteCorrectionFactors() delete all correction factors for this SRU?...";
	sru3.setCorrectionFactor(7,1,5.0);
	sru3.setCorrectionFactor(10,2,1.0);
	sru3.setCorrectionFactor(100,1,3.0);

	int terrain3, vegetation3;
	bool initiallySet, finallySet;

	if (sru3.isCorrectionFactorSet(7,1) &&
	    sru3.isCorrectionFactorSet(10,2) &&
	    sru3.isCorrectionFactorSet(100,1))
	{
		initiallySet = true;
	}

	sru3.deleteCorrectionFactors();

	finallySet = false;
	for (terrain3=1; terrain3<=100; terrain3++)
	{
		for (vegetation3=1; vegetation3<=3; vegetation3++)
		{
			if (sru3.isCorrectionFactorSet(terrain3, vegetation3))
			{
				finallySet = true;
			}
		}
	}

	if (initiallySet == true && finallySet == false)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing viewCorrectionFactors() */
	cout << "Does viewCorrectionFactors correctly display correction factor data?...\n";
	cout << "Output should be...\n";

	cout << "Terrain   Vegetation     Correction\n";
	cout << "		           Factor\n";
	cout << "===================================\n";
	cout << "    1          1            1.000\n";
	cout << "    1          2            2.000\n";
	cout << "   10          1            3.510\n";
	cout << "   10          3            9.500\n";
	cout << "   50          2            0.041\n";
	cout << "  100          3           10.000\n";

	cout << "Output is...\n";

	SRU sru4;
	sru4.setCorrectionFactor(1,1,1.0);
	sru4.setCorrectionFactor(1,2,2.0);
	sru4.setCorrectionFactor(10,1,3.51);
	sru4.setCorrectionFactor(10,3,9.50);
	sru4.setCorrectionFactor(50,2,0.041);
	sru4.setCorrectionFactor(100,3,10.0);

	sru4.viewCorrectionFactors();

	/* Testing addAssignment() and getAssignments() */
	cout << "Can I add and get Assignments correctly?...";
	sru3.setHoursAvail(2000);  /* Allow enough hours for the assignments below */
	sru3.addAssignment(Assignment(50,70.0));
	sru3.addAssignment(Assignment(80,40.5));
	sru3.addAssignment(Assignment(500,1000.0));

	vector<Assignment> assignments1 = sru3.getAssignments();

	if (testmode) PrintAssignmentVector(assignments1);

	if (assignments1.size() == 3 &&
	    assignments1[0].getAreaNum() == 50 &&
	    FloatEqual(assignments1[0].getResourceHours(), 70.0) &&
	    assignments1[1].getAreaNum() == 80 &&
	    FloatEqual(assignments1[1].getResourceHours(), 40.5) &&
	    assignments1[2].getAreaNum() == 500 &&
	    FloatEqual(assignments1[2].getResourceHours(), 1000.0) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	cout << "Does addAssignment() correctly add an assignment if sufficient resource hours are available?...";
	SRU sru13;
	sru13.setHoursAvail(10);
	sru13.addAssignment(Assignment(1, 5.0));
	sru13.addAssignment(Assignment(2, 3.0));

	/*
	 * Select a number of resource-hours that exceeds that available
	 * by less than the floating-point precision (0.0001)
	 */
	bool success1 = sru13.addAssignment(Assignment(3, 2.0 + 0.5 * 0.0001));

	vector<Assignment> assignments3 = sru13.getAssignments();

	if (testmode) PrintAssignmentVector(assignments3);

	if (success1 == true &&
	    assignments3.size() == 3 &&
	    assignments3[0].getAreaNum() == 1 &&
	    FloatEqual(assignments3[0].getResourceHours(), 5.0) &&
	    assignments3[1].getAreaNum() == 2 &&
	    FloatEqual(assignments3[1].getResourceHours(), 3.0) &&
	    assignments3[2].getAreaNum() == 3 &&
	    FloatEqual(assignments3[2].getResourceHours(), 2.0) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	cout << "Does addAssignment() add an assignment if insufficient resource hours are available?...";
	SRU sru14;
	sru14.setHoursAvail(10);
	sru14.addAssignment(Assignment(1, 4.5));
	sru14.addAssignment(Assignment(2, 3.5));

	/*
	 * Select a number of resource-hours that exceeds that available
	 * by more than the floating-point precision (0.0001)
	 */
	bool success2 = sru14.addAssignment(Assignment(3, 2.0 + 1.5 * 0.0001));

	vector<Assignment> assignments4 = sru14.getAssignments();

	if (testmode) PrintAssignmentVector(assignments4);

	if (success2 == false &&
	    assignments4.size() == 2 &&
	    assignments4[0].getAreaNum() == 1 &&
	    FloatEqual(assignments4[0].getResourceHours(), 4.5) &&
	    assignments4[1].getAreaNum() == 2 &&
	    FloatEqual(assignments4[1].getResourceHours(), 3.5) )
	{
		cout << "No.  SUCCESS." << endl;
	}
	else
	{
		cout << "Yes.  FAILURE." << endl;
	}

	cout << "Does addAssignment() alter the data stored when adding an Assignment with Resource Hours equal to 0?...";

	SRU sru20;
	sru20.setHoursAvail(10);
	sru20.addAssignment(Assignment(1, 4.5));
	sru20.addAssignment(Assignment(2, 3.5));

	/*
	 * Select a number of resource-hours that exceeds 0
	 * by less than the floating-point precision (0.0001)
	 */
	bool success3 = sru20.addAssignment(Assignment(3, 0.5 * 0.0001));

	vector<Assignment> assignments5 = sru20.getAssignments();

	if (testmode) PrintAssignmentVector(assignments5);

	if (success3 == true &&
	    assignments5.size() == 2 &&
	    assignments5[0].getAreaNum() == 1 &&
	    FloatEqual(assignments5[0].getResourceHours(), 4.5) &&
	    assignments5[1].getAreaNum() == 2 &&
	    FloatEqual(assignments5[1].getResourceHours(), 3.5) )
	{
		cout << "No.  SUCCESS." << endl;
	}
	else
	{
		cout << "Yes.  FAILURE." << endl;
	}

	cout << "Does addAssignment() add the Resource Hours of two Assignments with equal Area Numbers?...";

	SRU sru21;
	sru21.setHoursAvail(10);
	sru21.addAssignment(Assignment(1, 4.5));
	sru21.addAssignment(Assignment(2, 3.5));

	bool success4 = sru21.addAssignment(Assignment(2, 1.5));

	vector<Assignment> assignments6 = sru21.getAssignments();

	if (testmode) PrintAssignmentVector(assignments6);

	if (success4 == true &&
	    assignments6.size() == 2 &&
	    assignments6[0].getAreaNum() == 1 &&
	    FloatEqual(assignments6[0].getResourceHours(), 4.5) &&
	    assignments6[1].getAreaNum() == 2 &&
	    FloatEqual(assignments6[1].getResourceHours(), 5.0) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does addAssignment() fail to add an assignment if the resource-hours of the specified assignment are negative?...";

	SRU sru24;
	sru24.setHoursAvail(10);
	sru24.addAssignment(Assignment(1, 4.5));
	sru24.addAssignment(Assignment(2, 3.5));

	bool success7 = sru24.addAssignment(Assignment(2, -0.05));

	vector<Assignment> assignments9 = sru24.getAssignments();

	if (testmode) PrintAssignmentVector(assignments9);

	if (success7 == false &&
	    assignments9.size() == 2 &&
	    assignments9[0].getAreaNum() == 1 &&
	    FloatEqual(assignments9[0].getResourceHours(), 4.5) &&
	    assignments9[1].getAreaNum() == 2 &&
	    FloatEqual(assignments9[1].getResourceHours(), 3.5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/*Testing deleteAssignment() */
	cout << "Does deleteAssignment() correctly delete an assignment with a specified Area Number?...";
	SRU sru22;
	sru22.setHoursAvail(2000);
	sru22.addAssignment(Assignment(50,70.5));
	sru22.addAssignment(Assignment(80,40.5));
	sru22.addAssignment(Assignment(500,1000.5));
	bool success5 = sru22.deleteAssignment(80);

	vector<Assignment> assignments7 = sru22.getAssignments();

	if (testmode) PrintAssignmentVector(assignments7);

	if (success5 == true &&
	    assignments7.size() == 2 &&
	    assignments7[0].getAreaNum() == 50 &&
	    FloatEqual(assignments7[0].getResourceHours(), 70.5) &&
	    assignments7[1].getAreaNum() == 500 &&
	    FloatEqual(assignments7[1].getResourceHours(), 1000.5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does deleteAssignment fail to delete an assignment if there is none with the specified area number?...";
	bool success6 = sru22.deleteAssignment(1);

	vector<Assignment> assignments8 = sru22.getAssignments();

	if (testmode) PrintAssignmentVector(assignments8);

	if (success6 == false &&
	    assignments8.size() == 2 &&
	    assignments8[0].getAreaNum() == 50 &&
	    FloatEqual(assignments8[0].getResourceHours(), 70.5) &&
	    assignments8[1].getAreaNum() == 500 &&
	    FloatEqual(assignments8[1].getResourceHours(), 1000.5) )
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	/* Testing deleteAssignments() */
	cout << "Can I delete Assignments correctly?...";
	SRU sru5;
	sru5.setHoursAvail(2000);
	sru5.addAssignment(Assignment(50,70.5));
	sru5.addAssignment(Assignment(80,40.5));
	sru5.addAssignment(Assignment(500,1000.5));
	sru5.deleteAssignments();

	vector<Assignment> assignments2 = sru5.getAssignments();

	if (testmode) PrintAssignmentVector(assignments2);

	if (assignments2.size() == 0)
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing getHoursRemaining() */
	cout << "Does getHoursRemaining() correctly return the number of resource hours still to be allocated for an SRU?...";

	SRU sru6;
	sru6.setHoursAvail(145);
	sru6.addAssignment(Assignment(50,10.5));
	sru6.addAssignment(Assignment(80,35.0));
	sru6.addAssignment(Assignment(500,11.2));

	if (FloatEqual(sru6.getHoursRemaining(), 88.3))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	/* Testing hoursRemaining() */
	cout << "Does hoursRemaining return true if there are still resource-hours to be allocated for this SRU?...";

	/*
	 * Use assignments that leave more resource-hours available than the
	 * floating-point precision (0.0001).
	 */
	SRU sru15;
	sru15.setHoursAvail(10);
	sru15.addAssignment(Assignment(1, 5.0));
	sru15.addAssignment(Assignment(1, 3.0));
	sru15.addAssignment(Assignment(1, 2.0 - 1.5 * 0.0001));

	if (sru15.hoursRemaining())
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}


	cout << "Does hoursRemaining return false if there are no resource-hours still to be allocated for this SRU?...";

	/*
	 * Use assignments that leave less resource-hours available than the
	 * floating-point precision (0.0001).
	 */
	SRU sru16;
	sru16.setHoursAvail(10);
	sru16.addAssignment(Assignment(1, 5.0));
	sru16.addAssignment(Assignment(1, 3.0));
	sru16.addAssignment(Assignment(1, 2.0 - 0.5 * 0.0001));

	if (sru16.hoursRemaining())
	{
		cout << "No.  FAILURE." << endl;
	}
	else
	{
		cout << "Yes.  SUCCESS." << endl;
	}


	/* Testing getHoursAssigned() */
	cout << "Does getHoursAssigned() correctly return the number of resource hours assigned for this SRU?...";

	SRU sru17;
	sru17.setHoursAvail(145);
	sru17.addAssignment(Assignment(50,10.5));
	sru17.addAssignment(Assignment(80,35.0));
	sru17.addAssignment(Assignment(500,11.2));

	if (FloatEqual(sru17.getHoursAssigned(), 56.7))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}



	/* Testing ltResNum */
	cout << "Does ltResNum(A, B) return true if A has Resource Number less than B?...";
	SRU sru7;
	sru7.setResourceNum(10);
	SRU sru8;
	sru8.setResourceNum(12);
	SRU::ltResNum srult;
	if (srult(sru7, sru8))
	{
		cout << "Yes.  SUCCESS." << endl;
	}
	else
	{
		cout << "No.  FAILURE." << endl;
	}

	cout << "Does ltResNum(A, B) return true if A has Resource Number equal to B?...";
	SRU sru9;
	sru7.setResourceNum(10);
	SRU sru10;
	sru8.setResourceNum(10);
	if (srult(sru9, sru10))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}

	cout << "Does ltResNum(A, B) return true if A has Resource Number greater than B?...";
	SRU sru11;
	sru7.setResourceNum(20);
	SRU sru12;
	sru8.setResourceNum(12);
	if (srult(sru11, sru12))
	{
		cout << "Yes.  FAILURE." << endl;
	}
	else
	{
		cout << "No.  SUCCESS." << endl;
	}

	/* Testing getEffectiveSweepRate */
	cout << "Does getEffectiveSweepRate() return the correct value if no correction factors are specified as arguments?...";

	SRU sru18;
	sru18.setESW(12.6);
	sru18.setSpeed(21.5);
	sru18.setCorrectionFactor(1,1,3.0);

	if (FloatEqual(sru18.getEffectiveSweepRate(), 0.2709))
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}

	cout << "Does getEffectiveSweepRate() return the correct value if invalid terrain and vegetation values are specified as arguments?...";
	if (FloatEqual(sru18.getEffectiveSweepRate(0,1), 0.2709) &&
	    FloatEqual(sru18.getEffectiveSweepRate(101,1), 0.2709) &&
	    FloatEqual(sru18.getEffectiveSweepRate(1,0), 0.2709) &&
	    FloatEqual(sru18.getEffectiveSweepRate(1,4), 0.2709))
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}

	cout << "Does getEffectiveSweepRate() return the correct value if valid terrain and vegetation values are specified?...";
	if (FloatEqual(sru18.getEffectiveSweepRate(1,1), 0.8127))
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}


	/* Testing getSRUString */
	cout << "Does getSRUString() return the date stored in an SRU in the desired format?...";

	cout << "Output should be:\n";
	cout << "1, Excellent Stuff, 32.45, 11.56, 5.45, 150, ()\n";

	cout << "Output is: \n";
	SRU sru19;
	sru19.setResourceNum(1);
	sru19.setResourceType("Excellent Stuff");
	sru19.setPOD(32.45);
	sru19.setESW(11.56);
	sru19.setSpeed(5.45);
	sru19.setHoursAvail(150);
	cout << sru19.getSRUString() << endl;

	/* sortResNum() and findSRU() not tested here */

	/* Testing addSRU */
	cout << "Does addSRU successfully insert an SRU?...";
	SRU sru23;
	sru23.setResourceNum(1001);

	if (addSRU(sru23) && isSRU(1001))
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}

	cout << "Does addSRU prevent an SRU being added if it has the same Resource Number as an existing SRU?...";
	if (!addSRU(sru23) && isSRU(1001))
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}

	/* Testing SRU::isValidCorrectionFactor() */
	cout << "Does SRU::isValidCorectionFactor() return true for valid correction factor values?...";

	if (SRU::isValidCorrectionFactor(0) && SRU::isValidCorrectionFactor(10) &&
	    SRU::isValidCorrectionFactor(5) )
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}

	cout << "Does SRU::isValidCorectionFactor() return false for invalid correction factor values?...";

	if (!SRU::isValidCorrectionFactor(-0.01) && !SRU::isValidCorrectionFactor(10.01) )
	{
		cout << "Yes.  SUCCESS.\n";
	}
	else
	{
		cout << "No.  FAILURE.\n";
	}
}
