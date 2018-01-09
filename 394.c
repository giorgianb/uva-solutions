#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define MAXNAMELEN 10
#define MAXNDIMS 10

struct bound
{
  int low;
  int high;
};

typedef struct bound bound_t;

struct array
{
  char name[MAXNAMELEN + 1];
  size_t ndims;
  int base;
  unsigned elem_size;

  bound_t bounds[MAXNDIMS];
};

typedef struct array array_t;

int array_name_cmp (const void *const p1, const void *const p2);

int array_name_find (const void *const name, const void *const array);

int
main (void)
{
  unsigned narrays, nrefs;
  array_t *arrays = NULL;

  if (scanf ("%u %u", &narrays, &nrefs) != 2)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  if ((arrays = (array_t *) malloc (narrays * sizeof *arrays)) == NULL)
    {
      perror (__LOC__);
      exit (EXIT_FAILURE);
    }

  for (unsigned i = 0; i < narrays; ++i)
    {
      if (scanf ("%10s %d %u %zu",
		 arrays[i].name,
		 &arrays[i].base, &arrays[i].elem_size,
		 &arrays[i].ndims) != 4)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      for (size_t j = 0; j < arrays[i].ndims; ++j)
	if (scanf
	    ("%d %d", &arrays[i].bounds[j].low,
	     &arrays[i].bounds[j].high) != 2)
	  {
	    perror (__LOC__);
	    exit (EXIT_FAILURE);
	  }
    }

  qsort (arrays, narrays, sizeof *arrays, array_name_cmp);

  for (unsigned i = 0; i < nrefs; ++i)
    {
      char name[MAXNAMELEN + 1];

      if (scanf ("%10s", name) != 1)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      const array_t *array = (array_t *) bsearch (name, arrays, narrays,
						  sizeof *arrays,
						  array_name_find);
      assert (array != NULL);

      int C[MAXNDIMS];

      C[array->ndims - 1] = array->elem_size;
      for (size_t j = array->ndims - 1; j > 0; --j)
	C[j - 1] = C[j] * (array->bounds[j].high - array->bounds[j].low + 1);

      int address = array->base;
      for (size_t j = 0; j < array->ndims; ++j)
	address -= C[j] * array->bounds[j].low;

      if (printf ("%s[", array->name) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}

      for (size_t j = 0; j < array->ndims; ++j)
	{
	  int index;
	  if (scanf ("%d", &index) != 1)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  if (printf ("%s%d", (j != 0) ? ", " : "", index) < 0)
	    {
	      perror (__LOC__);
	      exit (EXIT_FAILURE);
	    }

	  address += C[j] * index;
	}
      if (printf ("] = %d\n", address) < 0)
	{
	  perror (__LOC__);
	  exit (EXIT_FAILURE);
	}
    }

  free (arrays);
  exit (EXIT_SUCCESS);
}


int
array_name_cmp (const void *const p1, const void *const p2)
{
  return strcmp (((const array_t *) p1)->name, ((const array_t *) p2)->name);
}

int
array_name_find (const void *const name, const void *const array)
{
  return strcmp ((const char *) name, ((const array_t *) array)->name);
}
