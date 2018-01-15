/* Problem URL: https://uva.onlinejudge.org/external/112/11223.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAX_CODE_LEN 6

static char code_table[MAX_CODE_LEN + 1][(1 << MAX_CODE_LEN) - 1];

void init_code_table (void);

int
main (void)
{
  int c;
  size_t len;
  unsigned code = 0;
  unsigned nmessages;

  if (scanf ("%u\n", &nmessages) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  init_code_table ();

  for (unsigned i = 0; i < nmessages; ++i)
    {
      code = 0;
      len = 0;

      if (printf ("Message #%u\n", i + 1) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      while ((c = getchar ()) != EOF && c != '\n')
	{
	  if (c == ' ' && len)
	    {
	      if (putchar (code_table[len][code]) == EOF)
		{
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}

	      code = 0;
	      len = 0;
	    }
	  else if (c == ' ' && len == 0)
	    {
	      if (putchar (' ') == EOF)
		{
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}
	    }
	  else
	    {
	      code <<= 1;
	      code |= (c == '-');
	      ++len;
	      assert (len <= 6);
	    }
	}

      if (len && putchar (code_table[len][code]) == EOF)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      if (c == EOF && i + 1 != nmessages)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      if (printf ("\n%s", (i + 1 < nmessages) ? "\n" : "") < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}


void
init_code_table (void)
{
  code_table[2][1] = 'A';
  code_table[4][7] = 'J';
  code_table[3][0] = 'S';
  code_table[5][15] = '1';
  code_table[6][21] = '.';
  code_table[6][56] = ':';
  code_table[4][8] = 'B';
  code_table[3][5] = 'K';
  code_table[1][1] = 'T';
  code_table[5][7] = '2';
  code_table[6][51] = ',';
  code_table[6][42] = ';';
  code_table[4][10] = 'C';
  code_table[4][4] = 'L';
  code_table[3][1] = 'U';
  code_table[5][3] = '3';
  code_table[6][12] = '?';
  code_table[5][17] = '=';
  code_table[3][4] = 'D';
  code_table[2][3] = 'M';
  code_table[4][1] = 'V';
  code_table[5][1] = '4';
  code_table[6][30] = '\'';
  code_table[5][10] = '+';
  code_table[1][0] = 'E';
  code_table[2][2] = 'N';
  code_table[3][3] = 'W';
  code_table[5][0] = '5';
  code_table[6][43] = '!';
  code_table[6][33] = '-';
  code_table[4][2] = 'F';
  code_table[3][7] = 'O';
  code_table[4][9] = 'X';
  code_table[5][16] = '6';
  code_table[5][18] = '/';
  code_table[6][13] = '_';
  code_table[3][6] = 'G';
  code_table[4][6] = 'P';
  code_table[4][11] = 'Y';
  code_table[5][24] = '7';
  code_table[5][22] = '(';
  code_table[6][18] = '"';
  code_table[4][0] = 'H';
  code_table[4][13] = 'Q';
  code_table[4][12] = 'Z';
  code_table[5][28] = '8';
  code_table[6][45] = ')';
  code_table[6][26] = '@';
  code_table[2][0] = 'I';
  code_table[3][2] = 'R';
  code_table[5][31] = '0';
  code_table[5][30] = '9';
  code_table[5][8] = '&';
}
