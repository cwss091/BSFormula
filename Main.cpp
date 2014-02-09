/* ISyE 6767 Project 1
 * Yuliang Li
 * GTID 903012703
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
#include "BondPrice.h"

#include "getCMT.h"
#include "CashFlow.h"

using namespace std;

// ForwardRate at some time
// r1 is the spot rate for long period, r2 is the spot rate for short period
// the greater one betweent t1 and t2 will be the long period;
double ForwardRate(double r1, double r2, double t1, double t2) 
{
	if(t1 < t2)
	{
		double temp = t2;
		t2 = t1;
		t1 = temp;
	}
	return (t1*r1 - t2*r2) / (t1 - t2);
}

int main()
{
	//input the file which includes spot price, strike price, barrier, rate, dividened yield, expirate date, volatility
	ifstream Input_para("./InputParameters.txt");
	if(!Input_para)
	{
		cout << "No parameters input file, please set your parameter file" << endl;
	}
	double spot_price; // the spot price
	double strike_price; // the strike price
	double div_y; // the dividened yield
	double RF_Rate; // the risk-free rate
	double expirate_data; // the expirate date
	double vol[2] = {0.0, 0.0}; // the volatility
	double barrier_sp;

	input_data(spot_price, strike_price, barrier_sp, RF_Rate, div_y, expirate_data, vol[0], vol[1], Input_para);
	cout << spot_price << " " << strike_price << " " << barrier_sp << " " << div_y << " " << RF_Rate << " " << expirate_data << " " << vol[0] << " " << vol[1] << endl;	

	map<double, double> cmt_itp = CMT_data(); // the CMT rate from the H15 website and interpolation

	double FR[3];
	FR[0] = cmt_itp[15.00] / 100.0; // the rate of 15 years at the formulation year

	FR[1] = ForwardRate(cmt_itp[15.00], cmt_itp[5.00], 15.00, 5.00) / 100.0; // the forward rate of 10 years at the fifth year
	FR[2] = ForwardRate(cmt_itp[15.00], cmt_itp[10.00], 15.00, 10.00) / 100.0; // the forward rate of 5 years at the 10th year


	double cfc[2] ={0}; // the cash flow

	fstream Port_price_cf; // open a file to record some results
	Port_price_cf.open("Portfolio_price_CF.txt", ios::out);
	Port_price_cf.close();

	for(int i = 0; i <= 1; i++)
	{
		// The price of a short Euro put option
		BS_EuroOption EuroShortProd(strike_price, RF_Rate, div_y, vol[i], expirate_data, 0, 0);
		double E_short_P = EuroShortProd(spot_price);
		// The price of a digital call option
		BS_DigiOption DigiCallProd(strike_price, RF_Rate, div_y, vol[i], expirate_data, 1, 0);
		double D_call_P = DigiCallProd(spot_price);
		// The price of a risk-free zero-coupon bond whose principal is 500
		double RZ_bond_P = zc_rs_bond(expirate_data, 500, RF_Rate);

		// output the unit price of the European put option, digital call option and the bond
		cout << " when the volatility is " << vol[i] << endl;
		cout << "the price of a unit European short option is " << E_short_P << endl;
		cout << "the price of a unit Digital call option is " << D_call_P << endl;
		cout << "the price of risk-free zero-coupon " << RZ_bond_P << endl;
		// the amount of left cash
		cout << "the cash left is " << 1000-(-500.0/840.0*E_short_P + 500 * D_call_P + RZ_bond_P) << endl;

		Port_price_cf.open("Portfolio_price_CF.txt", ios::out|ios::app);
		Port_price_cf << " when the volatility is " << vol[i] << endl;
		Port_price_cf << "the price of a unit European short option is " << E_short_P << endl;
		Port_price_cf << "the price of a unit Digital call option is " << D_call_P << endl;
		Port_price_cf << "the price of risk-free zero-coupon " << RZ_bond_P << endl;
		// the amount of left cash
		Port_price_cf << "the cash left is " << 1000-(-500.0/840.0*E_short_P + 500 * D_call_P + RZ_bond_P) << endl;
		Port_price_cf << endl;
		Port_price_cf.close();

		// the value of portfolio in the formulated year, the 5th yr and the 10th yr after generation
		double ex_d = 15.00; //the expirate date
		int j = 0;
		
		while(ex_d >= 5.00)
		{
			vector<double> p_value; // the values of portfolio
			vector<double> stockp; // the stock price

			double SP = 701.0; // index ranges
			while(SP < 1000.0)
			{
				stockp.push_back(SP);
				BS_EuroOption ES(strike_price, FR[j], div_y, vol[i], ex_d, 0, 0);
				BS_DigiOption DC(strike_price, FR[j], div_y, vol[i], ex_d, 1, 0);
				double Esvalue = ES(SP);
				double Dsvalue = DC(SP);
				double Rzbvalue = zc_rs_bond(ex_d, 500, FR[j]);
				p_value.push_back(-500.0/840.0 * Esvalue + 500 * Dsvalue + Rzbvalue);
				SP += 1.0;
			}
			// write the the value of portfolio ranges with index onto a .csv file
			char filename[25];
			sprintf(filename, "portfoliovalue_%d_%d.csv", i, int(15.0-ex_d)); // Name the files
			//cout << filename << endl;
			ofstream fout(filename);
			if(fout)
			{
				fout << filename << endl;
				fout << "volatility is " << vol[i] << endl;
				fout << "index" << "," << "portfolio value" << endl;
				print_vector(fout, stockp, p_value);
				fout.close();
			}
			j ++;
			ex_d -= 5.00;
			p_value.erase(p_value.begin(), p_value.end());
		}

		cfc[i] =  CFC(vol[i], spot_price, barrier_sp, div_y, expirate_data, cmt_itp); // current value of cash flow
		cout << "When the volatility is " << vol[i] << ", the cash flow is " << cfc[i] << endl;
		Port_price_cf.open("Portfolio_price_CF.txt", ios::out|ios::app);
		Port_price_cf << " when the volatility is " << vol[i] << ", the cash flow is " << cfc[i] << endl;
		Port_price_cf << endl;
		Port_price_cf.close();
	}

	return 0;
}
