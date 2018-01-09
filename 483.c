/* Problem URL: https://uva.onlinejudge.org/external/4/483.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define BUFSIZE 1

int
main (void)
{
  int c;
  char *buf;
  size_t pos, size;

  if ((buf = (char *) malloc ((size = BUFSIZE) * sizeof *buf)) == NULL)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  pos = 0;
  while ((c = getchar ()) != EOF)
    {
      if (isspace (c))
	{
	  for (size_t i = 0; i < pos; ++i)
	    if (putchar (buf[pos - i - 1]) == EOF)
	      {
		free (buf);
		perror (__LOC__);
		exit (EXIT_FAILURE);
	      }
	  pos = 0;

	  if (putchar (c) == EOF)
	    {
	      free (buf);
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	}
      else
	{
	  if (pos >= size)
	    {
	      char *newbuf;
	      if ((newbuf =
		   (char *) realloc (buf, (size * 2) * sizeof *buf)) == NULL)
		{
		  free (buf);
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}
	      else
		{
		  buf = newbuf;
		  size *= 2;
		}
	    }

	  buf[pos++] = c;
	}
    }

  free (buf);
  exit (EXIT_SUCCESS);
}
