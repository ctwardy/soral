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
 * InputFil.cpp
 *
 * InputFile provides access to records from a given file
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * GT  | 02/04/01 |  1  | Created.
 *---------------------------------------------------------------------------- * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */
#include <iostream>
#include <fstream>
#include <string>
#include "InputFil.h"
#include "global.h"
using namespace std;
/******************************************************************************
 * open()
 *
 * Open specified file for input.
 * Returns true if file successfully opened.
 * Returns false if file not opened (there is a file currently open
 * in this InputFile object, or the specified file cannot be found).
 *
 * Author : Gareth Thompson
 */
bool InputFile::open(string filename)
{
	if (testmode) cout << "entering InputFile::open(" << filename << ")\n";
	if (myFile == 0)
	{
		/* No file currently open - open specified file */
		myFile = new ifstream(filename.c_str());
		if (*myFile)
		{
			/* File successfully opened */
			myLastRecLine = 0;
			return true;
		}
		else
		{
			/* File could not be opened */
			return false;
		}
	}
	else
	{
		/* File currently open - cannot open new file */
		return false;
	}
}

/******************************************************************************
 * close()
 *
 * Close the currently open file.
 * This function has no effect if there is no file currently open.
 *
 * Author : Gareth Thompson
 */
void InputFile::close(void)
{
	if (testmode) cout << "entering InputFile::close()\n";
	delete myFile;
	myFile = 0;
	myLastRecLine = 0;
}
/******************************************************************************
 * getRecord()
 *
 * Sets its argument to the next record in the currently open file.
 * (A record is a line from the file that is not blank and that does
 * not begin with # or %).
 * Returns true if the argument was successfully set to the next
 * record in the file.
 * Returns false if no file is currently open, or if there are no
 * more records in the current file.
 *
 * Author : Gareth Thompson
 */
bool InputFile::getRecord(string& record)
{
	if (testmode) cout << "entering InputFile::getRecord()\n";
	/* Cannot provide a record if no file open */
	if (myFile == 0) return false;
	string inputLine;
	int linesRead = 0;
	while (true)
	{
		if(!getline(*myFile, inputLine))
		{
			/* End of file reached - cannot provide a record */
			return false;
		}
		linesRead++;
		if (isRecord(inputLine))
		{
			/*
			 * This is the next record in the file.
			 * record is set to this value.
			 */
			record = inputLine;
			/*
			 * Record line number at which this record
			 * is read
			 */
			myLastRecLine += linesRead;
			return true;
		}
	}
}
/******************************************************************************
 * isRecord()
 *
 * Returns false if str is blank (contains only whitespace) or is
 * a comment line (first non-whitespace character is # or %).
 * Returns true otherwise (str is a valid record from a file).
 *
 * Author : Gareth Thompson
 */
bool InputFile::isRecord(string str)
{
	if (testmode) cout << "entering InputFile::isRecord(" << str << ")\n";
	/* strip whitespace from beginning and end of str */
	str = StripWhite(str);
	/* check if str is a valid record */
	if ( (str.size() > 0) && (str[0] != '#') && (str[0] != '%') )
	{
		return true;
	}
	else
	{
		return false;
	}
}
