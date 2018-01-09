#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <error.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define NCOLORS 3
#define NBINS 3

enum color
{
  BROWN = 0,
  GREEN,
  CLEAR
};

#define LENGTH(arr) (sizeof (arr) / sizeof(arr[0]))

struct bin
{
  unsigned count[NCOLORS];
};

struct bin_arrangement
{
  enum color color[NBINS];
};


typedef struct bin bin_t;
typedef struct bin_arrangement bin_arrangement_t;

int read_bins (bin_t bins[]);

unsigned cost (const bin_t bins[], const bin_arrangement_t arrangement);

char color_to_char (enum color c);

int
main (void)
{
  bin_t bins[NBINS];
  const bin_arrangement_t arrangements[3 * 2 * 1] = {
    {{BROWN, CLEAR, GREEN}},
    {{BROWN, GREEN, CLEAR}},
    {{CLEAR, BROWN, GREEN}},
    {{CLEAR, GREEN, BROWN}},
    {{GREEN, BROWN, CLEAR}},
    {{GREEN, CLEAR, BROWN}}
  };

  while (read_bins (bins) == 3)
    {
      unsigned min_cost = UINT_MAX;
      const bin_arrangement_t *min_arrangement = NULL;
      for (size_t i = 0; i < LENGTH (arrangements); ++i)
	{
	  unsigned c = cost (bins, arrangements[i]);
	  if (c < min_cost)
	    {
	      min_cost = c;
	      min_arrangement = &arrangements[i];
	    }
	}


      for (size_t i = 0; i < LENGTH (min_arrangement->color); ++i)
	if (putchar (color_to_char (min_arrangement->color[i])) == EOF)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      printf (" %u\n", min_cost);
    }

  exit (EXIT_SUCCESS);
}

int
read_bins (bin_t bins[])
{
  int nread = 0;
  for (size_t i = 0; i < NBINS; ++i, ++nread)
    for (size_t j = 0; j < NCOLORS; ++j)
      if (scanf ("%u", &bins[i].count[j]) != 1)
	goto done;
done:
  return nread;
}

unsigned
cost (const bin_t bins[], const bin_arrangement_t arrangement)
{
  unsigned cost = 0;
  for (size_t i = 0; i < LENGTH (arrangement.color); ++i)
    for (size_t j = 0; j < LENGTH (bins[i].count); ++j)
      if (j != arrangement.color[i])	/* if the color doesn't match that of the arrangement */
	cost += bins[i].count[j];

  return cost;
}

char
color_to_char (enum color c)
{
  switch (c)
    {
    case BROWN:
      return 'B';
    case GREEN:
      return 'G';
    case CLEAR:
      return 'C';
    default:
      fprintf (stderr, __LOC_PRE__ "Unexpected color: %d\n", c);
      exit (EXIT_FAILURE);
    }
}
