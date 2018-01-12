/* Problem URL: https://uva.onlinejudge.org/external/108/10812.pdf */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

int
main (void)
{
  unsigned ncases;

  if (scanf ("%u", &ncases) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  for (unsigned i = 0; i < ncases; ++i)
    {
      unsigned s, d;
      if (scanf ("%u %u", &s, &d) != 2)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      /* solve the system of equations
         t1 + t2 = s
         t1 - t2 = d */

      /* football scores must always be integers */
      if ((s + d) % 2 != 0)
	{
	  if (puts ("impossible") == EOF)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	  continue;
	}

      const unsigned t1 = (s + d) / 2;

      /* football scores must always be positive */
      if (t1 > s)
	{
	  if (puts ("impossible") == EOF)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	  continue;
	}

      if (printf ("%u %u\n", t1, s - t1) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
