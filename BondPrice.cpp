#include "BondPrice.h"

double zc_rs_bond(double expire, double principal, double rate)
{
	/* expire:expire date
	 * principal: payment at maturity
	 * rate: risk free rate */
	return principal * exp(-rate * expire);
}
