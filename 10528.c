/* Problem URL: https://uva.onlinejudge.org/external/100/10082.pdf */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>

#define STR(X) #X
#define XSTR(X) STR(X)
#define __LOC__ __FILE__ ":" XSTR (__LINE__)
#define __LOC_PRE__ __LOC__ ": "

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

enum note
{
  A = 1 << 0,
  A_SHARP = 1 << 1,
  B = 1 << 2,
  C = 1 << 3,
  C_SHARP = 1 << 4,
  D = 1 << 5,
  D_SHARP = 1 << 6,
  E = 1 << 7,
  E_SHARP = 1 << 8,
  F = 1 << 9,
  F_SHARP = 1 << 10,
  G = 1 << 11,
  G_SHARP = 1 << 12
};

const char *note_to_string (const enum note note);
enum note char_to_note (const char c);

int
main (void)
{
  const enum note notes[] =
  { C, C_SHARP, D, D_SHARP, E, F, F_SHARP, G, G_SHARP, A, A_SHARP, B };
  const size_t offsets[] = { 1, 2, 2, 2, 1, 2 };	/* half, whole, whole, whole, half, whole */
  uint16_t scales[G_SHARP + 1];

  /* initialize scale. scale[note] returns a bitmask of all the scales containing said note */
  for (size_t i = 0; i < LENGTH (notes); ++i)
    {
      const enum note note = notes[i];
      size_t cur = i;
      scales[note] = note;
      for (size_t j = 0; j < LENGTH (offsets); ++j)
	{
	  cur += offsets[j];
	  scales[note] |= notes[cur % LENGTH (notes)];
	}
    }

  int c;
  enum note note;
  uint16_t scale = ~((uint16_t) 0);
  while ((c = getchar ()) != EOF)
    {
      /* hit the end in the word "END" */
      if (c == 'N')
	break;

      if (isalpha (c))
	note = char_to_note (c);
      else if (c == '#')
	note = (enum note) (note << 1);
      else if (c == ' ')
	scale &= scales[note];
      else if (c == '\n')
	{
	  scale &= scales[note];
	  bool first = true;
	  for (size_t i = 0; i < LENGTH (notes); ++i)
	    if (scale & notes[i])
	      {
		if (printf
		    ("%s%s", (first) ? "" : " ",
		     note_to_string (notes[i])) < 0)
		  {
		    perror (__LOC__);
		    exit (EXIT_FAILURE);
		  }
		first = false;
	      }
	  putchar ('\n');
	  scale = ~((uint16_t) 0);
	}
    }

  exit (EXIT_SUCCESS);
}

const char *
note_to_string (const enum note note)
{
  switch (note)
    {
    case C:
      return "C";
    case C_SHARP:
      return "C#";
    case D:
      return "D";
    case D_SHARP:
      return "D#";
    case E:
      return "E";
    case F:
      return "F";
    case F_SHARP:
      return "F#";
    case G:
      return "G";
    case G_SHARP:
      return "G#";
    case A:
      return "A";
    case A_SHARP:
      return "A#";
    case B:
      return "B";
    default:
      fprintf (stderr, __LOC_PRE__ "Unexpected note: %d.\n", note);
      exit (EXIT_FAILURE);
    }
}

enum note
char_to_note (const char c)
{
  switch (c)
    {
    case 'C':
      return C;
    case 'D':
      return D;
    case 'E':
      return E;
    case 'F':
      return F;
    case 'G':
      return G;
    case 'A':
      return A;
    case 'B':
      return B;
    default:
      fprintf (stderr, __LOC_PRE__ "Unexpected char: %d.\n", c);
      exit (EXIT_FAILURE);
    }
}
