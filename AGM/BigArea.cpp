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
 * BigAreas.cpp
 *
 *  Display Map showing POAs. Provide and Update POA values. Store Areas data.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * AO  | 02/04/00 |  1  | Created.
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */



#include <iostream>

#include <vector>

#include <string>

#include "InputFil.h"

#include <fstream>

#include "math.h"

#include "Areas.h"

#include <stdio.h>

#include "global.h"

#include "Err_mngr.h"

#include <cstdio>

#include "DataLimt.h"



using namespace std;

//char delaykey(string prompts); // messy patch. Linking is happening in the wrong order under windows.



/******************************************************************************

 * Normalise()

 *

 * Normalises the POA's

 *

 * Author : Andre Oboler

 */



int BigArea::Normalise()

{

	int i;

	float total=0;

	float scaler;



	for (i=0; i<area.size(); i++)

	{

		total=total + area[i].getPOA(); // Get POA return 0 is area no longer exists. So this does work in all cases !

	}



	scaler=100.0 / total;

	if (testmode) cout << "\nScaler is: " << scaler << "\n";



	for (i=0; i<area.size(); i++)

	{

		if (testmode) cout << area[i].getPOA() << " * " << scaler << " = ";

		area[i].setPOA(area[i].getPOA() * scaler);

		if (testmode) cout << area[i].getPOA() << "\n";



	}

	return 1;

}



/******************************************************************************

 * findArea()

 *

 * Returns -911 on area number not found. Else returns index into the vector of Areas

 * that references the area with area number "number"

 *

 * Author : Andre Oboler

 */

// WARNING: the number this function gets is an Area number.

//          the number it returns is the storage possition in the vector.

//          Do not confuse the two ! - Ao.

int BigArea::findArea(int number)

{

	int i;

	for (i=0; i<area.size(); i++)

	{

		if (area[i].getNumber() == number)

			return i;

	}

	return -911;

}



/******************************************************************************

 * getAreaNumList

 *

 * An addaption of Gareth's getSRUList, for areas.

 * The returned list is NOT in order (if it needs to be for some reason, let me know)

 *

 * Author : Andre Oboler

 */



vector<int> BigArea::getAreaNumList(void)

{

	if (testmode) cout << "entering BigArea::getAreaNumList()\n";



	vector<int> list;

	vector<Area>::iterator current;



	for (current = area.begin(); current != area.end(); current++)

	{

		list.push_back(current->getNumber());

	}



	return list;



}





/******************************************************************************

 * getSize

 *

 * Returns the Size of an area

 *

 * Author : Andre Oboler

 */



float BigArea::getSize(int number) // const float ?

{

	int index = findArea(number);

	if (isArea(number))

	{

		return area[index].getSize();

	}

	else

		return 0;



}



/******************************************************************************

 * getTerrain

 *

 * Returns the terrain of an area

 *

 * Author : Michael Eldridge

 */



int BigArea::getTerrain(int number)

{

	int index = findArea(number);

	if (isArea(number))

	{

		return area[index].getTerrain();

	}

	else

		return 0;



}



/******************************************************************************

 * getVegetation

 *

 * Returns the vegetation of an area

 *

 * Author : Michael Eldridge

 */



int BigArea::getVegetation(int number)

{

	int index = findArea(number);

	if (isArea(number))

	{

		return area[index].getVegetation();

	}

	else

		return 0;



}



/******************************************************************************

 * getPden

 *

 * Returns the Probability Density of an area

 *

 * Author : Andre Oboler

 */



float BigArea::getPden(int number) // const float ?

{

	int index = findArea(number);



	if (isArea(number))

	{

		return (area[index].getPOA() / area[index].getSize());

	}

	else

		return 0;



}



/******************************************************************************

 * isValid()

 *

 * This method checks to see if POAs as a whole look reasonable

 *

 * Author : Andre Oboler

 */



bool BigArea::isValid(void)

{

	int i;

	float total=0, restofworld;



	for (i=0; i<area.size(); i++)

	{

		total = total + area[i].getPOA();

	}

	if (isArea(-2) && area[findArea(-2)].getPOA() != 0)

	{

		cout << "\nBace camp has a probability greater than 0. Hmm... that could be a problem.\n";

		return 0;

	}

	if (isArea(-1))

	{

		restofworld = area[findArea(-1)].getPOA();

	}

	if (isArea(-1) && restofworld < 1)

	{

		cout << "\nRest of world has less than probability of less than 1. You sure about that ?\n";

		return 0;

	}

	else if (isArea(-1) && restofworld > 95)

	{

		cout << "\nRest of world has probability greater than 95%. You should give up.\n";

		return 0;

	}

	if (total != 100)

	{

		cout << "Total POA is not 100 ! (its " << total << ")\n";

		return 0;

	}

	return 1;

}



/******************************************************************************

 * isArea()

 *

 * Predicate funciton: Does area "number" exist ?

 *

 * Author : Andre Oboler

 */



bool BigArea::isArea(int number)

{

	if (findArea(number) == -911)

	{

		// Area does not exist

		return 0;

	}

	else

	{

		//Area Exists

		return 1;

	}

}



/******************************************************************************

 * Menu_____() collection

 *

 * Funciton: These functions allow search manager to call menu options directly.

 *

 * Author : Andre Oboler

 */



bool BigArea::MenuDeleteArea(int number)

{

	if (isArea(number))

	{

		deleteArea(number);

		return true;

	}

	else

	{

		return false;

	}

}



int BigArea::MenuExit(void)

{

		return 1;

}



int BigArea::MenuMap(void)

{

	int choice;



	cout << "\n(1) map showing POA's\n(2) graphical POA density map\n(3) both\n";

	cout << "Enter map prefference: ";

	cin >> choice;

	if (choice==1)

		printmap();

	else if (choice==2)

		printsymbolmap();

	else

	{

		printmap();

		printsymbolmap();

	}



	return 1;

}



int BigArea::MenuLoad(void)

{

	string filename;



	cout << "\nEnter name of file to load (eg area.dat): ";

	filename = GetInputString(cin);

	loadAreas(filename);

	return 1;

}



int BigArea::MenuSave(void)

{

	string filename;



	cout << "\nEnter name of file to save (eg area.dat): ";

	filename = GetInputString(cin);

	getAreas(filename);

	return 1;

}





int BigArea::MenuView(void)

{

	int number;



	cout << "\n";

	number = GetValidInputInteger("Enter number of Area to view: ", "Invalid Entry!", DataLimits::areaNum_min, DataLimits::areaNum_max);



	//number=findArea(number); // Changes number from Area to its index

	viewArea(number);

	return 1;

}



int BigArea::MenuNewArea()

{

	int number;

	UTM loc;

	string boundries;

	int traveltime;

	int alt;

	int terrain;

	int vegetation;

	float POA;



	// Do modify stuff

	cout << "Please enter new data\n";

	cout << "*********************\n";



	/* Area Number */

	cout << "\n";

	do

	{

		number = GetValidInputInteger("Area Number (1-100, -1 or -2): ", "Invalid Entry!", DataLimits::areaNum_min, DataLimits::areaNum_max);



		if (number == 0)

		{

			cout << "Invalid Entry!\n";

		}

	} while (number == 0);



	if (isArea(number))

	{

		cout << "Area already existed. Please use the modify area option to change the existing area, or try again with a different area number";

		return 0;

	}



	/* Altitude */

	cout << "\n";

	alt = GetValidInputInteger("Altitude: ", "Invalid entry!", DataLimits::altitude_min, DataLimits::altitude_max);



	/* Vegetation */

	cout << "\n";

	vegetation = GetValidInputInteger("Vegetation (integer 1 to 3): ", "Invalid entry!", DataLimits::vegetation_min, DataLimits::vegetation_max);



	/* Terrain */

	cout << "\n";

	terrain = GetValidInputInteger("Terrain (integer 1 to 100): ", "Invalid entry!", DataLimits::terrain_min, DataLimits::terrain_max);



	/* Location */

	int x = GetValidInputInteger("Location x (integer 0000 to 9999): ", "Invalid entry!", 0, 9999);

	loc.x = ConvertToStr(x);



	int y = GetValidInputInteger("Location y (integer 0000 to 9999): ", "Invalid entry!", 0, 9999);

	loc.y = ConvertToStr(y);



	/* POA */

	cout << "\n";

	POA = GetValidInputFloat("POA (float 0 to 100): ", "Invalid entry!", DataLimits::POA_min, DataLimits::POA_max);



	/* Travel Time */

	cout << "\n";

	traveltime = GetValidInputInteger("Travel Time: ", "Invalid entry!", DataLimits::travelTime_min, DataLimits::travelTime_max);



	/* boundaries */

	//cout << "\nBoundaries Format: ((5560/8320)(5590/8320)(5560/8330)(5590/8330))";

	// Some error checking here is essential !

	//cin >> boundries;

	//StripWhite(boundries);



	while (1)

	{

		if (ReadFourPointArea(number, boundries, true))

		{

			break;

		}

		else

		{

			error_manager->PostError(WARNING, "That is not a valid rectangle", "BigArea::modifyArea() an invalid rectangle was specified");

			return 0;

		}

	}





	addArea(number, loc, boundries, traveltime, alt, terrain, vegetation, POA);

	return 1;

}



/******************************************************************************

 * MenuModifyArea()

 *

 * Michael Eldridge

 *

 * Finds the area and starts to modify it.

 */



int BigArea::MenuModifyArea()

{

	int number;



	cout << "\n";

	number = GetValidInputInteger("Enter number of area to modify: ", "Invalid Entry!", DataLimits::areaNum_min, DataLimits::areaNum_max);

	if (isArea(number))

	{

		modifyArea(number);

		return 1;

	}

	else

	{

		cerr << "There is no Area with that Area Number\n";

		return 0;

	}

}



/******************************************************************************

 * menu()

 *

 * Menu for user access to areas.

 * NB: Test is very similar.

 *

 * Author : Andre Oboler

 */



int BigArea::menu(void)

{

	//int var;

	int choice=-1;

	int number; // area user selected

	ofstream outfile;

	Area testarea;

	UTM loc;

	loc.x="1843";

	loc.y="2232";

	/*

	cout << "Running in test mode\n";

	cout << "testing set functions\n";

	testarea.setNumber(55);

	testarea.setLocation(loc);

	testarea.setTerrain(7);

	testarea.setAltitude(56);

	testarea.setVegetation(76);

	testarea.setPOA(5);



	cout <<"testing insertfunction\n";

	insert(testarea);



	loc.x="300";

	loc.y="700";

	cout << "testing addArea function\n";

	//addArea(56,loc,22,66,3,2,5);

	cout << "Done. 2 Areas created.\n"; */



	while (choice !=0)

	{

		cout << "\n***************\n";

		cout <<   "** Area Menu **\n";

		cout <<   "***************\n\n";

		cout << "1) Modify an Area\n";

		cout << "2) Add a new Area\n";

		cout << "3) Delete an Area\n";

		cout << "4) View an Area\n";

		cout << "5) Print Map\n";

		//cout << "6) Find Area\n";

		//cout << "7) Exists Area ?\n";

		cout << "6) Load Areas from file\n";

		cout << "7) Save Areas to file\n";

		cout << "8) Normalise POA's\n";

		//cout << "9) checks to see total POA is valid\n";

		cout << "\n0) Main Menu\n";

		cin >> choice;

		if (choice <0 || choice > 8)

			choice = -1;



		if (choice==0)

			return 1;

		else if (choice==1)

		{

			MenuModifyArea();

			/*

			cout << "\nEnter number of area to modify: ";

			cin >> number;

			number=findArea(number); // Changes number from Area to its index

			modifyArea(number);*/

		}

		else if (choice==2)

		{

			MenuNewArea();

			/*testarea.setNumber(-1);

			loc.x="0";

			loc.y="0";

			testarea.setLocation(loc);

			testarea.setTerrain(-1);

			testarea.setAltitude(-1);

			testarea.setVegetation(-1);

			testarea.setPOA(-1);



			cout << "\nDummy record created, press y to modify it and add real values\n";

			insert(testarea);

			//modifyArea(count()-1);

			modifyArea(area[count()-1].getNumber());*/

		}

		else if (choice==3)

		{

			cout << "\nEnter number of area to delete: ";

			cin >> number;

			MenuDeleteArea(number);

			/*

// NOTE : this code can probably go!!

			number=findArea(number); // Changes number from Area to its index

			deleteArea(number);*/

		}

		else if (choice==4)

		{

			MenuView();

			/*cout << "\nEnter number of area to View: ";

			cin >> number;

			//number=findArea(number); // Changes number from Area to its index

			viewArea(number);*/

		}

		else if (choice==5)

		{

			MenuMap();/*

			cout << "\n(1) map showing POA's\n(2) graphical POA density map\n(3) both\n";

			cout << "Enter map prefference: ";

			cin >> choice;

			if (choice==1)

				printmap();

			else if (choice==2)

				printsymbolmap();

			else

			{

				printmap();

				printsymbolmap();

			}*/



		}/*

		else if (choice==6)

		{

			cout << "\nEnter number of area to find its possition: ";

			cin >> number;

			cout << "possition is: " << findArea(number);

		}

		else if (choice==7)

		{

			cout << "\nEnter number of area to see if it exists: ";

			cin >> number;

			if (isArea(number))

			{

				cout << "\nNope. That area doesn't exist";

			}

			else

			{

				cout << "Yip. It exists";

			}

		}*/

		else if (choice==6)

		{

			MenuLoad();

			/*cout << "\nEnter name of file to load (eg area.dat): ";

			cin >> filename;

			loadAreas(filename);*/



		}

		else if (choice==7) // This code changed to take stream rather than name. Then started crashing when menu returns.

		{

			MenuSave();

			/*cout << "\nEnter name of file to save (eg area.dat): ";

			cin >> filename;*/

			// This

			/*outfile.open(filename);

			getAreas(outfile);

			outfile.close();*/

			// Or this. Not both.

			/*getAreas(filename);*/

		}



		else if (choice==8)

		{

			Normalise();

		}

		else

		{

			cout << "\nInvalid input. Please choose an option from the menu.";

		}

		choice = -1;

	}

	return 1;

}



/*************/

/******************************************************************************

 * INSERT_FUNCTION_NAME()

 *

 * Maintence and testing menu for BigArea and Area classes

 * An addaption of this might be useful to the user

 * to modify areas on the fly

 *

 * Author : Andre Oboler

 */



int BigArea::test()

{

	//int var;

	int choice=-1;

	int number; // area user selected

	string filename;

	Area testarea;

	UTM loc;

	loc.x="1843";

	loc.y="2232";

	/*

	cout << "Running in test mode\n";

	cout << "testing set functions\n";

	testarea.setNumber(55);

	testarea.setLocation(loc);

	testarea.setTerrain(7);

	testarea.setAltitude(56);

	testarea.setVegetation(76);

	testarea.setPOA(5);



	cout <<"testing insertfunction\n";

	insert(testarea);



	loc.x="300";

	loc.y="700";

	cout << "testing addArea function\n";

	addArea(56,loc,22,66,3,2,5);

	cout << "Done. 2 Areas created.\n"; */



	while (choice !=0)

	{

		cout << "\n**********\n";

		cout << "** Menu **\n";

		cout << "**********\n\n";

		cout << "1) Modify an Area\n";

		cout << "2) Add a new Area\n";

		cout << "3) Delete an Area\n";

		cout << "4) View an Area\n";

		cout << "5) Print Map\n";

		cout << "6) Find Area\n";

		cout << "7) Exists Area ?\n";

		cout << "8) Load from file\n";

		cout << "9) isValid checks to see total POA is valid\n";

		cout << "\n0) Exit\n";

		cin >> choice;

		if (choice <0 || choice > 9)

			choice = -1;



		if (choice==0)

			return 1;

		else if (choice==1)

		{

			cout << "\nEnter number of area to modify: ";

			cin >> number;

			number=findArea(number); // Changes number from Area to its index

			modifyArea(number);

		}

		else if (choice==2)

		{

			testarea.setNumber(-1);

			loc.x="0";

			loc.y="0";

			testarea.setLocation(loc);

			testarea.setTerrain(-1);

			testarea.setAltitude(-1);

			testarea.setVegetation(-1);

			testarea.setPOA(-1);



			cout << "\nDummy record created, press y to modify it and add real values\n";

			insert(testarea);

			modifyArea(count()-1);

		}

		else if (choice==3)

		{

			cout << "\nEnter number of area to delete: ";

			cin >> number;

			number=findArea(number); // Changes number from Area to its index

			deleteArea(number);

		}

		else if (choice==4)

		{

			cout << "\nEnter number of area to View: ";

			cin >> number;

			number=findArea(number); // Changes number from Area to its index

			viewArea(number);

		}

		else if (choice==5)

		{

			cout << "\n(1) map showing POA's\n(2) graphical POA density map\n(3) both\n";

			cout << "Enter map prefference: ";

			cin >> choice;

			if (choice==1)

				printmap();

			else if (choice==2)

				printsymbolmap();

			else

			{

				printmap();

				printsymbolmap();

			}



		}

		else if (choice==6)

		{

			cout << "\nEnter number of area to find its possition: ";

			cin >> number;

			cout << "possition is: " << findArea(number);

		}

		else if (choice==7)

		{

			cout << "\nEnter number of area to see if it exists: ";

			cin >> number;

			if (isArea(number))

			{

				cout << "\nNope. That area doesn't exist";

			}

			else

			{

				cout << "Yip. It exists";

			}

		}

		else if (choice==8)

		{

			cout << "\nEnter name of file to load (eg area.dat): ";

			cin >> filename;

			loadAreas(filename);

		}

		else if (choice==9)

		{

			isValid();

		}

		else

		{

			cout << "\nInvalid input. Please choose an option from the menu.";

		}

		choice = -1;

	}

	return 1;

}



/******************************************************************************

 * printmap()

 *

 * Basic map printing

 *

 * Author : Andre Oboler

 */



bool BigArea::printmap(void)

{

	int i=0;

//	vector<Area>::iterator current;

//	current=area.begin();



	// needs more work re: formating

	cout << "\n\nPOA for all areas\n";

	cout << "=================\n";

	while (i<= sqrt((float) count() - 2))

	{

		printf("|%4d  ", i);

		i++;

	}

	i=1;

	cout << "|\n";

	while (i < count()-1)

	{

		if (i % (int) sqrt((float)count() - 2) == 1)

		{

			printf ("|%4d  ", 1+ i / (int) sqrt((float) count() - 2));

		}

		if (isArea(i))

		{

			if (area[findArea(i)].getPOA() < 10)

				printf ("|0%2.3f", area[findArea(i)].getPOA());

			else

				printf ("|%2.3f", area[findArea(i)].getPOA());

		}

		else

		{

			cout << "| ?  ";

		}

		if (i % (int) sqrt((float) count() - 2) == 0)

		{

			cout << "|\n";

		}

		//cout << "[" << i << "]" << area[i].getPOA() << "\n";

		i++;

	}

	if (isArea(-2))

	{

		cout << "\nBase camp has a POA of: " << area[findArea(-2)].getPOA();

	}

	if (isArea(-1))

	{

		cout << "\nRest of world has a POA of: " << area[findArea(-1)].getPOA() << "\n";

	}

	//cout << "the map !";

	return 1;

}



/******************************************************************************

 * printsymbolmap()

 *

 * ASCII art map printing

 *

 * Author : Andre Oboler

 */



bool BigArea::printsymbolmap()

{

	int i=0;

	float val;

	string shallcontinue;

	const char low= char(176);

	const char medium=char(177);

	const char high=char(178);

	const int lowval=10;

	const int mediumval=20;

	// needs more work re: formating

	cout << "\n\nPOA density\n";

	cout <<     "===========\n";

	while (i<= sqrt((float)count() - 2))

	{

		printf("%2d", i);

		i++;

	}

	cout << "\n";

	i=1;

	while (i < count()-1)

	{

		if (isArea(i))

		{

			if (i % (int) sqrt((float)count() - 2) == 1)

			{

				printf ("%2d", 1+ i / (int) sqrt((float)count() - 2));

			}

			val = area[findArea(i)].getPOA();

			if (val < lowval)

			{

				cout << low << low;

			}

			else if (val < mediumval)

			{

				cout << medium << medium;

			}

			else

			{

				cout << high << high;

			}

		}

		else

		{

			cout << "?";

		}

		if (i % (int) sqrt((float)count() - 2) == 0)

		{

			cout << "\n";

		}

		//cout << "[" << i << "]" << area[i].getPOA() << "\n";

		i++;

	}

	if (isArea(-2))

	{

		cout << "\nBase camp has a POA of: " << area[findArea(-2)].getPOA();

	}

	if (isArea(-1))

	{

		cout << "\nRest of world has a POA of: " << area[findArea(-1)].getPOA() << "\n";

	}

	//cout << "the map !";

	cout << "\n\nKey:\n====\n";

	cout << low << "less than " << lowval << "\n";

	cout << medium << " " << lowval << " to " << mediumval << "\n";

	cout << high << " above " << mediumval << "\n";

	cout << "\nContinue ?\n";

	cin >> shallcontinue;



	return 1;

}





/******************************************************************************

 * insert()

 *

 * Insert a copy of an existing area into the vector

 *

 * Author : Andre Oboler

 */



bool BigArea::insert(BigArea::Area temp)

{

	area.push_back(temp);

	//cout << "added !";

	return 1;

}



/******************************************************************************

 * addArea()

 *

 * Create a new area in the vector based on data

 *

 * If accepting a UTM vector for boundary, would be: "vector<UTM> &boundries"

 *

 * Author : Andre Oboler

 */



bool BigArea::addArea(int number, UTM location, string boundries, int traveltime, int alt, int terrain, int vegetation, float POA)

{

	float length=0;

	float width=0;

	float thesize=0;

	string firstx;

	string secondx;

	string firsty;

	string secondy;



	Area temp;

	temp.setAltitude(alt);

	temp.setLocation(location);

	temp.setNumber(number);

	temp.setPOA(POA);



	if(temp.setBoundaries(boundries) == false)

	{

		error_manager->PostError(WARNING, "Boundaries could not be set. Boundaries points need to define a square. Area Ignored.", "setBoundaries returned false to addArea");

		return false;

	}

	if (calcSize(&temp)==false)

	{

		error_manager->PostError(WARNING, "Size could not be calculated Area ignored.", "calcSize returned false to addArea");

		return false;

	}



	/* Caluclate size and store it *//* Now handled by calcSize

	firstx  = (temp.boundaries[1].x).substr(0,2);

	secondx = (temp.boundaries[0].x).substr(0,2);

	firsty  = (temp.boundaries[2].y).substr(0,2);

	secondy = (temp.boundaries[1].y).substr(0,2);

	length=atof(firstx.c_str())-atof(secondx.c_str());

	width=atof(firsty.c_str())-atof(secondy.c_str());



	firstx  = (temp.boundaries[1].x).substr(2,2);

	secondx = (temp.boundaries[0].x).substr(2,2);

	firsty  = (temp.boundaries[2].y).substr(2,2);

	secondy = (temp.boundaries[1].y).substr(2,2);

	length=length + 0.01 * (atof(firstx.c_str())-atof(secondx.c_str()));

	width = width + 0.01 * (atof(firsty.c_str())-atof(secondy.c_str()));

	//length=((area[findArea(number)].boundaries[1].x[0]*10) + (area[findArea(number)].boundaries[1].x[0])) - ((area[findArea(number)].boundaries[0].x[0]*10) + (area[findArea(number)].boundaries[0].x[0]));

	//width =((area[findArea(number)].boundaries[2].y[0]*10) + (area[findArea(number)].boundaries[2].y[0])) - ((area[findArea(number)].boundaries[1].y[0]*10) + (area[findArea(number)].boundaries[1].y[0]));

	//length=(atof((area[findArea(number)].boundaries[1].x.substr(0,2)).c_str()))-(atof((area[findArea(number)].boundaries[0].x.substr(0,2)).c_str()));

	//width= (atof((area[findArea(number)].boundaries[2].y.substr(0,2)).c_str()))-(atof((area[findArea(number)].boundaries[1].y.substr(0,2)).c_str()));

	thesize=length*width;

	temp.setSize(thesize);

	*/

	//temp.setSize(size); //out of date.

	temp.setTraveltime(traveltime);

	temp.setTerrain(terrain);

	temp.setVegetation(vegetation);



	area.push_back(temp);

	return true;

}



/******************************************************************************

 * calcSize(area* temp)

 *

 * Takes a pointer to an existing area, accesses it's boundry points,

 * Sets the area's size

 *

 * NB: Precondition: Area must have boundaris in correct order.

 * Post consition: Size will be set to some value greater than 0.

 *

 * Author : Andre Oboler

 * Bug Fix: 14/6/01 (functioned added, code moved from add area).

 */





bool BigArea::calcSize(BigArea::Area *temp)

{

	float length=0;

	float width=0;

	float thesize=0;

	string firstx;

	string secondx;

	string firsty;

	string secondy;



	firstx  = (temp->boundaries[1].x).substr(0,2);

	secondx = (temp->boundaries[0].x).substr(0,2);

	firsty  = (temp->boundaries[2].y).substr(0,2);

	secondy = (temp->boundaries[1].y).substr(0,2);

	length=atof(firstx.c_str())-atof(secondx.c_str());

	if (length <= 0)

	{

		error_manager->PostError(WARNING, "Area has a length less than 1 km. Area Number: "+ConvertToStr(temp->getNumber())+". ", "calcSize could not set: length=firstx.c_str())-atof(secondx.c_str())");

		/* return false;*/ // Do not return false as it may still be valid. If it isn't, it will be caught below anyway */

	}

	width=atof(firsty.c_str())-atof(secondy.c_str());

	if (width <= 0)

	{

		error_manager->PostError(WARNING, "Area has a width less than 1km. Area Number: "+ConvertToStr(temp->getNumber())+". ", "atof(firsty.c_str())-atof(secondy.c_str())");

		/*return false;*/ //Do not return false as it may still be valid. If it isn't, it will be caught below anyway

	}

	firstx  = (temp->boundaries[1].x).substr(2,2);

	secondx = (temp->boundaries[0].x).substr(2,2);

	firsty  = (temp->boundaries[2].y).substr(2,2);

	secondy = (temp->boundaries[1].y).substr(2,2);



	length=length + 0.01 * (atof(firstx.c_str())-atof(secondx.c_str()));

	if (length <= 0)





	{

		error_manager->PostError(WARNING, "Area has a length < 0  Area Number: " + ConvertToStr(temp->getNumber())+". ", "Line: length=length + 0.01 * (atof(firstx.c_str())-atof(secondx.c_str()))");

		return false;

	}

	width = width + 0.01 * (atof(firsty.c_str())-atof(secondy.c_str()));

	if (width <= 0)

	{

		error_manager->PostError(WARNING, "Area has a width < 0  Area Number: "+ConvertToStr(temp->getNumber())+". ", "Line: width = width + 0.01 * (atof(firsty.c_str())-atof(secondy.c_str()));");

		return false;

	}

	thesize=length*width;


	//cout << "size = ";

	//cout << thesize;



	if (temp->setSize(thesize)==false)

	{

		error_manager->PostError(WARNING, "Area would not allow size to be changed", "setSize returned false to calcSize");

		return false;

	}

	return true;

}

/********************/



/******************************************************************************

 * modifyArea()

 *

 * Modify existing area, also used by new which creates a dummy area

 * and then ask the user to modify it

 *

 * Takes: Area Number

 * Author : Andre Oboler

 */



bool BigArea::modifyArea(int number)

{

	string confirm="j";

	viewArea(number);

	int index = findArea(number); // conver number from Area Number to reference.

	string s = "Are you sure you wish to modify this area?";



	if (GetResponce(s))

	{

		int newnumber;

		string newstring;

		char cont='y';

		UTM newUTM;

		float newPOA;



		// Do modify stuff

		cout << "Please enter new data\n";

		cout << "*********************\n";



		/* Area Number */

		cout << "\n";

		do

		{

			newnumber = GetValidInputInteger("Area Number (integer 1-100, -1 or -2) : ", "Invalid Entry!", DataLimits::areaNum_min, DataLimits::areaNum_max);



			if (newnumber == 0)

			{

				cout << "Invalid entry!\n";

			}

		} while (newnumber == 0);



		area[index].setNumber(newnumber);



		/* Altitude */

		cout << "\n";

		newnumber = GetValidInputInteger("Altitude: ", "Invalid Entry!", DataLimits::altitude_min, DataLimits::altitude_max);



		area[index].setAltitude(newnumber);



		/* Vegetation */

		cout << "\n";

		newnumber = GetValidInputInteger("Vegetation (integer 1 to 3): ", "Invalid Entry!", DataLimits::vegetation_min, DataLimits::vegetation_max);



		area[index].setVegetation(newnumber);



		/* Terrain */

		cout << "\n";

		newnumber = GetValidInputInteger("Terrain (integer 1 to 100): ", "Invalid Entry!", DataLimits::terrain_min, DataLimits::terrain_max);



		area[index].setTerrain(newnumber);



		/* POA */

		cout << "\n";

		newPOA = GetValidInputFloat("POA (floating point number 0 to 100): ", "Invalid Entry!", DataLimits::POA_min, DataLimits::POA_max);



		area[index].setPOA(newPOA);



		/* Travel Time */

		cout << "\n";

		newnumber = GetValidInputInteger("Travel Time: ", "Invalid Entry!", DataLimits::travelTime_min, DataLimits::travelTime_max);



		area[index].setTraveltime(newnumber);



		/* Location */

		int x = GetValidInputInteger("Location x (integer 0000 to 9999): ", "Invalid entry!", 0, 9999);

		newUTM.x = ConvertToStr(x);



		int y = GetValidInputInteger("Location y (integer 0000 to 9999): ", "Invalid entry!", 0, 9999);

		newUTM.y = ConvertToStr(y);



		area[index].setLocation(newUTM);



		/* boundaries */

		string temp_string;



		while (1)

		{

			if (ReadFourPointArea(index, temp_string, true))

			{

				break;

			}

			else

			{

				error_manager->PostError(WARNING, "That is not a valid rectangle", "BigArea::modifyArea() an invalid rectangle was specified");

				return false;

			}

		}





		/********  AO addition 14/6/01 ***********/

		if(area[index].setBoundaries(temp_string) == false)

		{

			error_manager->PostError(WARNING, "Boundaries could not be set. Boundaries points need to define a square. Area Ignored.", "setBoundaries returned false to addArea");

			return false;

		}

		if (calcSize(&area[index])==false)

		{

			error_manager->PostError(WARNING, "Size could not be calculated Area ignored.", "calcSize returned false to addArea");

			return false;

		}

		/******** End addition **********/

		return 1;

	}

	else

	{

		//cout << "Modify command not confirmed\nModification cancelled\n";

		return 1;

	}

	return 0;

}



/******************************************************************************

 * deleteArea()

 *

 * Remove an area from the list

 * In: an area number

 *

 * Author : Andre Oboler

 */



bool BigArea::deleteArea(int number)

{

	int index;

	index = findArea(number);



	if (isArea(number))

	{

		cout << "Deleted area "<< number << "\n";

		area.erase(area.begin() + index); // 12/1/03 ASO changed from area.erase(&area[index]) .. which didn't work under gcc 3.1.1

		return true;

	}

	else

	{

		error_manager->PostError(WARNING, "There is no Area with Area Number "+ConvertToStr(number)+".  Area could not be deleted.", "BigArea::deleteArea() - isArea(number) returned false.");

		return false;

	}



}



/******************************************************************************

 * viewArea()

 *

 * Show stored data about an area

 * In: An area number

 *

 * Author : Andre Oboler

 */



bool BigArea::viewArea(int number)

{

	//cout << "Number: " << number << "   count: " << count();

	int in=0;

	if (!isArea(number))

	{

		cout << "\nArea doesn't exist\n";

		return false;

	}

	number = findArea(number); // conver number from Area Number to reference.



	cout << "\nViewing area: "<< area[number].getNumber() << "\n";

	cout <<   "*****************\n";

	cout << "Number: " << area[number].getNumber() << "\n";

	cout << "Altitude: " <<  area[number].getAltitude() << "\n";

	cout << "Center Location: " << area[number].getLocation().x << "," << area[number].getLocation().y << "\n";

	cout << "Boundary Points: \n";

	for (in=0; in< area[number].boundaries.size(); in++)

	{

		cout << "    Point [" << in + 1 << "]";

		cout << area[number].boundaries[in].x;

		cout << ",";

		cout << area[number].boundaries[in].y;

		cout << "\n";

	}

	//////////while (

	cout << "Terrain: " <<  area[number].getTerrain() << "\n";

	cout << "Vegitation: " <<  area[number].getVegetation() << "\n";

	cout << "Size: " <<  area[number].getSize() << "\n";

	cout << "POA: " <<  area[number].getPOA() << "\n";

	cout << "Travel Time: " <<  area[number].getTraveltime() << "\n";

	return true;

}



/******************************************************************************

 * loadAreas()

 *

 * Load data from file. Should be called on program start up.

 *

 * Author : Andre Oboler / Gareth Thompson

 */



bool BigArea::loadAreas(string filename)

{

	if (testmode) cout << "entering BigArea::loadAreas(" << filename << ")\n";



	InputFile in;

	string record;



	/* Check if file can be opened */

	if (!in.open(filename))

	{

		error_manager->PostError(WARNING_OPTION, "File "+filename+" could not be opened.  No areas data loaded.", "BigArea::loadAreas() - in.open(filename) returned false.");

		return false;

	}



	while (in.getRecord(record))

	{

		if (testmode) cout << "record: " << record <<"\n";



		/* Tokenise record read from file at commas */

		vector<string> data = Tokenise(record, ',');



		/* Strip leading and trailing whitespace from each token */

		data = StripWhite(data);



		if (testmode)

		{

			cout << "SPLIT RECORD: ";

			PrintStringVector(data);

		}



		if (data.size() != 8)

		{

			/* Incorrect number of tokens in this record */

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - This line does not have 8 pieces of data specified.  Area ignored.", "BigArea::loadAreas() - Less or more than 8 comma-separated tokens on line of file.");

			continue;

		}



		/* Correct number of tokens in this record */



		/* Check if first piece of data is a valid Area Number */

		if (!IsInt(data[0]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Area Number "+data[0]+" is not a valid integer.  Area ignored.", "BigArea::loadAreas() - data[0] does not contain a valid integer.");

			continue;

		}



		int areaNum = atoi(data[0].c_str());

		if (areaNum < DataLimits::areaNum_min || areaNum > DataLimits::areaNum_max || areaNum == 0)

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Area Number "+data[0]+" is not between "+ConvertToStr((int) DataLimits::areaNum_min)+" and "+ConvertToStr((int) DataLimits::areaNum_max)+" or is 0.  Area ignored.", "BigArea::loadAreas() - data[0] does not contain a valid Area Number.");

			continue;

		}



		if (isArea(areaNum))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - There is already an Area with Area Number "+ConvertToStr(areaNum)+".  Area ignored.", "BigArea::loadAreas() - isArea(areaNum) returned false.");

			continue;

		}



		/* Check if second piece of data is a valid UTM coordinate pair */



		/* Check for leading/trailing brackets and remove them */

		string utmString;

		if (data[1][0] == '(' && data[1][data[1].size()-1] == ')')

		{

			utmString = data[1].substr(1, data[1].size()-2);

		}

		else

		{

			/* No leading / trailing brackets present */

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Locations coordinate pair is not correctly parenthesised.  Area ignored.", "BigArea::loadAreas() - data[1] does not have leading and trailing brackets");

			continue;

		}



		/* Tokenise correction string at '/' to split into x and y parts */

		vector<string> coordinates = Tokenise(utmString, '/');



		/* Check that there are exactly two parts (x and y) specified */

		if (!(coordinates.size() == 2))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Location "+data[1]+" does not have two parts.  Area ignored.", "BigArea::loadAreas() - less or more than 2 / separated tokens in a location (UTM).");

			continue;

		}



		/* Check that x part is exactly 4 digits */

		bool validCoordinate = false;

		if (coordinates[0].size() == 4)

		{

			validCoordinate = true;



			int i;

			for (i=0; i<4; i++)

			{

				if (coordinates[0][i] < '0' && coordinates[0][i] > '9')

				{

					validCoordinate = false;

				}

			}

		}



		if (!validCoordinate)

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - x-part "+coordinates[0]+" of location is not 4 digits.  Area ignored.", "BigArea::loadAreas() - coordinates[0] does not have size 4 or contains a character that is not a digit.");

			continue;

		}





		/* Check that y part is exactly 4 digits */

		validCoordinate = false;

		if (coordinates[1].size() == 4)

		{

			validCoordinate = true;



			int i;

			for (i=0; i<4; i++)

			{

				if (coordinates[1][i] < '0' && coordinates[1][i] > '9')

				{

					validCoordinate = false;

				}

			}

		}



		if (!validCoordinate)

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - y-part "+coordinates[1]+" of location is not 4 digits.  Area ignored.", "BigArea::loadAreas() - coordinates[1] does not have size 4 or contains a character that is not a digit.");

			continue;

		}



		/* Store coordinates in a UTM */

		UTM loc;

		loc.x = coordinates[0];

		loc.y = coordinates[1];



		/* Check if third piece of data contains valid polygon boundaries */

		string boundaries = data[2];

		if (!ReorderUTMString(boundaries))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Polygon boundaries "+boundaries+" are invalid.  Area ignored.", "BigArea::loadAreas() - ReorderUTMString(boundaries) returned false.");

			continue;

		}



		/* Check if 4th piece of data is a valid travel time */

		if (!IsInt(data[3]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Travel time "+data[3]+" is not a valid integer.  Area ignored.", "BigArea::loadAreas() - data[3] does not contain a valid integer.");

			continue;

		}



		int travelTime = atoi(data[3].c_str());

		if (travelTime < DataLimits::travelTime_min || travelTime > DataLimits::travelTime_max)

		{

			error_manager->PostError(WARNING, "File "+filename+" line"+ConvertToStr(in.lastRecLine())+" - Travel Time "+data[3]+" is not between "+ConvertToStr((int) DataLimits::travelTime_min)+" and "+ConvertToStr((int) DataLimits::travelTime_max)+".  Area ignored.", "BigArea::loadAreas() - data[3] does not contain a valid Travel Time.");

			continue;

		}



		/* Check if 5th piece of data is a valid altitude */

		if (!IsInt(data[4]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Altitude "+data[4]+" is not a valid integer.  Area ignored.", "BigArea::loadAreas() - data[4] does not contain a valid integer.");

			continue;

		}



		int altitude = atoi(data[4].c_str());

		if (altitude < DataLimits::altitude_min || altitude > DataLimits::altitude_max)

		{

			error_manager->PostError(WARNING, "File "+filename+" line"+ConvertToStr(in.lastRecLine())+" - Altitude "+data[4]+" is not between "+ConvertToStr((int) DataLimits::altitude_min)+" and "+ConvertToStr((int) DataLimits::altitude_max)+".  Area ignored.", "BigArea::loadAreas() - data[4] does not contain a valid Altitude value.");

			continue;

		}



		/* Check if 6th piece of data is a valid terrain */

		if (!IsInt(data[5]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Terrain "+data[5]+" is not a valid integer.  Area ignored.", "BigArea::loadAreas() - data[5] does not contain a valid integer.");

			continue;

		}



		int terrain = atoi(data[5].c_str());

		if (terrain < DataLimits::terrain_min || terrain > DataLimits::terrain_max)

		{

			error_manager->PostError(WARNING, "File "+filename+" line"+ConvertToStr(in.lastRecLine())+" - Terrain "+data[5]+" is not between "+ConvertToStr((int) DataLimits::terrain_min)+" and "+ConvertToStr((int) DataLimits::terrain_max)+".  Area ignored.", "BigArea::loadAreas() - data[5] does not contain a valid Terrain value.");

			continue;

		}



		/* Check if 7th piece of data is a valid vegetation */

		if (!IsInt(data[6]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - Vegetation "+data[6]+" is not a valid integer.  Area ignored.", "BigArea::loadAreas() - data[6] does not contain a valid integer.");

			continue;

		}



		int vegetation = atoi(data[6].c_str());

		if (vegetation < DataLimits::vegetation_min || vegetation > DataLimits::vegetation_max)

		{

			error_manager->PostError(WARNING, "File "+filename+" line"+ConvertToStr(in.lastRecLine())+" - Vegetation "+data[6]+" is not between "+ConvertToStr((int) DataLimits::vegetation_min)+" and "+ConvertToStr((int) DataLimits::vegetation_max)+".  Area ignored.", "BigArea::loadAreas() - data[6] does not contain a valid Vegetation value.");

			continue;

		}



		/* Check if 8th piece of data is a valid POA */

		if (!IsFloat(data[7]))

		{

			error_manager->PostError(WARNING, "File "+filename+" line "+ConvertToStr(in.lastRecLine())+" - POA "+data[7]+" is not a valid floating point number.  Area ignored.", "BigArea::loadAreas() - data[7] does not contain a valid floating point number.");

			continue;

		}



		double POA = atof(data[7].c_str());

		if (POA < DataLimits::POA_min || POA > DataLimits::POA_max)

		{

			error_manager->PostError(WARNING, "File "+filename+" line"+ConvertToStr(in.lastRecLine())+" - POA "+data[7]+" is not between "+ConvertToStr(DataLimits::POA_min)+" and "+ConvertToStr(DataLimits::POA_max)+".  Area ignored.", "BigArea::loadAreas() - data[7] does not contain a valid POA value.");

			continue;

		}



		/* Add Area to list */

		addArea(areaNum, loc, boundaries, travelTime, altitude, terrain, vegetation, POA);

	}



	return true;

}



/******************************************************************************

 * updatePOA()

 *

 * Replace existing POA with new POA as suplied

 *

 * Author : Andre Oboler

 */



bool BigArea::updatePOA(int number, float newPOA)

{

	int index = findArea(number);

	if (isArea(number))

	{

		area[index].setPOA(newPOA);

		return true;

	}

	else

		return false;

	//cout << "Updating POA to: "<< POA << "for area number: " << number

}



/******************************************************************************

 * getPOA()

 *

 * Returns the POA of an area

 *

 * Author : Andre Oboler

 */



float BigArea::getPOA(int number) // const float ?

{

	//cout << "showing POA for area number: " << number;

	int index = findArea(number);

	if (isArea(number))

	{

		return area[index].getPOA();

	}

	else

		return 0;



}



/******************************************************************************

 * getArea()

 *

 * Returns the data for all areas to a file

 *

 * Author : Andre Oboler

 */



bool BigArea::getAreas(string filename) // const float ?

{

	//OR bool BigArea::getAreas(ofstream outfile)

	//cout << "showing POA for area number: " << number;

	vector<int> list;

	//OR remove line below

	ofstream outfile;



	//OR remove line below

	outfile.open(filename.c_str());



	vector<Area>::iterator current;



	for (current = area.begin(); current != area.end(); current++)

	{

		outfile << current->DumpArea();

	}

	//OR remove line below

	outfile.close();

	return true;

}



/******************************************************************************

 * OutputAllAreas()

 *

 * Prints out all the current area details

 *

 * Author : Michael Eldridge

 */



void BigArea::OutputAllAreas(ostream &out)

{

	//OR bool BigArea::getAreas(ofstream outfile)

	//cout << "showing POA for area number: " << number;

	vector<int> list;

	//OR remove line below

	//ofstream outfile;



	//OR remove line below

	//outfile.open(filename.c_str());



	vector<Area>::iterator current;



	for (current = area.begin(); current != area.end(); current++)

	{

		out << current->DumpArea();

	}

	//OR remove line below

	//outfile.close();

}



/******************************************************************************

 * ReadFourPointArea()

 *

 * Michael Eldridge

 *

 * Function added to specifically load an area with four UTM co-ordinates

 * which define the area as a rectangle.

 */



// NOTE : needs finishing properly



bool BigArea::ReadFourPointArea(int area_index, string &s, bool return_string)

{

	int x[4];

	int y[4];

	int i;



	int combinations[12] = { 1,2, 1,3, 1,4, 2,3, 2,4, 3,4 };

	int pos = 0;



	if (testmode) { cout << "Entering Read4points..." << endl; }



	cout << endl << "Enter co-ordinates in UTM format ( 1234 = 12.34km )" << endl;



	for (i = 0 ; i < 4 ; i++)

	{

		x[i] = GetValidInputInteger("Enter x"+ConvertToStr(i+1)+" (0000 to 9999): ", "Invalid Entry!", 0, 9999);



		y[i] = GetValidInputInteger("Enter y"+ConvertToStr(i+1)+" (0000 to 9999): ", "Invalid Entry!", 0, 9999);

	}



	// Check that the co-ordinates are ok.



	for (i = 0 ; i < 6 ; i += 2)

	{

		if (x[combinations[i]] == x[combinations[i + 1]])

		{

			if (y[combinations[i]] == y[combinations[i + 1]])

			{

				pos++;

			}

		}

		else if (y[combinations[i]] != y[combinations[i + 1]])

		{

			pos++;

		}



		if (pos > 2)

			return false;

	}



	// format the co-ordinates



	string temp_string;



	if (!return_string)

	{

		area[area_index].boundaries.clear();



		for (i = 0 ; i < 4 ; i++)

		{

			UTM utm;

			temp_string = ConvertToStr(x[i]);

			utm.x = temp_string;

			temp_string = ConvertToStr(y[i]);

			utm.y = temp_string;

			area[area_index].boundaries.push_back(utm);

		}

	}



	s = MakeUTMString(x, y);

	if (s == "error")

	{

		error_manager->PostError(WARNING, "Could not make rectangle from those co-ordinates", "MakeUTMString failed. Area is not a rectangle.");

		return false;

	}



	return true;

}



/******************************************************************************

 * MakeUTMString()

 *

 * Michael Eldridge

 * Re written by: Andre Oboler 15/6/01

 *

 * Turn a a set of UTM values into a sting of UTM's

 */



/* Post condition: the value "error" or a valid value.

   Always, always, always trap for this funciton returning "error"

*/



string BigArea::MakeUTMString(int x[], int y[])

{

	int array[8];



	/* Case 1 */

	/* x1 == x2 */

	if (x[0] == x[1])

	{

		/* x3 == x4 */

		if (x[2] == x[3])

		{

			if (x[0] < x[2])

			{

				array[0] = x[0];

				array[4] = x[0];

				array[2] = x[2];

				array[6] = x[2];

			}

			else if (x[0] > x[2])

			{

				array[0] = x[2];

				array[4] = x[2];

				array[2] = x[0];

				array[6] = x[0];

			}

			else

			{

				return "error";

			}



		}

		/* x3 != x4 Fail */

		else

		{

			return "error";

		}

	}



	/* Case 2 */

	/* x1 == x3 */

	else if (x[0] == x[2])

	{

		/* x2 == x4 */

		if (x[1] == x[3])

		{

			/* where 0 < 1 */

			if (x[0] < x[1])

			{

				array[0] = x[0];

				array[4] = x[0];

				array[2] = x[1];

				array[6] = x[1];

			}

			else if (x[0] > x[1])

			{

				array[0] = x[1];

				array[4] = x[1];

				array[2] = x[0];

				array[6] = x[0];

			}

			else

			{

				return "error";

			}

		}

		/* x2 != x4  Fail */

		else

		{

			return "error";

		}

	}

	/* Case 3 */

	/* x1 == x4 */

	else if(x[0] == x[3])

	{

		/* x2 == x3 */

		if (x[1]== x[2])

		{

			if (x[0] < x[1])

			{

				array[0] = x[0];

				array[4] = x[0];

				array[2] = x[1];

				array[6] = x[1];

			}

			else if (x[0] > x[1])

			{

				array[0] = x[1];

				array[4] = x[1];

				array[2] = x[0];

				array[6] = x[0];

			}

			else

			{

				return "error";

			}

		}

		/* x2 != x3  Fail */

		else

		{

			return "error";

		}

	}



	/* Case 4 */

	/* x1 == none So Fail. */

	else

	{

		return "error";

	}



/**********  Y *************/

	/* Case 1 */

	/* y1 == y2 */

	if (y[0] == y[1])

	{

		/* y3 == y4 */

		if (y[2] == y[3])

		{

			if (y[0] < y[2])

			{

				array[1] = y[0];

				array[3] = y[0];

				array[5] = y[2];

				array[7] = y[2];

			}

			else if (y[0] > y[2])

			{

				array[1] = y[2];

				array[3] = y[2];

				array[5] = y[0];

				array[7] = y[0];

			}

			else

			{

				return "error";

			}



		}

		/* x3 != x4 Fail */

		else

		{

			return "error";

		}

	}



	/* Case 2 */

	/* y1 == y3 */

	else if (y[0] == y[2])

	{

		/* y2 == y4 */

		if (y[1] == y[3])

		{

			/* where 0 < 1 */

			if (y[0] < y[1])

			{

				array[1] = y[0];

				array[3] = y[0];

				array[5] = y[1];

				array[7] = y[1];

			}

			else if (y[0] > y[1])

			{

				array[1] = y[1];

				array[3] = y[1];

				array[5] = y[0];

				array[7] = y[0];

			}

			else

			{

				return "error";

			}

		}

		/* x2 != x4  Fail */

		else

		{

			return "error";

		}

	}

	/* Case 3 */

	/* y1 == y4 */

	else if (y[0] == y[3])

	{

		/* y2 == y3 */

		if (y[1]== y[2])

		{

			if (y[0] < y[1])

			{

				array[1] = y[0];

				array[3] = y[0];

				array[5] = y[1];

				array[7] = y[1];

			}

			else if (y[0] > y[1])

			{

				array[1] = y[1];

				array[3] = y[1];

				array[5] = y[0];

				array[7] = y[0];

			}

			else

			{

				return "error";

			}

		}

		/* y2 != y3  Fail */

		else

		{

			return "error";

		}

	}



	/* Case 4 */

	/* y1 == none So Fail. */

	else

	{

		return "error";

	}

/*********************/



	// ((5560/8320)(5590/8320)(5560/8330)(5590/8330))

	char temp_char[5];



	// check to see if the numbers are less than 1000 (is 4 digits).





	string string_array[8];



	temp_char[4] = '\0';

	for (int i = 0 ; i < 8 ; i++)

	{

		temp_char[0] = (array[i] / 1000) + 48;

		temp_char[1] = ((array[i] % 1000) / 100) + 48;

		temp_char[2] = ((array[i] % 100) / 10) + 48;

		temp_char[3] = ((array[i] % 10) / 1) + 48;



		string_array[i] = temp_char;

	}





	//sprintf(temp_char, "((%d/%d)(%d/%d)(%d/%d)(%d/%d))\0", array[0], array[1], array[2], array[3], array[4], array[5], array[6], array[7]);

	string s;

	s = "((" + string_array[0] + "/" + string_array[1] + ")(" + string_array[2] + "/" + string_array[3] + ")(" + string_array[4] + "/" + string_array[5] + ")(" + string_array[6] + "/" + string_array[7] + "))\0";

	return s;

}



/******************************************************************************

 * ReorderUTMString()

 *

 * Michael Eldridge

 *

 * Take a UTM string and make sure the UTM's are in the correct order

 */



bool BigArea::ReorderUTMString(string &utm)

{

	int x[4];

	int y[4];

	int i, j;



	char buffer[32];

	char utms[8][5];



	int pos = 0;

	int numbers_read = 0;



	if(utm.size() != 14 + 32)

	{

		return false;

	}



	for(i = 0 ; i < utm.size() ; i++)

	{

		if (utm[i] != '(' && utm[i] != ')' && utm[i] != '/')

		{

			buffer[pos++] = utm[i];

		}

	}



	pos = 0;

	for (i = 0 ; i < 8 ; i++)

	{

		for (j = 0 ; j < 4 ; j++)

		{

			utms[i][j] = buffer[pos++];

		}

		utms[i][j] = '\0';

	}



	x[0] = atoi(utms[0]);

	y[0] = atoi(utms[1]);

	x[1] = atoi(utms[2]);

	y[1] = atoi(utms[3]);

	x[2] = atoi(utms[4]);

	y[2] = atoi(utms[5]);

	x[3] = atoi(utms[6]);

	y[3] = atoi(utms[7]);



	utm = MakeUTMString(x, y);

	if (utm=="error")

	{

		return false;

	}



	return true;

}



/******************************************************************************

 * viewAllAreas()

 *

 * Prints details of all Areas to standard output in a table form.

 *

 * Author : Michael Eldridge

 */



void BigArea::ViewAllAreas(void)

{

	if (testmode) cout << "entering BigArea::ViewAllAreas()\n";



	/* Output headings for table */

	//cout << " \nNum   Type                               POD      ESW    Speed     Hours\n";

	///cout << "                                          (%)      (m)   (km/h)     Avail\n";

	//cout << "\n";



	printf("\n\n%4s %8s %10s %9s %12s %8s", "Area", "Size", "Altitude", "Terrain", "Vegetation", "POA");

	printf("\n===========================================================\n");

	/* Output details of each area*/

	vector<Area>::iterator current;

	for (current = area.begin(); current != area.end(); current++)

	{

		printf("%4d ", current->getNumber());

		printf("%8.4f ", current->getSize());

		printf("%8.1f ", current->getAltitude());

		printf("%9d ", current->getTerrain());

		printf("%9d ", current->getVegetation());

		printf("%15.4f\n", current->getPOA());

	}

}

