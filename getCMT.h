#ifndef _GETCMT_H__
#define _GETCMT_H__

/*
 * Get the CMT data from the files downloaded from
 * http://www.federalreserve.gov/releases/h15/data.htm* 
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <map>
#include <numeric>
#include <utility>
#include "IO.h"
#include "LinearInterpolation.h"
#include "NormDistIntegral.h"
#include "BSE.h"

std::map<double, double> CMT_data();

#endif
