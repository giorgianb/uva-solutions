/* Problem URL: https://uva.onlinejudge.org/external/102/10281.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

#define MAXLINELEN 100

int
main (void)
{
  char line[MAXLINELEN + 1];

  double speed = 0;
  double distance = 0;
  unsigned time = 0;
  while (fgets (line, LENGTH (line), stdin) == line)
    {
      unsigned hour, min, sec;
      double curspeed;

      const int nmatched =
	sscanf (line, "%u:%u:%u %lf", &hour, &min, &sec, &curspeed);

      const unsigned curtime = hour * 3600 + min * 60 + sec;
      /* managed to read time */
      if (nmatched >= 3)
	{
	  distance += speed / 3600 * (curtime - time);	/* curspeed / 3600 gives km/s, curtime - time gives delta t */
	  if (nmatched == 3
	      && printf ("%02u:%02u:%02u %.2lf km\n", hour, min, sec,
			 distance) < 0)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	  time = curtime;

	  /* speed specified */
	  if (nmatched == 4)
	    speed = curspeed;
	}
      else
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }
}
