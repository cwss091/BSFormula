#ifndef _CASHFLOW_H__
#define _CASHFLOW_H__

/* Calculate the present value of the interets which the security pays each quartar */

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
#include "getCMT.h"

double average(std::vector<double>& v); // Calculate the average of v
std::vector<double> ProbOverK(double K, double S0, double div_y, double vol, double expiry, bool call, double t, std::map<double, double> cmt_cur); // Probability of the index above K
void cfc_fix(const double& fixrate, std::vector<double>& v); // payment with fix rate quarterly
void cfc_float(std::vector<double>& v); // payment with float quarterly
double CFC(const double& vol, const double& S_index, const double& Barrier, const double& div_y, const double& expiry, std::map<double, double>inputcmt);

#endif
