/*
 * Get the CMT data from the files downloaded from
 * http://www.federalreserve.gov/releases/h15/data.htm* 
 */


#include "getCMT.h"

using namespace std;

typedef double manurity;
typedef double rate;

map<double, double> CMT_data()
{
	map<manurity, rate> cmt; // store the rate of manurity

	ifstream infile_3mCMT("./FRB_H15_CMT_3m.csv");
	if(!infile_3mCMT)
	{
		cout << "There is no document for 3 month CMT" << endl;
	}
	vector<double> m3CMT = get_data_H15(infile_3mCMT);
	infile_3mCMT.close();
	m3CMT.erase(m3CMT.begin(), m3CMT.end());

	ifstream infile_6mCMT("./FRB_H15_CMT_6m.csv");
	if(!infile_6mCMT)
	{
		cout << "There is no document for 6 month CMT" << endl;
	}
	vector<double> m6CMT = get_data_H15(infile_6mCMT);
	infile_6mCMT.close();
	cmt[0.50] = *(m6CMT.end()-1);
	m6CMT.erase(m6CMT.begin(), m6CMT.end());

	ifstream infile_1yCMT("./FRB_H15_1y.csv");
	if(!infile_1yCMT)
	{
		cout << "There is no document for 1 year CMT" << endl;
	}
	vector<double> y1CMT = get_data_H15(infile_1yCMT);
	infile_1yCMT.close();
	cmt[1.00] = *(y1CMT.end()-1);
	y1CMT.erase(y1CMT.begin(), y1CMT.end());

		
	ifstream infile_2yCMT("./FRB_H15_2y.csv");
	if(!infile_2yCMT)
	{
		cout << "There is no document for 2 year CMT" << endl;
	}
	vector<double> y2CMT = get_data_H15(infile_2yCMT);
	infile_2yCMT.close();
	cmt[2.00] = *(y2CMT.end()-1);
	y2CMT.erase(y2CMT.begin(), y2CMT.end());


	ifstream infile_3yCMT("./FRB_H15_3y.csv");
	if(!infile_3yCMT)
	{
		cout << "There is no document for 3 year CMT" << endl;
	}
	vector<double> y3CMT = get_data_H15(infile_3yCMT);
	infile_3yCMT.close();
	cmt[3.00] = *(y3CMT.end()-1);
	y3CMT.erase(y3CMT.begin(), y3CMT.end());

	ifstream infile_5yCMT("./FRB_H15_5y.csv");
	if(!infile_5yCMT)
	{
		cout << "There is no document for 5 year CMT" << endl;
	}
	vector<double> y5CMT = get_data_H15(infile_5yCMT);
	infile_5yCMT.close();
	cmt[5.00] = *(y5CMT.end()-1);
	y5CMT.erase(y5CMT.begin(), y5CMT.end());

	ifstream infile_7yCMT("./FRB_H15_7y.csv");
	if(!infile_7yCMT)
	{
		cout << "There is no document for 7 year CMT" << endl;
	}
	vector<double> y7CMT = get_data_H15(infile_7yCMT);
	infile_7yCMT.close();
	cmt[7.00] = *(y7CMT.end()-1);
	y7CMT.erase(y7CMT.begin(), y7CMT.end());

	ifstream infile_10yCMT("./FRB_H15_10y.csv");
	if(!infile_10yCMT)
	{
		cout << "There is no document for 10 year CMT" << endl;
	}
	vector<double> y10CMT = get_data_H15(infile_10yCMT);
	infile_10yCMT.close();
	cmt[10.00] = *(y10CMT.end()-1);
	y10CMT.erase(y10CMT.begin(), y10CMT.end());

	ifstream infile_20yCMT("./FRB_H15_20y.csv");
	if(!infile_20yCMT)
	{
		cout << "There is no document for 20 year CMT" << endl;
	}
	vector<double> y20CMT = get_data_H15(infile_20yCMT);
	infile_20yCMT.close();
	cmt[20.00] = *(y20CMT.end()-1);
	y20CMT.erase(y20CMT.begin(), y20CMT.end());
	
	vector< pair<double, double> > cmt_dload; // store the CMT data in a vector downloaded from Fed's site
	// store the downloaded data in the map which stores all rates
	for(map<manurity, rate>::iterator it = cmt.begin(); it != cmt.end(); it++)
	{
		pair<double, double> temp(it->first, it->second);
		cmt_dload.push_back(temp);
	}
	// linear interpolate to get quarterly rates from 0.25 yr to 15 yr
	vector<pair<double, double> >::iterator kt;
	double quar = 0.25;
	for(kt = cmt_dload.begin(); kt != cmt_dload.end()-1; kt++)
	{
		for(double intx = (*kt).first+quar; intx != (*(kt+1)).first; intx += quar)
		{
			if(intx > 15.00)
			{
				break;
			}
			cmt[intx] = interp((*kt).first, (*(kt+1)).first, (*kt).second, (*(kt+1)).second, intx); // interpolate
		}
	}

	cmt_dload.erase(cmt_dload.begin(), cmt_dload.end());

	return cmt;
}

