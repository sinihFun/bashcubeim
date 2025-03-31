
#include <stdio.h>
#include <stdbool.h>

#include "menu.h"
#include "block.h"
#include "inventory.h"

#include <curses.h>

int main() {
  initscr();
  start_color();
  WINDOW *inv;
  bool winprot = false;
  int yy, xx, py, px;
  char output = ' ';
  char player = '@';
  getmaxyx(stdscr, yy, xx);
  int slotselected;
  noecho();
  curs_set(0);
  FILE *fptr1;

  
  char cfg[] = "qadwsbxzcfrge";
  char cfgchar;
  short cfgkeycount = 0;
  fptr1 = fopen("cfg.txt", "r");
  if (fptr1 == NULL) {
    fptr1 = fopen("cfg.txt", "w");
    fprintf(fptr1, "quit:q\nleft:a\nright:d\njump/up:w\ndown:s\nbuild:b\ndelete:x\nchange block 1:z\nchange block 2:c\nplace:f\ndebug:r\nsave:g\ninventory:e");
    fclose(fptr1);
  } else {
    for (int i = 0; i < 140; i++) {
      cfgchar = fgetc(fptr1);
      if (cfgchar == ':') {
        cfgchar = fgetc(fptr1);
        cfg[cfgkeycount] = cfgchar;
        cfgkeycount++;
      }
    }
  }





  halfdelay(3);
  slotselected = menu(yy, xx, fptr1);

  if (slotselected == 0)
    output = 'q';



  // создание карты
  char map[yy][xx];
  for (int i = 0; i < yy; i++) {
    for (int g = 0; g < xx; g++) {
      map[i][g] = 0;
    }
  }
  if (slotselected == 1) {
    fptr1 = fopen("save1.txt", "r");
    if (fptr1 != NULL) {
      for (int i = 0; i < yy; i++) {
        for (int g = 0; g < xx; g++)
          if (feof(fptr1) == 0)
            map[i][g] = fgetc(fptr1);
      }
    }
    else if (fptr1 == NULL) {
      for (int i = 0; i < xx; i++) {
        map[yy/2][i] = 1;
      }
    }
  }
  if (slotselected == 2) {
    fptr1 = fopen("save2.txt", "r");
    if (fptr1 != NULL) {
      for (int i = 0; i < yy; i++) {
        for (int g = 0; g < xx; g++)
          if (feof(fptr1) == 0)
            map[i][g] = fgetc(fptr1);
      }
    }
    else if (fptr1 == NULL) {
      for (int i = 0; i < xx; i++) {
        map[yy/2][i] = 1;
      }
    }
  }
  if (slotselected == 3) {
    fptr1 = fopen("save3.txt", "r");
    if (fptr1 != NULL) {
      for (int i = 0; i < yy; i++) {
        for (int g = 0; g < xx; g++)
          if (feof(fptr1) == 0)
            map[i][g] = fgetc(fptr1);
      }
    }
    else if (fptr1 == NULL) {
      for (int i = 0; i < xx; i++) {
        map[yy/2][i] = 1;
      }
    }
  }
  if (slotselected == 4) {
    fptr1 = fopen("save4.txt", "r");
    if (fptr1 != NULL) {
      for (int i = 0; i < yy; i++) {
        for (int g = 0; g < xx; g++)
          if (feof(fptr1) == 0)
            map[i][g] = fgetc(fptr1);
      }
    }
    else if (fptr1 == NULL) {
      for (int i = 0; i < xx; i++) {
        map[yy/2][i] = 1;
      }
    }
  }


  // задаём главные переменные заново (оперативная памаять алес капут)
  py = (yy/2)-1;
  px = 5;
  player = '@';
  int buildchars[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int bldchar = 0;
  char dltchar = 'x';
  int by = yy/2-2;
  int bx = xx/2;
  int iy = 1, ix = 1;
  short jumppower = 0;
  bool buildmode = false;
  bool deletemode = false;
  bool invmode = false;
  bool saved = true;

  // главный цикл
  while (output != cfg[0]) {

    // отрисовка карты
    for (int i = 0; i < yy; i++) {
      for (int g = 0; g < xx; g++) {
        printblock(i, g, map[i][g]);
      }
    }
    winprot = false;

    //отрисовка игрока, калькулейшон передвижения
    if (output == cfg[2] && map[py][px+1] == 0 && !buildmode && !deletemode && !invmode)
      px++;
    else if (output == cfg[1] && map[py][px-1] == 0 && !buildmode && !deletemode && !invmode)
      px--;
    if (output == cfg[3] && map[py+1][px] != 0 && !buildmode && !deletemode && !invmode)
      jumppower = 3;
    if (map[py-1][px] != 0)
      jumppower = 0;
    if (jumppower > 0) {
      py--;
      jumppower--;
    }
    if (jumppower == 0 && map[py+1][px] == 0)
      py++;
    mvprintw(py, px, "%c", player);

    if(invmode && output == cfg[12]) {
      invmode = false;
      buildmode = true;
      output = ' ';
      curs_set(0);
      halfdelay(3);
    }


    //билд мод
    if (output == cfg[5] && !buildmode) {
      buildmode = true;
      deletemode = false;
      output = ' ';
    }
    if (buildmode && !deletemode && output == cfg[5])
      buildmode = false;
    if (buildmode && !deletemode) {
      if (output == cfg[2])
        bx++;
      if (output == cfg[1])
        bx--;
      if (output == cfg[3])
        by--;
      if (output == cfg[4])
        by++;
      if (output == cfg[7] && bldchar > 0)
        bldchar--;
      if (output == cfg[8] && bldchar < 11)
        bldchar ++;

      printblock(by, bx, buildchars[bldchar]);


      if (output == cfg[9]) {
        map[by][bx] = buildchars[bldchar];
	saved = false;
      }
    }


    //делете мод
    if (output == cfg[6] && !deletemode) {
      buildmode = false;
      deletemode = true;
      output = ' ';
    }
    if (deletemode && output == cfg[6])
      deletemode = false;
    if (deletemode && !buildmode) {
      if (output == cfg[2])
        bx++;
      if (output == cfg[1])
        bx--;
      if (output == cfg[3])
        by--;
      if (output == cfg[4])
        by++;
      mvprintw(by, bx, "%c", dltchar);

      if (output == cfg[9]) {
        map[by][bx] = 0;
	saved = false;
      }
    }


    //сохранялово
    if (output == cfg[11]) {
      saved = true;
      if (slotselected == 1) {
        fptr1 = fopen("save1.txt", "w");
        for (int i = 0; i < yy; i++) {
          for (int g = 0; g < xx; g++)
            fprintf(fptr1, "%c", map[i][g]);
        }
        fclose(fptr1);
      }
      if (slotselected == 2) {
        fptr1 = fopen("save2.txt", "w");
        for (int i = 0; i < yy; i++) {
          for (int g = 0; g < xx; g++)
            fprintf(fptr1, "%c", map[i][g]);
        }
        fclose(fptr1);
      }
      if (slotselected == 3) {
        fptr1 = fopen("save3.txt", "w");
        for (int i = 0; i < yy; i++) {
          for (int g = 0; g < xx; g++)
            fprintf(fptr1, "%c", map[i][g]);
        }
        fclose(fptr1);
      }
      if (slotselected == 4) {
        fptr1 = fopen("save4.txt", "w");
        for (int i = 0; i < yy; i++) {
          for (int g = 0; g < xx; g++)
            fprintf(fptr1, "%c", map[i][g]);
        }
        fclose(fptr1);
      }
      mvprintw(0, xx-6, "saved!");
    }


    if(!saved)
      mvprintw(0, xx-1, "*");


    if(buildmode && !invmode && output == cfg[12]) {
      buildmode = false;
      invmode = true;
      output = ' ';
      curs_set(1);
      halfdelay(100);
    }
      
    if(invmode) {
    
      if(output == 'a' && ix > 1)
        ix--;
      else if(output == 'd' && ix < 6)
        ix++;
      else if(output == 'w' && iy > 1)
        iy--;
      else if(output == 's' && iy < 2)
        iy++;
      
      bldchar = inv_calc(inv, by, bx, winprot, iy, ix, output);
      move(by+iy, bx+ix);
    }
    output = getch();
    clear();
  }
  endwin();
  return 0;
}
