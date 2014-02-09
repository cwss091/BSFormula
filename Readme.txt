/* ISyE 6767 Project i
 * Yuliang Li
 * MS-QCF student
 * 2013-10-01
 */

This Program complete 4 tasks to analyze a security as below:
1. Get the data from H15 and interpolate to get all rates on each quarter.
2. Price the substitute portfolios and the cash left.
3. Value the portfolios on the date of generation, 5 yrs and 4 yrs after formulation.
4. Calculate the current value of cash flow.

The inputfiles include
-InputParameters.txt: input 8 parameters, and one line has only one parameter. From the first to the last  line, includes spot index, strike index, barrier, risk-free rate, divindend yield, expire date, volatilit y1, volatility 2.

-FRB_H15_CMT_3m.csv, FRB_H15_CMT_6m.csv, FRB_H15_1y.csv, FRB_H15_2y.csv, FRB_H15_3y.csv,FRB_H15_5y.csv, FRB_H15_7y.csv, FRB_H15_10y.csv, FRB_H15_20y.csv: the monthly CMT rates downloaded from http://www.federalreserve.gov/releases/h15/data.htm. 

-FRB_H15_Sw2.csv and FRB_H15_Sw30.csv: the swap rate of 2yrs and 30yrs

The oputfiles include
-portfoliovalue_0_0.csv, portfoliovalue_0_5.csv, portfoliovalue_0_10.csv, portfoliovalue_1_0.csv, portfoliovalue_1_5.csv, portfoliovalue_1_10.csv: the value of portfolio
-Portfolio_price_CF.txt: the price of portfolios and the current value of cash flow



