#ifndef INVENTORY_H
#define INVENTORY_H

#include <curses.h>
#include <stdbool.h>

#include "block.h"

int inv_calc(WINDOW *inv, int by, int bx, bool winprot, int iy, int ix, char output) {
  if (!winprot) {
    inv = newwin(4, 8, by, bx);
    winprot = true;
    box(inv, 0, 0);
  }
  refresh();
  wrefresh(inv);

  int result = 0;

  mvwprintw(inv, 0, 1, "inv");
  
  /* grass */
  wprintblock(inv, 1, 1, 1);

  /* dirt */
  wprintblock(inv, 1, 2, 2);

  /* wood */
  wprintblock(inv, 1, 3, 3);

  /* stone */
  wprintblock(inv, 1, 4, 4);

  /* bricks */
  wprintblock(inv, 1, 5, 5);

  /* ? */
  wprintblock(inv, 1, 6, 6);

  /* red wool */
  wprintblock(inv, 2, 1, 7);

  /* blue wool */
  wprintblock(inv, 2, 2, 8);

  /* white wool */
  wprintblock(inv, 2, 3, 9);

  /* green wool */
  wprintblock(inv, 2, 4, 10);

  /* water */
  wprintblock(inv, 2, 5, 11);

  /* lava */
  wprintblock(inv, 2, 6, 12);


  
  //block names + select
  
  /* grass */
  if(iy == 1 && ix == 1) {
    mvwprintw(inv, 3, 1, "grass");
    result = 0;
  }

  /* dirt */
  if(iy == 1 && ix == 2) {
    mvwprintw(inv, 3, 1, "dirt");
    result = 1;
  }

  /* wood */
  if(iy == 1 && ix == 3) {
    mvwprintw(inv, 3, 1, "wood");
    result = 2;
  }

  /* stone */
  if(iy == 1 && ix == 4) {
    mvwprintw(inv, 3, 1, "stone");
    result = 3;
  }

  /* bricks */
  if(iy == 1 && ix == 5) {
    mvwprintw(inv, 3, 1, "bricks");
    result = 4;
  }

  /* ? */
  if(iy == 1 && ix == 6) {
    mvwprintw(inv, 3, 6, "?");
    result = 5;
  }

  /* red wool */
  if(iy == 2 && ix == 1) {
    mvwprintw(inv, 3, 1, "r-wool");
    result = 6;
  }

  /* blue wool */
  if(iy == 2 && ix == 2) {
    mvwprintw(inv, 3, 1, "b-wool");
    result = 7;
  }

  /* white wool */
  if(iy == 2 && ix == 3) {
    mvwprintw(inv, 3, 1, "w-wool");
    result = 8;
  }

  /* green wool */
  if(iy == 2 && ix == 4) {
    mvwprintw(inv, 3, 1, "g-wool");
    result = 9;
  }

  /* water */
  if(iy == 2 && ix == 5) {
    mvwprintw(inv, 3, 1, "water");
    result = 10;
  }

  /* lava */
  if(iy == 2 && ix == 6) {
    mvwprintw(inv, 3, 1, "lava");
    result = 11;
  }

  wmove(inv, iy, ix);

  wrefresh(inv);
  wclear(inv);

  return (result);
}
#endif
