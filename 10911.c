/* Problem URL: https://uva.onlinejudge.org/external/109/10911.pdf */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

#define MAXNCASES 8
#define UNSEEN -1


struct coord
{
  unsigned x;
  unsigned y;
};

typedef struct coord coord_t;

double min_cost (const coord_t houses[MAXNCASES * 2], const size_t nhouses);

int
main (void)
{
  unsigned npairs, ncases = 0;
  coord_t houses[MAXNCASES * 2];
  while (scanf ("%u", &npairs) == 1)
    {
      for (unsigned i = 0; i < 2 * npairs; ++i)
	if (scanf ("%*s %u %u", &houses[i].x, &houses[i].y) != 2)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
      if (npairs > 0)
	if (printf
	    ("Case %u: %.2f\n", ++ncases, min_cost (houses, 2 * npairs)) < 0)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
    }

  exit (EXIT_SUCCESS);
}

double
distance (const coord_t a, const coord_t b)
{
  const unsigned dx = (a.x > b.x) ? a.x - b.x : b.x - a.x;
  const unsigned dy = (a.y > b.y) ? a.y - b.y : b.y - a.y;

  return sqrt (dx * dx + dy * dy);
}

unsigned long long
to_bit_mask (const bool used[MAXNCASES * 2], const size_t len)
{
  unsigned long long mask = 0;
  for (size_t i = 0; i < len; ++i)
    if (used[i])
      mask |= (1 << i);

  return mask;
}

double
min_cost_helper (const coord_t houses[MAXNCASES * 2], const size_t nhouses,
		 bool used[MAXNCASES * 2], double seen[1 << (MAXNCASES * 2)])
{
  const unsigned long long mask = to_bit_mask (used, nhouses);

  if (seen[mask] != UNSEEN)
    return seen[mask];

  size_t start = 0;
  while (used[start] && start < nhouses)
    ++start;

  if (start == nhouses)
    return seen[mask] = 0;

  used[start] = true;
  double min_cost = DBL_MAX;
  for (size_t i = 0; i < nhouses; ++i)
    if (!used[i])
      {
	used[i] = true;
	const double c = (min_cost_helper (houses, nhouses, used, seen)
			  + distance (houses[start], houses[i]));
	min_cost = (c < min_cost) ? c : min_cost;

	used[i] = false;
      }

  used[start] = false;

  return seen[mask] = min_cost;
}

double
min_cost (const coord_t houses[MAXNCASES * 2], const size_t nhouses)
{
  bool used[MAXNCASES * 2] = { 0 };
  double seen[1 << (MAXNCASES * 2)];
  for (size_t i = 0; i < LENGTH (seen); ++i)
    seen[i] = UNSEEN;

  return min_cost_helper (houses, nhouses, used, seen);
}
