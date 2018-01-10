/* Problem URL: https://uva.onlinejudge.org/external/8/837.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <math.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

struct line
{
  double x1, x2;
  double r;
};

typedef struct line line_t;

int linecmp (const void *const p1, const void *const p2);
int doublecmp (const void *const p1, const void *const p2);

int
main (void)
{
  unsigned ncases;

  if (scanf ("%u", &ncases) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  for (unsigned i = 0; i < ncases; ++i)
    {
      size_t nlines;
      if (scanf ("%zu", &nlines) != 1)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      line_t *lines;
      double *points;
      if ((lines = (line_t *) malloc (nlines * sizeof *lines)) == NULL)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      if ((points = (double *) malloc (2 * nlines * sizeof *points)) == NULL)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      for (size_t i = 0; i < nlines; ++i)
	{
	  double x1, x2;
	  if (scanf ("%lf %*f %lf %*f %lf", &x1, &x2, &lines[i].r) != 3)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  lines[i].x1 = (x1 < x2) ? x1 : x2;
	  lines[i].x2 = (x1 > x2) ? x1 : x2;
	  points[2 * i] = x1;
	  points[2 * i + 1] = x2;
	}

      qsort (lines, nlines, sizeof *lines, linecmp);
      qsort (points, nlines * 2, sizeof *points, doublecmp);

      unsigned nsegments = (2 * nlines - 1 + (points[0] != -INFINITY)
			    + (points[2 * nlines - 1] != INFINITY));

      if (printf ("%u\n", nsegments) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      if (points[0] != -INFINITY)
	if (printf ("-inf %.3f %.3f\n", points[0], 1.0) < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      for (size_t i = 0; i < 2 * nlines - 1; ++i)
	{
	  const double x1 = points[i];
	  const double x2 = points[i + 1];

	  /* find all line segments covering (x1, x2) */
	  double light = 1;
	  for (size_t j = 0; j < nlines; ++j)
	    if (lines[j].x1 <= x1 && lines[j].x2 >= x2)
	      light *= lines[j].r;

	  if (x2 != INFINITY)
	    {
	      if (printf ("%.3f %.3f %.3f\n", x1, x2, light) < 0)
		{
		  perror (__LOC__);
		  exit (EXIT_FAILURE);
		}
	    }
	  else if (printf ("%.3f +inf %.3f\n", x1, light) < 0)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	}

      if (points[2 * nlines - 1] != INFINITY)
	if (printf ("%.3f +inf %.3f\n", points[2 * nlines - 1], 1.0) < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      if (i < ncases - 1)
	if (putchar ('\n') == EOF)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      free (lines);
      free (points);
    }

  exit (EXIT_SUCCESS);
}

int
linecmp (const void *const p1, const void *const p2)
{
  const line_t *const l1 = (const line_t *) p1;
  const line_t *const l2 = (const line_t *) p2;

  /* Problem definition guarantees there won't be overlapping points */
  return (l1->x1 < l2->x1) ? -1 : 1;
}


int
doublecmp (const void *const p1, const void *const p2)
{
  const double *const d1 = (const double *) p1;
  const double *const d2 = (const double *) p2;

  /* Problem definition guarantees there won't be overlapping points */
  return (*d1 < *d2) ? -1 : 1;
}
