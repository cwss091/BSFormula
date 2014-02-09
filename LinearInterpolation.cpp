#include "LinearInterpolation.h"

using namespace std;

double interp(double x0, double x1, double y0, double y1, double t)
{
	if(x1 != x0)
	{
		return (y1-y0) / (x1-x0) * (t-x0) + y0;
	}
	else
	{
		return y0;
	}
}

