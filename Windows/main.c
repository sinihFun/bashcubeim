
#include <stdio.h>
#include <curses.h>

int main() {
	initscr();
	int xx, yy, py, px;
	int test = 0;
	char output = ' ';
	char player = '@';
	short menustatus = 1;
	short s1ex = 0, s2ex = 0, s3ex = 0, s4ex = 0;
	getmaxyx(stdscr, yy, xx);
	int slotselected = 0;
	noecho();
	curs_set(0);
	FILE *fptr1;
	//вычислить свободные слоты
	fptr1 = fopen("save1.txt", "r");
	if (fptr1 != NULL)
		s1ex = 1;
	fptr1 = fopen("save2.txt", "r");
	if (fptr1 != NULL)
		s2ex = 1;
	fptr1 = fopen("save3.txt", "r");
	if (fptr1 != NULL)
		s3ex = 1;
	fptr1 = fopen("save4.txt", "r");
	if (fptr1 != NULL)
		s4ex = 1;

	halfdelay(3);






	// цикл меню
	while (menustatus) {
		//menustatus 1 - главное меню
		if (menustatus == 1) {
			mvprintw(yy/2-5, xx/2-5, "BASHCUBEIM");

			mvprintw(yy/2-3, xx/2-9, "type 'h' for help!");
			mvprintw(yy/2-2, xx/2-15, "select a save slot! (type 1-4)");
			mvprintw(yy/2-1, xx/2-21, "to erase a slot, try to manually delete it");
			if(!s1ex) {
				mvprintw(yy/2+1, xx/2-7, "slot 1(unused)");
			} else {
				mvprintw(yy/2+1, xx/2-3, "slot 1");
			}
			if(!s2ex) {
				mvprintw(yy/2+2, xx/2-7, "slot 2(unused)");
			} else {
				mvprintw(yy/2+2, xx/2-3, "slot 2");
			}
			if(!s3ex) {
				mvprintw(yy/2+3, xx/2-7, "slot 3(unused)");
			} else {
				mvprintw(yy/2+3, xx/2-3, "slot 3");
			}
			if(!s4ex) {
				mvprintw(yy/2+4, xx/2-7, "slot 4(unused)");
			} else {
				mvprintw(yy/2+4, xx/2-3, "slot 4");
			}
		}

		//menustatus 3 - help menu
		if (menustatus == 3) {
			mvprintw(yy/2-5, xx/2-5, "BASHCUBEIM");

			mvprintw(yy/2-3, xx/2-15, "type 'h' to close this message");

			mvprintw(yy/2-1, xx/2-8, "w,a,d - movement");
			mvprintw(yy/2, xx/2-7, "b - build mode");
			mvprintw(yy/2+1, xx/2-9, "z,c - change block");
			mvprintw(yy/2+2, xx/2-8, "f - place  block");
			mvprintw(yy/2+3, xx/2-8, "x - delete  mode (doesn't work for windows)");
			mvprintw(yy/2+4, xx/2-7, "r - debug info");
			mvprintw(yy/2+5, xx/2-4, "g - save");
		}

		// оутпуты всякие
		output = getch();
		if (output == 'h') {
			if (menustatus == 3) {
				menustatus = 1;
			} else {
				menustatus = 3;
				output = ' ';
			}
		}
		else if (output == '1') {
            menustatus = 0;
            slotselected = 1;
            output = ' ';
		}
		else if (output == '2') {
            menustatus = 0;
            slotselected = 2;
            output = ' ';
		}
		else if (output == '3') {
            menustatus = 0;
            slotselected = 3;
            output = ' ';
		}
		else if (output == '4') {
            menustatus = 0;
            slotselected = 4;
            output = ' ';
		}
		else if (output == 'q')
			break;
		clear();
	}



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
			map[yy/2-1][15] = '#';
			map[yy/2-1][3] = '#';
			map[yy/2-3][5] = '#';
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
			map[yy/2-1][15] = '#';
			map[yy/2-1][3] = '#';
			map[yy/2-3][5] = '#';
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
			map[yy/2-1][15] = '#';
			map[yy/2-1][3] = '#';
			map[yy/2-3][5] = '#';
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
			map[yy/2-1][15] = '#';
			map[yy/2-1][3] = '#';
			map[yy/2-3][5] = '#';
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
	short devmode = 0;
	short jumppower = 0;
	short buildmode = 0;
	short deletemode = 0;

	// главный цикл
	while (output != 'q') {

		// отрисовка карты
		for (int i = 0; i < yy; i++) {
			for (int g = 0; g < xx; g++) {
				mvprintw(i, g, "%c", map[i][g]);
			}
		}



		//отрисовка игрока, калькулейшон передвижения
		if (output == 'd' && map[py][px+1] == ' ' && !buildmode && !deletemode)
			px++;
		else if (output == 'a' && map[py][px-1] == ' ' && !buildmode && !deletemode)
			px--;
		if (output == 'w' && map[py+1][px] != ' ' && !buildmode && !deletemode)
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
		if (output == 'b' && !buildmode) {
			buildmode = 1;
			deletemode = 0;
			output = ' ';
		}
		if (buildmode && !deletemode && output == 'b')
			buildmode = 0;
		if (buildmode && !deletemode) {
			if (output == 'd')
				bx++;
			if (output == 'a')
				bx--;
			if (output == 'w')
				by--;
			if (output == 's')
				by++;
			if (output == 'z' && bldchar > 0)
				bldchar--;
			if (output == 'c' && bldchar < 30)
				bldchar ++;

			mvprintw(by, bx, "%c", buildchars[bldchar]);


			if (output == 'f')
				map[by][bx] = buildchars[bldchar];
		}


		//делете мод
		if (output == 'x' && !deletemode) {
			buildmode = 0;
			deletemode = 1;
			output = ' ';
		}
		if (deletemode && output == 'x')
			deletemode = 0;
		if (deletemode && !buildmode) {
			if (output == 'd')
				bx++;
			if (output == 'a')
				bx--;
			if (output == 'w')
				by--;
			if (output == 's')
				by++;
			mvprintw(by, bx, "%c", dltchar);

			if (output == 'f')
				map[by][bx] = ' ';
		}


		//сохранялово
		if (output == 'g') {
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
		if (output == 'r' && devmode == 1)
			devmode = 0;
		else if (output == 'r' && devmode == 0)
			devmode = 1;
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
