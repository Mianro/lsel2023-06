#include "snake_display.h"

#define _GNU_SOURCE

#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_X 32
#define MAX_Y 32

struct fb_t {
  char pixel[MAX_Y][MAX_X];
};
static struct fb_t fb_s;
static struct fb_t* fb = &fb_s;

static void
clear_screen()
{
  printf("\e[1;1H\e[2J");
  fsync(1);
}

static void
print_hlimit(snake_game_t* p_game)
{

  printf("+");
  for (int i = 0; i < p_game->limits.x; i++) {
    printf("-");
  }
  printf("+\r\n");
}


static void
print_row(snake_game_t* p_game, int y)
{
  printf("|");

  /* TODO print row of game from fb struct */


  for (int x = 0; x < p_game->limits.x; x++) {
    switch(fb->pixel[x][y]){
    case '*':
      printf("\033[31m%c\033[0m", fb->pixel[x][y]);
      break;
    case'o':
      printf("\033[34m%c\033[0m", fb->pixel[x][y]);
      break; 
    case '@':
      printf("\033[32m%c\033[0m", fb->pixel[x][y]);
      break; 
    default:
      printf("%c",fb->pixel[x][y]);
      break; 
    }
  }

    //for (int x = 0; x < p_game->limits.x; x++) {

      //printf("%c",fb->pixel[x][y]);
    //}

  printf("|\r\n");
}


void 
snake_display_render(snake_game_t* p_game)
{
  /* Change: Each element is a char */
  /* - Apple is '*' */
  /* - Snake head is '@' */
  /* - Snake body 'o' */
  /* - Empty pixels are ' ' */
  struct segment_t *seg_i;

  /* Set Blank */
  memset(fb, ' ', sizeof(struct fb_t));

  /* TODO Set Apple */

  /* TODO Set snake body */

  /* TODO Set snake head */
  	fb->pixel[p_game->apple.x][p_game->apple.y]='*';
	for(seg_i = p_game->snake.tail; seg_i->next; seg_i=seg_i->next) {
		fb->pixel[seg_i->x][seg_i->y] = 'o';
	}

  fb->pixel[seg_i->x][seg_i->y]='@';
  
  clear_screen();
  print_hlimit(p_game); 

  /* TODO Print every row with print_row */
  for(int y=0; y< p_game->limits.x;y++){
  print_row(p_game,y);
  }

  print_hlimit(p_game); 
}

int
snake_display_init(snake_game_t* p_game)
{
  /* TODO Set limits */
  p_game->limits.x = 32;
  p_game->limits.y = 32;

  return 1;
}

void
snake_display_close(snake_game_t* p_game)
{
  clear_screen();

}
