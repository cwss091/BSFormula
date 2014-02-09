/*
 * CashFlow.cpp
 * Calculate the present value of the interets which the security pays each quartar
 * Copyright @ Yuliang Li
 * GTID# 903012703
 */


#include "CashFlow.h"

using namespace std;

typedef double manurity;
typedef double rate;

vector<double> pv_cf;
const double pcp = 1000.0; // principal is define
const double disc_r = exp(-0.0544); // discounted rate
MyNormDist stdN(0.0, 1.0);

// Current value of cash flow
double CFC(const double& vol, const double& S_index, const double& Barrier, const double& div_y, const double& expiry, map<double, double> inputcmt)
{
	// The first year, pay interest with fixed rate of 12%
	double fix_r = 0.12;
	cfc_fix(fix_r, pv_cf);
	// After the 1st year, pay interest with float rate
	cfc_float(pv_cf);
	vector<double> LowP = ProbOverK(Barrier, S_index, div_y, vol, expiry, 1, 0, inputcmt); // the probability of index above 1008
	double Sum_cf = inner_product(pv_cf.begin(), pv_cf.end(), LowP.begin(), 0.0); //the Sum of cash flow
	pv_cf.erase(pv_cf.begin(), pv_cf.end());
	return Sum_cf;
}

double average(vector<double>& v) // Calculate the average of v
{
	double ave = 0;
	for(vector<double>::iterator j = v.begin(); j != v.end(); j++)
	{
		ave += *j;
	}
	ave = ave / v.size();
	return ave;
}
// Probability of the index above K after the first year
vector<double> ProbOverK(double K, double S0, double div_y, double vol, double expiry, bool call, double t, map<double, double> cmt_cur) 
{
	vector<double> prop;
	double quar = 0.25;
	double d2;
	
	while(quar <= 15.00)
	{
		if(quar <= 1.00)
		{
			prop.push_back(1.0);
		}
		else
		{
			BS_EuroOption Euro_Op(K, cmt_cur[quar] / 100.0, div_y, vol, quar, call, t);
			prop.push_back(stdN.Norm_cdf((Euro_Op.d_value(S0)).second));
		}
		quar += 0.25;
	}
	return  prop;
}


void cfc_fix(const double& fixrate, vector<double>& pay) // payment with fix rate quarterly
{
	double t;
	for(t = 0.25; t <= 1.00; t = t+0.25)
	{
		double intrpay = pcp * (exp(fixrate/4.0) - 1);
		intrpay = intrpay * pow(disc_r, t);
		pay.push_back(intrpay);
	}
}

void cfc_float(vector<double>& pay) // payment with float rate quarterly
{
	ifstream infile_30("./FRB_H15_Sw30.csv");
	if(!infile_30)
	{
		cout << "There is no document for 30 year swap rate" << endl;
	}
	vector<double> Sw_30 = get_data_H15(infile_30);

	ifstream infile_2("./FRB_H15_Sw2.csv");
	if(!infile_2)
	{
		cout << "There is no document for 2 year swap rate" << endl;
	}
	vector<double> Sw_2 = get_data_H15(infile_2);

	double float_r = 5.0 * (average(Sw_30) - average(Sw_2)) / 100.0;
	double t;
	for(t = 1.25; t <= 15.00; t = t+0.25)
	{
		double intrpay = pcp * (exp(float_r/4.0) - 1);
		intrpay = intrpay * pow(disc_r, t);
		pay.push_back(intrpay);
	}
}

