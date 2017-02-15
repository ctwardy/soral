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
 * Areas.h
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

#ifndef _areas_h_
#define _areas_h_

using namespace std;

/* UTM maintained by Andre*/
struct UTMtype
{
	string x;
	string y;
};
typedef struct UTMtype UTM;
/* The UTM may be better if represented by 2 ints, not sure about this */

/*  bigArea (formerly map) maintained by Andre
	This Contains all the areas in the map     */
class BigArea
{
private:
	/* Area maintained by Andre
	   This class represents a clearly defined area on the search map
	   It is a private class of bigArea and my only be accessed through bigArea
	   as encapsulation allows.
	*/
	class Area
	{
		private:
			int number;
			UTM location;
			float size;
			int traveltime; // In minutes !
			float altitude;
			int terrain;
			int vegetation;
			float POA;
			/* float initPOA; ? */


		public:
			vector<UTM> boundaries;
			inline int			getNumber(void)		{ return number;	}
			inline UTM			getLocation(void)	{ return location;	}
			inline vector<UTM>	getBoundaries(void) { return boundaries;}
			inline float		getSize(void)		{ return size;		}
			inline int			getTraveltime(void) { return traveltime;}
			inline float		getAltitude(void)	{ return altitude;	}
			inline int			getTerrain(void)	{ return terrain;	}
			inline int			getVegetation(void) { return vegetation;}
			inline float		getPOA(void)		{ return POA;		}
			//inline void			clearUTMpoints(void){ boundaries.Clear(); }

			string DumpArea(void);
			bool setNumber(int newnumber);
			bool setLocation(UTM newlocation);
			bool setBoundaries(string boundariesString);
			bool setSize(float newSize);
			bool setTraveltime(int newTravelTime);
			bool setAltitude(int newaltitude);
			bool setTerrain(int newterrain);
			bool setVegetation(int newvegetation);
			bool setPOA(float newPOA);
	};

	vector <Area> area;

public:
	inline int count(void) { return area.size(); }
	inline void deleteAllAreas(void) { area.clear(); }

	int menu(void);
	int   findArea(int number);
	bool  isValid(void);
	bool  isArea(int number);
	int   test();
	bool  printmap();
	bool  printsymbolmap();
	bool  insert(Area temp);
	bool  addArea(int number, UTM location, string boundries, int traveltime, int alt, int terrain, int vegetation, float POA);
	// Old addArea from Assignment 1. /*bool  addArea(int number, UTM location, float size, int alt, int terrain, int vegetation, float POA);*/
	bool  modifyArea(int number);
	bool  calcSize(Area* temp);
	void  OutputAllAreas(ostream &out);
	bool  getAreas(string filename);
	bool  deleteArea(int number);
	bool  viewArea(int number);
	bool  loadAreas(string filename);
	bool  updatePOA(int number, float newPOA);
	float getPOA(int number);
	float getPden(int number);
	float getSize(int number);
	int getTerrain(int number);
	int getVegetation(int number);

	bool MenuDeleteArea(int AreaNum);
	int MenuExit();
	int MenuMap();
	int MenuLoad();
	int MenuSave();
	int MenuView();
	int MenuModifyArea();
	int MenuNewArea();

	void ViewAllAreas(void);

	bool ReadFourPointArea(int area_number, string &s, bool return_string);
	string MakeUTMString(int x[4], int y[4]);
	bool ReorderUTMString(string &utm);

	int Normalise();

	vector<int> getAreaNumList(void);
};

#endif


