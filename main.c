
#include <stdio.h>
#include <stdbool.h>
#include "menu.h"
#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif


int main() {
        initscr();
	int yy, xx, py, px;
	int test = 0;
	char output = ' ';
	char player = '@';
	getmaxyx(stdscr, yy, xx);
	int slotselected;
	noecho();
	curs_set(0);
	FILE *fptr1;
	char cfg[] = "qadwsbxzcfrg";
	char cfgchar;
	short cfgkeycount = 0;
	fptr1 = fopen("cfg.txt", "r");
	if (fptr1 == NULL) {
		fptr1 = fopen("cfg.txt", "w");
		fprintf(fptr1, "quit:q\n left:a\n right:d\n jump/up:w\n down:s\n build:b\n delete:x\n change block 1:z\n change block 2:c\n place:f\n debug:r\n save:g");
		fclose(fptr1);
	} else {
		for (int i = 0; i < 134; i++) {
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
			map[i][g] = ' ';
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
				map[yy/2][i] = '#';
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
				map[yy/2][i] = '#';
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
				map[yy/2][i] = '#';
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
				map[yy/2][i] = '#';
			}
		}
	}


	// задаём главные переменные заново (оперативная памаять алес капут)
	py = (yy/2)-1;
	px = 5;
	test = 0;
	player = '@';
	char buildchars[] = "#$!&ABCDEFGHIJKLMNOPRSQTUWVXYZ";
	int bldchar = 0;
	char dltchar = 'x';
	int by = yy/2-2;
	int bx = xx/2;
	bool devmode = false;
	short jumppower = 0;
	bool buildmode = false;
	bool deletemode = false;

	// главный цикл
	while (output != cfg[0]) {

		// отрисовка карты
		for (int i = 0; i < yy; i++) {
			for (int g = 0; g < xx; g++) {
				mvprintw(i, g, "%c", map[i][g]);
			}
		}



		//отрисовка игрока, калькулейшон передвижения
		if (output == cfg[2] && map[py][px+1] == ' ' && !buildmode && !deletemode)
			px++;
		else if (output == cfg[1] && map[py][px-1] == ' ' && !buildmode && !deletemode)
			px--;
		if (output == cfg[3] && map[py+1][px] != ' ' && !buildmode && !deletemode)
			jumppower = 3;
		if (map[py-1][px] != ' ')
			jumppower = 0;
		if (jumppower > 0) {
			py--;
			jumppower--;
		}
		if (jumppower == 0 && map[py+1][px] == ' ')
			py++;
		mvprintw(py, px, "%c", player);


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
			if (output == cfg[8] && bldchar < 30)
				bldchar ++;

			mvprintw(by, bx, "%c", buildchars[bldchar]);


			if (output == cfg[9])
				map[by][bx] = buildchars[bldchar];
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

			if (output == cfg[9])
				map[by][bx] = ' ';
		}


		//сохранялово
		if (output == cfg[11]) {
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
		}


		//системная инфа
		if (output == cfg[10] && devmode == true)
			devmode = false;
		else if (output == cfg[10] && devmode == false)
			devmode = true;
		if (devmode == 1) {
			mvprintw(0, 0, "resize window to increase map size!");
			mvprintw(1, 0, "this window has been updated %d times", test);
			mvprintw(2, 0, "plr coords: %d %d", py, px);
			if (buildmode)
				mvprintw(3, 0, "buildmode");
			else if (deletemode)
				mvprintw(3, 0, "deletemode");
		}




		test++;
		output = getch();
		clear();
	}
	endwin();
}
