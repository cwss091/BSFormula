/** These are the functions declared in IO.h. **/

#include "IO.h"

using namespace std;

vector<double> get_data_H15(ifstream& infile) // get the data from H15 form and store in a vector
{
	string word;
	string temp1;
	double temp2;
	vector<double> rate;
	int i =0;
	while(getline(infile, word, '\r')) // search for the start of the data
	{
		i = i + 1;
		istringstream Intr(word);
		Intr >> temp1;
		if(i == 6)
		{
			break;
		}
	}
	while(getline(infile, word, ',')) // push the date into the vector
	{
		istringstream Tp1(word);
		getline(infile, word, '\r');
		istringstream Rt(word);
		Rt >> temp2;
		rate.push_back(temp2);
	}
	infile.close(); // close the file
	return rate;
}

void input_data(double& spot, double& strike, double& barrier, double& rate, double& div_yield, double& expiry, double& volatility1, double& volatility2, ifstream& infile)
{
    infile >> spot; // spot price
    infile >> strike; // strike index
    infile >> barrier; // barrier index
    infile >> rate; // risk free rate
    infile >> div_yield; // dividend yield
    infile >> expiry; // expire date
    infile >> volatility1; // volatility 1
    infile >> volatility2; // volatility 2
}

void print_vector(ofstream& outfile, vector<double> v)
{
    vector<double>::iterator it = v.begin();
	while(it != v.end()) outfile << *it++ << endl;
}

void print_vector(ofstream& outfile, vector<double> u, vector<double> v)
{
	vector<double>::iterator it = v.begin();
    vector<double>::iterator ip = u.begin();
    while(it != v.end()) outfile << *ip++ << "," << *it++ << endl;
}
