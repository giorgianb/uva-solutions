/* Problem URL: https://uva.onlinejudge.org/external/110/11044.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

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
      unsigned len, width;
      if (scanf ("%u %u", &len, &width) != 2)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      unsigned count = ceil ((len - 2.0) / 3) * ceil ((width - 2.0) / 3);
      if (printf ("%u\n", count) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
