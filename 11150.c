/* Problem URL: https://uva.onlinejudge.org/external/111/11150.pdf */
#include <stdio.h>
#include <stdlib.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

int
main (void)
{
  unsigned nbottles;
  while (scanf ("%u", &nbottles) == 1)
    {
      unsigned total = 1;
      for (unsigned i = 1; i < nbottles; ++i)
	total += (i % 2 == 0) ? 1 : 2;

      if (printf ("%u\n", total) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
