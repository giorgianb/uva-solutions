/* Problem URL: https://uva.onlinejudge.org/external/100/10082.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
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
    if (isspace (c))
      {
	if (putchar (c) == EOF)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
      }
    else
      {
	char out;
	switch (c)
	  {
	  case '1':
	    out = '`';
	    break;
	  case '2':
	  case '3':
	  case '4':
	  case '5':
	  case '6':
	  case '7':
	  case '8':
	  case '9':
	    out = c - 1;
	    break;
	  case '0':
	    out = '9';
	    break;
	  case '-':
	    out = '0';
	    break;
	  case '=':
	    out = '-';
	    break;
	  case 'W':
	    out = 'Q';
	    break;
	  case 'E':
	    out = 'W';
	    break;
	  case 'R':
	    out = 'E';
	    break;
	  case 'T':
	    out = 'R';
	    break;
	  case 'Y':
	    out = 'T';
	    break;
	  case 'U':
	    out = 'Y';
	    break;
	  case 'I':
	    out = 'U';
	    break;
	  case 'O':
	    out = 'I';
	    break;
	  case 'P':
	    out = 'O';
	    break;
	  case '[':
	    out = 'P';
	    break;
	  case ']':
	    out = '[';
	    break;
	  case '\\':
	    out = ']';
	    break;
	  case 'S':
	    out = 'A';
	    break;
	  case 'D':
	    out = 'S';
	    break;
	  case 'F':
	    out = 'D';
	    break;
	  case 'G':
	    out = 'F';
	    break;
	  case 'H':
	    out = 'G';
	    break;
	  case 'J':
	    out = 'H';
	    break;
	  case 'K':
	    out = 'J';
	    break;
	  case 'L':
	    out = 'K';
	    break;
	  case ';':
	    out = 'L';
	    break;
	  case '\'':
	    out = ';';
	    break;
	  case 'X':
	    out = 'Z';
	    break;
	  case 'C':
	    out = 'X';
	    break;
	  case 'V':
	    out = 'C';
	    break;
	  case 'B':
	    out = 'V';
	    break;
	  case 'N':
	    out = 'B';
	    break;
	  case 'M':
	    out = 'N';
	    break;
	  case ',':
	    out = 'M';
	    break;
	  case '.':
	    out = ',';
	    break;
	  case '/':
	    out = '.';
	    break;
	  default:
	    fprintf (stderr, __LOC_PRE__ "Unexpected character: '%c'\n", c);
	    exit (EXIT_FAILURE);
	  }

	if (putchar (out) == EOF)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
      }

  exit (EXIT_SUCCESS);
}
