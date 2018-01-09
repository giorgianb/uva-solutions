/* Problem URL: https://uva.onlinejudge.org/external/6/661.pdf */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAXNDEVICES 20

int
main (void)
{
  unsigned consum[MAXNDEVICES];
  unsigned ndevices, nops, cap;
  unsigned seq = 0;

  while (scanf ("%u %u %u", &ndevices, &nops, &cap) == 3)
    {
      if (ndevices == 0 && nops == 0 && cap == 0)
	break;

      for (size_t i = 0; i < ndevices; ++i)
	if (scanf ("%u", &consum[i]) != 1)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      unsigned cur = 0, maxconsum = 0;
      bool on[MAXNDEVICES] = { 0 };
      for (unsigned i = 0; i < nops; ++i)
	{
	  size_t device;
	  if (scanf ("%zu", &device) != 1)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  cur += (on[device - 1] ? -1 : 1) * consum[device - 1];
	  on[device - 1] = !on[device - 1];
	  maxconsum = (cur > maxconsum) ? cur : maxconsum;
	}

      const bool blown = (maxconsum > cap);

      if (printf
	  ("Sequence %u\nFuse was %sblown.\n", ++seq,
	   blown ? "" : "not ") < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      if (!blown)
	if (printf ("Maximal power consumption was %u amperes.\n", maxconsum)
	    < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      if (putchar ('\n') == EOF)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
