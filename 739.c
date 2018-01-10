/* Problem URL: https://uva.onlinejudge.org/external/7/739.pdf */
#include <stdio.h>
#include <error.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAXNAMELEN 20
#define CODELEN 4

int
main (void)
{
  if (printf ("%9s%-25s%s\n", "", "NAME", "SOUNDEX CODE") < 0)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  char name[MAXNAMELEN + 1];
  while (scanf ("%20s", name) == 1)
    {
      char code[CODELEN] = { '0', '0', '0', '0' };
      size_t index = 0;
      size_t len = strlen (name);
      bool new_code = false;

      for (size_t i = 0; i < len && index < CODELEN; ++i)
	switch (name[i])
	  {
	  case 'B':
	  case 'P':
	  case 'F':
	  case 'V':
	    new_code |= ((index == 0) || code[index - 1] != '1');
	    if (new_code)
	      {
		code[index++] = '1';
		new_code = false;
	      }
	    break;
	  case 'C':
	  case 'S':
	  case 'K':
	  case 'G':
	  case 'J':
	  case 'Q':
	  case 'X':
	  case 'Z':
	    new_code |= ((index == 0) || code[index - 1] != '2');
	    if (new_code)
	      {
		code[index++] = '2';
		new_code = false;
	      }
	    break;
	  case 'D':
	  case 'T':
	    new_code |= ((index == 0) || code[index - 1] != '3');
	    if (new_code)
	      {
		code[index++] = '3';
		new_code = false;
	      }
	    break;
	  case 'L':
	    new_code |= ((index == 0) || code[index - 1] != '4');
	    if (new_code)
	      {
		code[index++] = '4';
		new_code = false;
	      }
	    break;
	  case 'M':
	  case 'N':
	    new_code |= ((index == 0) || code[index - 1] != '5');
	    if (new_code)
	      {
		code[index++] = '5';
		new_code = false;
	      }
	    break;
	  case 'R':
	    new_code |= ((index == 0) || code[index - 1] != '6');
	    if (new_code)
	      {
		code[index++] = '6';
		new_code = false;
	      }
	    break;
	  case 'A':
	  case 'E':
	  case 'I':
	  case 'O':
	  case 'U':
	  case 'Y':
	  case 'W':
	  case 'H':
	    new_code = true;
	    if (i == 0)
	      ++index;
	    break;
	  }
      code[0] = name[0];
      if (printf ("%9s%-25s%.*s\n", "", name, CODELEN, code) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  if (printf ("%19s%s\n", "", "END OF OUTPUT") < 0)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
