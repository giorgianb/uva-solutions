/* Problem URL: https://uva.onlinejudge.org/external/9/941.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAXSTRLEN 20

int charcmp (const void *const p1, const void *const p2);
unsigned long long fac (const unsigned n);

int
main (void)
{
  unsigned nsamples;

  if (scanf ("%u", &nsamples) != 1)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  for (unsigned i = 0; i < nsamples; ++i)
    {
      char s[MAXSTRLEN + 1];
      unsigned long long nperm;

      if (scanf ("%20s %llu", s, &nperm) != 2)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
      const size_t len = strlen (s);

      qsort (s, len, sizeof s[0], charcmp);

      char perm[MAXSTRLEN + 1];
      bool used[MAXSTRLEN] = { 0 };
      for (size_t j = 0; j < len; ++j)
	{
	  const unsigned long long div = fac (len - j - 1);
	  const size_t nth = nperm / div;

	  unsigned nunused = 0;
	  size_t pos;
	  for (pos = 0; pos < len && nunused < nth; ++pos)
	    nunused += !used[pos];

	  // Skip any used elements that remain
	  while (used[pos] && ++pos < len)
	    ;

	  perm[j] = s[pos];
	  used[pos] = true;


	  nperm -= (nth * div);
	}
      perm[len] = '\0';

      if (printf ("%s\n", perm) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}

int
charcmp (const void *const p1, const void *const p2)
{
  const char *const c1 = (const char *) p1;
  const char *const c2 = (const char *) p2;
  return ((*c1 < *c2) ? -1 : ((*c1 == *c2) ? 0 : 1));
}

unsigned long long
fac (const unsigned n)
{
  unsigned long long fac = 1;

  for (unsigned i = 2; i <= n; ++i)
    fac *= i;

  return fac;
}
