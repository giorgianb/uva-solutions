/* Problem URL: https://uva.onlinejudge.org/external/101/10141.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

#define MAXLINELEN 81

struct proposal
{
  char name[MAXLINELEN + 1];
  unsigned met;			/* number of requirements met */
  double price;
};

typedef struct proposal proposal_t;

int proposalcmp (const void *const p1, const void *const p2);

int
main (void)
{
  unsigned cur = 1;
  unsigned nreq, nproposals;

  char req[MAXLINELEN + 1];
  while (scanf ("%u %u\n", &nreq, &nproposals) == 2)
    {
      if (nreq == 0 && nproposals == 0)
	break;

      if (cur > 1)
	if (putchar ('\n') == EOF)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      for (unsigned i = 0; i < nreq; ++i)
	if (fgets (req, LENGTH (req), stdin) == NULL)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }

      proposal_t best;
      for (unsigned i = 0; i < nproposals; ++i)
	{
	  proposal_t current;
	  if (fgets (current.name, LENGTH (current.name), stdin) == NULL)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }
	  if (scanf ("%lf %u\n", &current.price, &current.met) != 2)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  /* skip requirements met */
	  for (unsigned j = 0; j < current.met; ++j)
	    if (fgets (req, LENGTH (req), stdin) == NULL)
	      {
		perror (__LOC__);
		exit (EXIT_FAILURE);
	      }

	  if (i == 0 || current.met > best.met
	      || (current.met == best.met && current.price < best.price))
	    best = current;
	}

      if (printf ("RFP #%u\n%s", cur++, best.name) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
