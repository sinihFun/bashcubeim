#ifndef BLOCKS_H
#define BLOCKS_H

#include <curses.h>

int printblock(int y, int x, int id)
{
  //init color pairs
  init_pair(1, COLOR_GREEN, COLOR_BLACK);   /*   grass    */
  init_pair(2, COLOR_CYAN, COLOR_BLACK);    /*    dirt    */ /*(color doesnt match)*/
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);  /*    wood    */
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK); /*   stone    */ /*(color doesnt match)*/
  init_pair(5, COLOR_RED, COLOR_BLACK);     /*   bricks   */
  init_pair(6, COLOR_WHITE, COLOR_BLACK);   /*     ?      */
  init_pair(7, COLOR_RED, COLOR_BLACK);     /*  red wool  */
  init_pair(8, COLOR_BLUE, COLOR_BLACK);    /*  blue wool */
  init_pair(9, COLOR_WHITE, COLOR_BLACK);   /* white wool */
  init_pair(10, COLOR_GREEN, COLOR_BLACK);  /* green wool */
  init_pair(11, COLOR_BLUE, COLOR_BLACK);   /*    water   */
  init_pair(12, COLOR_YELLOW, COLOR_BLACK); /*    lava    */

  
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

    /* dirt */
    case 2:
      init_color(COLOR_CYAN, 500, 250, 0);
      attr_on(COLOR_PAIR(2), NULL);
      mvprintw(y, x, "#");
      attr_off(COLOR_PAIR(2), NULL);
      break;

    /* wood */
    case 3:
      attr_on(COLOR_PAIR(3), NULL);
      mvprintw(y, x, "$");
      attr_off(COLOR_PAIR(3), NULL);
      break;

    /* stone */
    case 4:
      init_color(COLOR_MAGENTA, 500, 500, 500);
      attr_on(COLOR_PAIR(4), NULL);
      mvprintw(y, x, "%%");
      attr_off(COLOR_PAIR(4), NULL);
      break;
      
    /* bricks */
    case 5:
      attr_on(COLOR_PAIR(5), NULL);
      mvprintw(y, x, "&");
      attr_off(COLOR_PAIR(5), NULL);
      break;

    /* ? */
    case 6:
      attr_on(COLOR_PAIR(6), NULL);
      mvprintw(y, x, "?");
      attr_off(COLOR_PAIR(6), NULL);
      break;

    /* red wool */
    case 7:
      attr_on(COLOR_PAIR(7), NULL);
      mvprintw(y, x, "W");
      attr_off(COLOR_PAIR(7), NULL);
      break;

    /* blue wool */
    case 8:
      attr_on(COLOR_PAIR(8), NULL);
      mvprintw(y, x, "W");
      attr_off(COLOR_PAIR(8), NULL);
      break;

    /* white wool */
    case 9:
      attr_on(COLOR_PAIR(9), NULL);
      mvprintw(y, x, "W");
      attr_off(COLOR_PAIR(9), NULL);
      break;

    /* green wool */
    case 10:
      attr_on(COLOR_PAIR(10), NULL);
      mvprintw(y, x, "W");
      attr_off(COLOR_PAIR(10), NULL);
      break;

    /* water */
    case 11:
      attr_on(COLOR_PAIR(11), NULL);
      mvprintw(y, x, "~");
      attr_off(COLOR_PAIR(11), NULL);
      break;

    /* lava */
    case 12:
      attr_on(COLOR_PAIR(12), NULL);
      mvprintw(y, x, "~");
      attr_off(COLOR_PAIR(12), NULL);
      break;
      
  }
  
  return 0;
}

int wprintblock(WINDOW *win, int y, int x, int id)
{
  //init color pairs
  init_pair(1, COLOR_GREEN, COLOR_BLACK);   /*   grass    */
  init_pair(2, COLOR_CYAN, COLOR_BLACK);    /*    dirt    */ /*(color doesnt match)*/
  init_pair(3, COLOR_YELLOW, COLOR_BLACK);  /*    wood    */
  init_pair(4, COLOR_MAGENTA, COLOR_BLACK); /*   stone    */ /*(color doesnt match)*/
  init_pair(5, COLOR_RED, COLOR_BLACK);     /*   bricks   */
  init_pair(6, COLOR_WHITE, COLOR_BLACK);   /*     ?      */
  init_pair(7, COLOR_RED, COLOR_BLACK);     /*  red wool  */
  init_pair(8, COLOR_BLUE, COLOR_BLACK);    /*  blue wool */
  init_pair(9, COLOR_WHITE, COLOR_BLACK);   /* white wool */
  init_pair(10, COLOR_GREEN, COLOR_BLACK);  /* green wool */
  init_pair(11, COLOR_BLUE, COLOR_BLACK);   /*    water   */
  init_pair(12, COLOR_YELLOW, COLOR_BLACK); /*    lava    */

  
  //parse ids, etc...
  switch(id) {
    
    /* air */
    case 0:
      mvwprintw(win, y, x, " ");
      break;
      
    /* grass */
    case 1:
      wattr_on(win, COLOR_PAIR(1), NULL);
      mvwprintw(win, y, x, "#");
      wattr_off(win, COLOR_PAIR(1), NULL);
      break;

    /* dirt */
    case 2:
      init_color(COLOR_CYAN, 500, 250, 0);
      wattr_on(win, COLOR_PAIR(2), NULL);
      mvwprintw(win, y, x, "#");
      wattr_off(win, COLOR_PAIR(2), NULL);
      break;

    /* wood */
    case 3:
      wattr_on(win, COLOR_PAIR(3), NULL);
      mvwprintw(win, y, x, "$");
      wattr_off(win, COLOR_PAIR(3), NULL);
      break;

    /* stone */
    case 4:
      init_color(COLOR_MAGENTA, 500, 500, 500);
      wattr_on(win, COLOR_PAIR(4), NULL);
      mvwprintw(win, y, x, "%%");
      wattr_off(win, COLOR_PAIR(4), NULL);
      break;
      
    /* bricks */
    case 5:
      wattr_on(win, COLOR_PAIR(5), NULL);
      mvwprintw(win, y, x, "&");
      wattr_off(win, COLOR_PAIR(5), NULL);
      break;

    /* ? */
    case 6:
      wattr_on(win, COLOR_PAIR(6), NULL);
      mvwprintw(win, y, x, "?");
      wattr_off(win, COLOR_PAIR(6), NULL);
      break;

    /* red wool */
    case 7:
      wattr_on(win, COLOR_PAIR(7), NULL);
      mvwprintw(win, y, x, "W");
      wattr_off(win, COLOR_PAIR(7), NULL);
      break;

    /* blue wool */
    case 8:
      wattr_on(win, COLOR_PAIR(8), NULL);
      mvwprintw(win, y, x, "W");
      wattr_off(win, COLOR_PAIR(8), NULL);
      break;

    /* white wool */
    case 9:
      wattr_on(win, COLOR_PAIR(9), NULL);
      mvwprintw(win, y, x, "W");
      wattr_off(win, COLOR_PAIR(9), NULL);
      break;

    /* green wool */
    case 10:
      wattr_on(win, COLOR_PAIR(10), NULL);
      mvwprintw(win, y, x, "W");
      wattr_off(win, COLOR_PAIR(10), NULL);
      break;

    /* water */
    case 11:
      wattr_on(win, COLOR_PAIR(11), NULL);
      mvwprintw(win, y, x, "~");
      wattr_off(win, COLOR_PAIR(11), NULL);
      break;

    /* lava */
    case 12:
      wattr_on(win, COLOR_PAIR(12), NULL);
      mvwprintw(win, y, x, "~");
      wattr_off(win, COLOR_PAIR(12), NULL);
      break;
      
  }
  
  return 0;
}

#endif
