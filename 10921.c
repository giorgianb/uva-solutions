/* Problem URL: https://uva.onlinejudge.org/external/109/10921.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

int
main (void)
{
  int c;
  while ((c = getchar ()) != EOF)
    {
      char out;
      switch (c)
	{
	case 'A':
	case 'B':
	case 'C':
	  out = '2';
	  break;
	case 'D':
	case 'E':
	case 'F':
	  out = '3';
	  break;
	case 'G':
	case 'H':
	case 'I':
	  out = '4';
	  break;
	case 'J':
	case 'K':
	case 'L':
	  out = '5';
	  break;
	case 'M':
	case 'N':
	case 'O':
	  out = '6';
	  break;
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	  out = '7';
	  break;
	case 'T':
	case 'U':
	case 'V':
	  out = '8';
	  break;
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	  out = '9';
	  break;
	default:
	  if (isspace (c) || c == '-' || c == '0' || c == '1')
	    out = c;
	  else
	    {
	      fprintf (stderr, __LOC_PRE__ "Unexpected character: %c\n", c);
	      exit (EXIT_FAILURE);
	    }
	}

      if (putchar (out) == EOF)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
