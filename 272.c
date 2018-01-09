#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

int
main (void)
{
  int c;
  bool quote_start = true;

  while ((c = getchar ()) != EOF)
    if (c == '"' && quote_start)
      {
	if (printf ("``") < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
	quote_start = !quote_start;
      }
    else if (c == '"' && !quote_start)
      {
	if (printf ("''") < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
	quote_start = !quote_start;
      }
    else if (putchar (c) == EOF)
      {
	perror (__LOC__);
	exit (EXIT_FAILURE);
      }

  exit (EXIT_SUCCESS);
}
