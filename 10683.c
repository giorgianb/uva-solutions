/* Problem URL: https://uva.onlinejudge.org/external/106/10683.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAX_NORMAL_TIME ((23 * 60 * 60 * 100) + (59 * 60 * 100) + (59 * 100) + 100)
#define MAX_DECIMAL_TIME ((9 * 100 * 100 * 100) + (99 * 100 * 100) + (99 * 100) + 100)

int
main (void)
{
  unsigned hour, min, sec, cs;
  while (scanf ("%2u%2u%2u%2u", &hour, &min, &sec, &cs) == 4)
    {
      const unsigned ntime =
	cs + (sec * 100) + (min * 60 * 100) + (hour * 60 * 60 * 100);
      double dtime = (ntime * 1.0 / MAX_NORMAL_TIME) * MAX_DECIMAL_TIME;

      const double fraction = dtime - floor (dtime);
      if (1.0 - fraction <= 0.000001)
	dtime = ceil (dtime);

      if (printf ("%07.0lf\n", floor (dtime)) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

    }

  exit (EXIT_SUCCESS);
}
