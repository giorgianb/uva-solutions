#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#define MAX_NBLOCKS 25
#define NO_BLOCK -1
#define MAX_COMMAND_LEN 5

#define MOVE_COMMAND "move"
#define PILE_COMMAND "pile"
#define QUIT_COMMAND "quit"
#define ONTO_DIRECTIVE "onto"
#define OVER_DIRECTIVE "over"

#define LENGTH(arr) (sizeof (arr) / sizeof (arr[0]))

enum
command_type
  {
    MOVE_COMMAND_NUM = (1 << 0),
    PILE_COMMAND_NUM = (1 << 1),
    QUIT_COMMAND_NUM = (1 << 2),
    ONTO_DIRECTIVE_NUM = (1 << 3),
    OVER_DIRECTIVE_NUM = (1 << 4)
  };

size_t
block_position (const int block_pile[], const int block);

void
clear_block_pile (int blocks[MAX_NBLOCKS][MAX_NBLOCKS + 1], size_t location[MAX_NBLOCKS], const int bottom_block);

int
main (void)
{
  int blocks[MAX_NBLOCKS][MAX_NBLOCKS + 1];
  size_t location[MAX_NBLOCKS];
  size_t nblocks;

  if (scanf ("%zu", &nblocks) != 1)
    {
      perror ("101.c: Could not read nblocks");
      exit (EXIT_FAILURE);
    }


  for (size_t i = 0; i < nblocks; ++i)
    {
      location[i] = i;
      blocks[i][0] = i;
      for (size_t j = 1; j < LENGTH (blocks[i]); ++j)
	blocks[i][j] = NO_BLOCK;
    }

  char command[MAX_COMMAND_LEN], directive[MAX_COMMAND_LEN];
  size_t block1, block2;
  int nread;
  while ((nread = scanf ("%5s %zu %5s %zu", command, &block1, directive, &block2)) == 4)
    {
      int cmd;
      if (strcmp (command, MOVE_COMMAND) == 0)
	cmd = MOVE_COMMAND_NUM;
      else if (strcmp (command, PILE_COMMAND) == 0)
	cmd = PILE_COMMAND_NUM;
      else if (strcmp (command, QUIT_COMMAND) == 0)
	cmd = QUIT_COMMAND_NUM;
      else
	{
	  fprintf (stderr, "Unrecognized command: %s\n", command);
	  exit (EXIT_FAILURE);
	}

      if (cmd == QUIT_COMMAND_NUM)
	{
	  fprintf (stderr, "Unexpected parameters for 'quit' command: %zu %s %zu\n", block1, directive, block2);
	  exit (EXIT_FAILURE);
	}

      if (strcmp (directive, ONTO_DIRECTIVE) == 0)
	cmd |= ONTO_DIRECTIVE_NUM;
      else if (strcmp (directive, OVER_DIRECTIVE) == 0)
	cmd |= OVER_DIRECTIVE_NUM;
      else
	{
	  fprintf (stderr, "Unrecognized directive: %s\n", directive);
	  exit (EXIT_FAILURE);
	}

      if (block1 >= nblocks || block2 >= nblocks)
	{
	  fprintf (stderr, "Invalid block specification: %zu %zu\n", block1, block2);
	  exit (EXIT_FAILURE);
	}

      /* ignore illegal commands */
      if (location[block1] == location[block2])
	continue;

      switch (cmd)
	{
	case (MOVE_COMMAND_NUM | ONTO_DIRECTIVE_NUM):
	  /* Return all blocks on top of block2 to their original position */
	  clear_block_pile (blocks, location, block2);
	  /* fall through */
	case (MOVE_COMMAND_NUM | OVER_DIRECTIVE_NUM):
	  {
	    /* Return all blocks on top of block1 to their original position */
	    clear_block_pile (blocks, location, block1);

	    /* move block1 onto block2 */
	    size_t top = block_position (blocks[location[block2]], NO_BLOCK);
	    blocks[location[block2]][top++] = block1;
	    blocks[location[block2]][top++] = NO_BLOCK;

	    /* mark the top of what was block1's stack */
	    blocks[location[block1]][block_position (blocks[location[block1]], block1)] = NO_BLOCK;

	    /* Update block1's location */
	    location[block1] = location[block2];
	    break;
	  }
	case (PILE_COMMAND_NUM | ONTO_DIRECTIVE_NUM):
	  clear_block_pile (blocks, location, block2);
	  /* fall through */
	case (PILE_COMMAND_NUM | OVER_DIRECTIVE_NUM):
	  {
	    const size_t old_pile = location[block1];
	    const size_t b1_pile_begin = block_position (blocks[old_pile], block1); 
	    size_t top = block_position(blocks[location[block2]], NO_BLOCK);

	    for (size_t i = b1_pile_begin; blocks[old_pile][i] != NO_BLOCK && i < 2 * MAX_NBLOCKS; ++i)
	      {

		blocks[location[block2]][top++] = blocks[old_pile][i]; /* move block */
		location[blocks[old_pile][i]] = location[block2]; /* update location of moved block */
		blocks[old_pile][i] = NO_BLOCK; /* mark top of pile for old pile */
	      }

	    blocks[location[block2]][top] = NO_BLOCK; /* mark top of pile for new pile */
	    break;
	  }
	default:
	  fprintf (stderr, "Unexpected command: %d\n", cmd);
	  exit (EXIT_FAILURE);
	}
    }

  if (nread != 1 && strcmp (command, QUIT_COMMAND) == 0)
    {
      perror ("101.c: Error reading command");
      exit (EXIT_FAILURE);
    }

  for (size_t i = 0; i < nblocks; ++i)
    {
      if (printf ("%zu:", i) < 0)
	{
	  perror ("101.c");
	  exit (EXIT_FAILURE);
	}

      for (size_t j = 0; blocks[i][j] != NO_BLOCK; ++j)
	if (printf (" %d", blocks[i][j]) < 0)
	  {
	    perror ("101.c");
	    exit (EXIT_FAILURE);
	  }
      if (putchar ('\n') == EOF)
	{
	  perror ("101.c");
	  exit (EXIT_FAILURE);
	}
    }

  exit (EXIT_SUCCESS);
}
	      

/* clear all blocks above the block specified by "bottom_block" */
void
clear_block_pile (int blocks[MAX_NBLOCKS][MAX_NBLOCKS + 1], size_t location[MAX_NBLOCKS], const int bottom_block)
{
  const size_t pile = location[bottom_block];
  const size_t pos = block_position (blocks[pile], bottom_block);
  const size_t pile_size = block_position (blocks[pile], NO_BLOCK);

  for (size_t i = pos + 1; i < pile_size; ++i)
    {
      const int block = blocks[pile][i]; /* take the block on top of bottom_block */
      size_t top = block_position (blocks[block], NO_BLOCK); /* find the top of its stack */
      blocks[block][top++] = block; /* place the block on top of its stack */
      location[block] = block; /* update the location of the block */
      blocks[block][top++] = NO_BLOCK; /* mark the top of the stack */
      
      blocks[pile][i] = NO_BLOCK; /* update the original stack */
    }
}

size_t
block_position (const int block_pile[], const int block)
{
  size_t pos;
  for (pos = 0; block_pile[pos] != NO_BLOCK && block_pile[pos] != block; ++pos)
    ;

  assert (block_pile[pos] == block);
  return pos;
}
