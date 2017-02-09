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
 * DataLimt.cpp
 *
 * Defines the upper and lower limits for all pieces of
 * data in the SAR program.
 *
 *-----+----------+-----+-----------------------------------------------------
 * Who |   When   | Ver | What
 *-----+----------+-----+-----------------------------------------------------
 * ?   |     ?    |  1  | Created. The header file noted that there was no cpp
 *     |          |     | file. This is obviously no longer true as this file
 *     |          |     | exists. ASO 7/3/08
 *----------------------------------------------------------------------------
 * AO  | 07/03/08 | 1.1 | Gareth altered copyright notice etc for release,
 *     |          |     | Andre updated version info and (c) date
 *----------------------------------------------------------------------------
 */

#include "DataLimt.h"

using namespace std;

const double DataLimits::POA_min = 0.0;
const double DataLimits::POA_max = 100.0;

const double DataLimits::POD_min = 0;
const double DataLimits::POD_max = 100;

const double DataLimits::ESW_min = 0;
const double DataLimits::ESW_max = FLOATMAXVAL;

const double DataLimits::speed_min = 0;
const double DataLimits::speed_max = FLOATMAXVAL;

const double DataLimits::correctionFactor_min = 0;
const double DataLimits::correctionFactor_max = 10;

