#ifndef _IO_H__
#define _IO_H__

/* IO file input and out data from program */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<double> get_data_H15(std::ifstream& infile); // get the data from H15 form and store in a vector

// input the parameters
void input_data(double& spot, double& strike, double& barrier, double& rate, double& div_yield, double& expiry, double& volatility1, double& volatility2, std::ifstream& infile);

// input a tow double type
void input_vol(double& volatility1, double& volatility);

// print one vector
void print_vector(std::ofstream& outfile, std::vector<double> v);

// print two vectors simultaneously
void print_vector(std::ofstream& outfile, std::vector<double> u, std::vector<double> v);

#endif
