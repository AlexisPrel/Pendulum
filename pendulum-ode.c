#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int func(double t, const double y[], double f[], void *params)
{
    // y[0] - phi	[rad]
    // y[1] - phi'	[rad]

    double O = *(double *) params;
	double x = 0.01;
	
	f[0] = y[1];
	f[1] = (x*O*O*sin(O*t) - 1)*sin(y[0]);

    return GSL_SUCCESS;
}
