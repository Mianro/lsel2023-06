#include "snake_random.h"

#include <stdlib.h>
#include <time.h>

int
snake_random_init(snake_game_t* p_game)
{
  /* Copy from linux solution */
    srand(time(NULL));
    return 1;
}

int
snake_random_get(int limit)
{
  /* Copy from linux solution */
  return rand()%limit;
  return 1;
}

void
snake_random_close(snake_game_t* p_game)
{
  /* Copy from linux solution */

}
