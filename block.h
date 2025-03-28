#ifndef BLOCKS_H
#define BLOCKS_H

#include <curses.h>

int printblock(int y, int x, int id)
{
  //init color pairs
  init_pair(1, COLOR_GREEN, COLOR_BLACK); /* grass */
  init_pair(2, COLOR_RED, COLOR_BLACK);  /*  wood   */
  
  //parse ids, etc...
  switch(id) {
    
    /* air */
    case 0:
      mvprintw(y, x, " ");
      break;
      
    /* grass */
    case 1:
      attr_on(COLOR_PAIR(1), NULL);
      mvprintw(y, x, "#");
      attr_off(COLOR_PAIR(1), NULL);
      break;

    /* wood */
    case 2:
      attr_on(COLOR_PAIR(2), NULL);
      mvprintw(y, x, "$");
      attr_off(COLOR_PAIR(2), NULL);
      break;
  }
  
  return 0;
}





























#endif
