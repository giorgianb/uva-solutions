/* Problem URL: https://uva.onlinejudge.org/external/107/10703.pdf */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

#define MAX_DIFF_LEN 8
#define GROWTH_FACTOR 2

struct rect
{
  int x1, y1;
  int x2, y2;
};
typedef struct rect rect_t;

struct rect_diff
{
  rect_t rects[MAX_DIFF_LEN];
  size_t len;
};
typedef struct rect_diff rect_diff_t;

rect_t make_rect (const int x1, const int y1, const int x2, const int y2);
unsigned rect_area (const rect_t r);
rect_t rect_intersection (const rect_t r1, const rect_t r2);
rect_diff_t rect_difference (const rect_t r1, const rect_t r2);

int
main (void)
{
  unsigned w, h;
  size_t nrects;
  while (scanf ("%u %u %zu", &w, &h, &nrects) == 3)
    {
      if (h == 0 && w == 0 && nrects == 0)
	break;

      const rect_t board = make_rect (0, 0, w, h);

      rect_t *list;
      if ((list = (rect_t *) malloc (nrects * sizeof *list)) == NULL)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
      size_t l_size = nrects;
      size_t l_pos = 0;

      rect_t *stack;
      if ((stack = (rect_t *) malloc (nrects * sizeof *stack)) == NULL)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
      size_t s_size = nrects;
      size_t s_pos = 0;

      for (size_t i = 0; i < nrects; ++i)
	{
	  int x1, y1, x2, y2;
	  if (scanf ("%d %d %d %d", &x1, &y1, &x2, &y2) != 4)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  rect_t rect = make_rect (x1, y1, x2, y2);
	  /* deal with coordinate system */
	  --rect.x1;
	  --rect.y1;

	  rect = rect_intersection (board, rect);

	  if (rect_area (rect) > 0)
	    stack[s_pos++] = rect;
	}

      while (s_pos)
	{
	  const rect_t rect = stack[--s_pos];	/* pop rectangle off of the stack */
	  if (rect_area (rect) == 0)
	    continue;

	  /* whether the rectangle at the top of the stack intersects
	     any of the rectangles in the accepted list */
	  bool intersect = false;
	  for (size_t i = 0; i < l_pos && !intersect; ++i)
	    {
	      const rect_t common = rect_intersection (rect, list[i]);
	      if (rect_area (common) > 0)
		{
		  intersect = true;
		  /* push differences onto stack for processing */
		  rect_diff_t diffs = rect_difference (rect, common);
		  for (size_t j = 0; j < diffs.len; ++j)
		    {
		      if (s_pos == s_size)
			{
			  rect_t *new_stack;
			  if ((new_stack = (rect_t *)
			       realloc (stack,
					s_size * GROWTH_FACTOR *
					sizeof *new_stack)) == NULL)
			    {
			      perror (__LOC__);
			      exit (EXIT_FAILURE);
			    }
			  stack = new_stack;
			  s_size *= GROWTH_FACTOR;
			}
		      stack[s_pos++] = diffs.rects[j];
		    }
		}
	    }

	  /* rectangle shared no area with any of the seen rectangles */
	  if (!intersect)
	    {
	      if (l_pos == l_size)
		{
		  rect_t *new_list;
		  if ((new_list = (rect_t *)
		       realloc (list,
				l_size * GROWTH_FACTOR * sizeof *new_list)) ==
		      NULL)
		    {
		      perror (__LOC__);
		      exit (EXIT_FAILURE);
		    }
		  list = new_list;
		  l_size *= GROWTH_FACTOR;
		}
	      list[l_pos++] = rect;
	    }
	}

      unsigned used_area = 0;
      for (size_t i = 0; i < l_pos; ++i)
	used_area += rect_area (list[i]);

      const unsigned area = rect_area (board) - used_area;
      if (area <= 1)
	{
	  if (printf
	      ("There is %s empty spot%s.\n", (area == 0) ? "no" : "one",
	       (area == 0) ? "s" : "") < 0)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	}
      else
	{
	  if (printf ("There are %u empty spots.\n", area) < 0)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	}

      free (list);
      free (stack);
    }

  exit (EXIT_SUCCESS);
}

int
min (const int a, const int b)
{
  return (a < b) ? a : b;
}

int
max (const int a, const int b)
{
  return (a > b) ? a : b;
}

rect_t
make_rect (const int x1, const int y1, const int x2, const int y2)
{
  rect_t r;
  r.x1 = min (x1, x2);
  r.y1 = min (y1, y2);

  r.x2 = max (x1, x2);
  r.y2 = max (y1, y2);

  return r;
}



unsigned
rect_area (const rect_t r)
{
  return (r.x2 - r.x1) * (r.y2 - r.y1);
}

rect_t
rect_intersection (const rect_t r1, const rect_t r2)
{
  /* if any of the rectangles are empty, there is no intersection */
  if (rect_area (r1) == 0 || rect_area (r2) == 0)
    return make_rect (0, 0, 0, 0);

  const int x1 = max (r1.x1, r2.x1);
  const int x2 = min (r1.x2, r2.x2);

  const int y1 = max (r1.y1, r2.y1);
  const int y2 = min (r1.y2, r2.y2);

  if (x1 > x2 || y1 > y2)
    return make_rect (0, 0, 0, 0);
  else
    return make_rect (x1, y1, x2, y2);
}


/* note that r2 must be a subset of r1 */
rect_diff_t
rect_difference (const rect_t r1, const rect_t r2)
{
  rect_diff_t diffs;
  diffs.len = 0;

  rect_t r;

  if (rect_area (r = make_rect (r1.x1, r1.y1, r2.x1, r2.y1)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r1.x1, r2.y2, r2.x1, r2.y1)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r1.x1, r1.y2, r2.x1, r2.y2)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r2.x1, r2.y2, r2.x2, r1.y2)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r2.x2, r2.y2, r1.x2, r1.y2)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r2.x2, r2.y2, r1.x2, r2.y1)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r2.x2, r2.y1, r1.x2, r1.y1)) > 0)
    diffs.rects[diffs.len++] = r;

  if (rect_area (r = make_rect (r2.x1, r2.y1, r2.x2, r1.y1)) > 0)
    diffs.rects[diffs.len++] = r;

  return diffs;
}
