#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

int
main (void)
{
  int bound1, bound2;
  
  while (scanf ("%d %d", &bound1, &bound2) == 2)
    {
      int low, high;
      low = (bound1 < bound2) ? bound1 : bound2;
      high = (bound1 < bound2) ? bound2 : bound1;

      int max = 0;
      for (int i = low; i <= high; ++i)
	{
	  int n = i;
	  int len = 1;
	  while (n != 1)
	    {
	      if (n % 2 == 1)
		n = 3*n + 1;
	      else
		n /= 2;
	      ++len;
	    }
	  max = (len > max) ? len : max;
	}
      if (printf("%d %d %d\n", bound1, bound2, max) < 0)
	{
	  perror("100.c");
	  exit(EXIT_FAILURE);
	}
    }

  exit(EXIT_SUCCESS);
}
