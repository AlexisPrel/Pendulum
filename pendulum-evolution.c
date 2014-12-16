#include <stdio.h>
#include <math.h>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_odeiv2.h>

int func (double t, const double y[], double f[], void *params);

double pendulum_evolution (char filename[], double O)
{
    size_t neqs = 2;                            // number of equations 
    double eps_abs = 1.e-8, eps_rel = 0.;       // desired precision
    double stepsize = 1.e-4;                    // initial integration step
    double t = 0., t1 = 10.*M_PI; // O;       // time interval. Omega*tau = omega*t from 0 to 1000 pi (500 natural oscillations) 
    int status;
    FILE *out;                                  // output file
    out = fopen (filename, "w+");

    // initial conditions
    double y[2] = { 0.99 * M_PI, 0. };

    // averaging
    double mean_phi = y[0];
    int n = 1;

    // Explicit embedded Runge-Kutta-Fehlberg (4,5) method. 
    gsl_odeiv2_step *s = gsl_odeiv2_step_alloc (gsl_odeiv2_step_rkf45, neqs);
    gsl_odeiv2_control *c = gsl_odeiv2_control_y_new (eps_abs, eps_rel);
    gsl_odeiv2_evolve *e = gsl_odeiv2_evolve_alloc (neqs);
    gsl_odeiv2_system sys = { func, NULL, neqs, &O };

    // Evolution loop 
    while (t < t1)
    {
        status = gsl_odeiv2_evolve_apply (e, c, s, &sys, &t, t1, &stepsize, y);
        if (status != GSL_SUCCESS)
        {
            printf ("Troubles: % .5e  % .5e  % .5e\n", t, y[0], y[1]);
            break;
        }
        fprintf (out, "% .5e  % .5e  % .5e\n", t, y[0], y[1]);  //writing in the file
        n++;
        mean_phi += y[0];
    }

    mean_phi /= n;              // the mean angle (around which oscillations are) is the sum of the angles divided by the # of steps

    // freeing memory and closing file
    gsl_odeiv2_evolve_free (e);
    gsl_odeiv2_control_free (c);
    gsl_odeiv2_step_free (s);
    fclose (out);

    return mean_phi;
}
