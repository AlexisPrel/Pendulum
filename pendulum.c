/*
Alexis Prel
Phys2200: Computational physics

Final take-home question 2: Numerical study of a pendulum

This programs solves for the equilibrium position of a simple pendulum
Adimensional equations
	phi'' + (1 - x*Omega^2 sin(Omega*tau))*sin(phi) = 0
	rewrites as:
		dy[1] = (x*O*O*sin(O*t) - 1)*sin(y[0])
		dy[0] = y[1]
	
	with:
	[abb]	name		definition				unit
	t		tau 	=== t*omega_0				[]
	O		Omega	=== omega/omega_0			[]
	x		x		=== a/l						[]
			omega_0	=== sqrt(l/g)				[rad/s]
			a		:	amplitude of the osc.	[m]
			omega	:	frequency -----------	[rad/s]
			l		:	length of the pendulum	[m]
			g		:	gravitationnal constant	[m/s2]
		
	y[0]	phi		:	angle with normal		[rad]
	y[1]	phi'	===	dphi/dtau				[rad]
*/

#include <stdio.h>
#include <math.h>

double pendulum_evolution (char filename[], double O);

char stable_pos(double O)
{
    double mean_phi = pendulum_evolution ("out", O);
    if (fabs (mean_phi - M_PI) < M_PI/30.)	// if close enough from pi -> up
        return 'u';
    else if (fabs(mean_phi - 0) < M_PI/30.)	// idem with 0 -> down
        return 'd';
    else									// otherwise -> diverging
        return 'x';
}

int main(void)
{
    //parameters
    double O = 150.;            //to be variated

    double O1 = 100., O2 = 200.;        //band (to be shortened)
    double tolerance = 0.05 * O1;       //width of desired band

    //typical graphs: i is not useful, but we want the "out_1" "out_2" files for graphs
    int i = pendulum_evolution("out_1", O1);
    i = pendulum_evolution("out_2", O2);

    //main loop: proceed by dichotomy
    char pos;
    char pos1 = stable_pos(O1), pos2 = stable_pos(O2);
    	// explanatory message
    	printf("d: down, u: up, x: diverging\n");
    printf("%f: %c\n%f: %c\n", O1, pos1, O2, pos2);
    
    while ((O2 - O1) > tolerance)       // until desired precision is achieved
    {
        pos = stable_pos(O);
        if (pos == pos1)        // tests band edges  ...
            O1 = O;             // ... and narrow it ...
        else if (pos == pos2)
            O2 = O;             // ... one way or another.
        else
        {
            printf("! solution is not in the given band\n");
            break;
        }
        printf("%f: %c\n", O, pos);
        O = (O1 + O2) / 2.;     // next iteration in the new middle of the band
    }
    // printing result
    printf ("Solution: %f +- %f\n", O, (O2 - O1) / 2.);
    return 0;
}
