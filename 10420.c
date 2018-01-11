/* Problem URL: https://uva.onlinejudge.org/external/104/10420.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

#define MAXLINELEN 75
#define MAXNLINES 2000

struct entry
{
  char country[MAXLINELEN + 1];
  unsigned count;
};

typedef struct entry entry_t;

int country_find (const void *const key, const void *const entry);
int entrycmp (const void *const p1, const void *const p2);

int
main (void)
{
  unsigned ncountries;
  char line[MAXLINELEN + 1];
  entry_t list[MAXNLINES];

  size_t top = 0;
  if (scanf ("%u\n", &ncountries) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  for (unsigned i = 0; i < ncountries; ++i)
    {
      if (fgets (line, LENGTH (line), stdin) == NULL)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      char country[MAXLINELEN + 1];
      if (sscanf (line, "%75s", country) != 1)
	{
	  perror (__LOC__);
	  fputs (line, stderr);
	  exit (EXIT_FAILURE);
	}

      entry_t *entry = (entry_t *)
	bsearch (country, list, top, sizeof list[0], country_find);
      if (entry == NULL)
	{
	  entry = &list[top++];
	  strcpy (entry->country, country);
	  entry->count = 1;
	  qsort (list, top, sizeof list[0], entrycmp);
	}
      else
	++entry->count;
    }

  for (size_t i = 0; i < top; ++i)
    if (printf ("%s %u\n", list[i].country, list[i].count) < 0)
      {
	perror (__LOC__);
	exit (EXIT_FAILURE);
      }

  exit (EXIT_SUCCESS);
}

int
country_find (const void *const key, const void *const entry)
{
  return strcmp ((const char *) key, ((const entry_t *) entry)->country);
}

int
entrycmp (const void *const p1, const void *const p2)
{
  return strcmp (((const entry_t *) p1)->country,
		 ((const entry_t *) p2)->country);
}
