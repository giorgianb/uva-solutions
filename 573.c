#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

int
main (void)
{
  unsigned h, u, d, f;

  while (scanf ("%u %u %u %u", &h, &u, &d, &f) == 4)
    {
      if (h == 0)
	break;

      double cur = 0, cu = u, dcu = -(u * (f / 100.0));
      unsigned day = 0;

      while (cur >= 0)
	{
	  ++day;
	  cur += cu;
	  cu = (cu + dcu > 0) ? cu + dcu : 0;
	  if (cur > h)
	    {
	      if (printf ("success on day %u\n", day) < 0)
		{
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}
	      break;
	    }

	  cur -= d;
	  if (cur < 0)
	    {
	      if (printf ("failure on day %u\n", day) < 0)
		{
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}
	      break;
	    }
	}
    }

  exit (EXIT_SUCCESS);
}
