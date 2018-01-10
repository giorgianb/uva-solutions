/* Problem URL: https://uva.onlinejudge.org/external/103/10363.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define NROWS 3
#define NCOLUMNS 3

bool valid_board (char board[NROWS][NCOLUMNS]);

int
main (void)
{
  unsigned ncases;

  if (scanf ("%u", &ncases) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  char board[NROWS][NCOLUMNS];

  for (unsigned i = 0; i < ncases; ++i)
    {
      for (size_t j = 0; j < NROWS; ++j)
	if (scanf ("%3s", board[j]) != 1)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      if (!valid_board (board))
	{
	  if (puts ("no") == EOF)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	}
      else if (puts ("yes") == EOF)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}

bool
valid_board (char board[NROWS][NCOLUMNS])
{
  /* check that there are a valid number of X's and O's */
  unsigned nx, no;

  nx = no = 0;
  for (size_t i = 0; i < NROWS; ++i)
    for (size_t j = 0; j < NCOLUMNS; ++j)
      {
	nx += board[i][j] == 'X';
	no += board[i][j] == 'O';
      }
  if (!(nx == no || nx == no + 1))
    return false;

  /* check that there's at most one horizontal win */
  unsigned nhorz = 0;
  char hwin = '.';
  for (size_t i = 0; i < NROWS; ++i)
    {
      bool win = true;
      for (size_t j = 1; j < NCOLUMNS && win; ++j)
	win &= (board[i][j - 1] == board[i][j] && board[i][j] != '.');
      nhorz += win;

      hwin = (win) ? board[i][0] : hwin;
    }

  if (nhorz > 1)
    return false;

  /* check that there's at most one vertical win */
  unsigned nvert = 0;
  char vwin = '.';
  for (size_t i = 0; i < NCOLUMNS; ++i)
    {
      bool win = true;
      for (size_t j = 1; j < NROWS && win; ++j)
	win &= (board[j - 1][i] == board[j][i] && board[j][i] != '.');
      nvert += win;

      vwin = (win) ? board[0][i] : vwin;
    }

  /* there can be two diagonal wins, so don't bother keeping count */
  char dwin = '.';
  bool lwin = true, rwin = true;
  for (size_t i = 1; i < NROWS; ++i)
    {
      lwin &= board[i - 1][i - 1] == board[i][i] && board[i][i] != '.';
      rwin &= board[i - 1][NROWS - (i - 1) - 1] == board[i][NROWS - i - 1]
	&& board[i][NROWS - i - 1] != '.';
    }
  if (lwin)
    dwin = board[0][0];
  else if (rwin)
    dwin = board[0][NROWS - 1];

  if (nvert > 1)
    return false;

  if (hwin != '.' || vwin != '.' || dwin != '.')
    {
      const char winner = ((hwin != '.') ? hwin :
			   (vwin != '.') ? vwin : dwin);


      if (winner == 'O')
	return no == nx;
      else if (winner == 'X')
	return nx == no + 1;
    }

  return true;
}
