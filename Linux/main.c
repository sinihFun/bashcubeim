
#include <stdio.h>
#include <ncurses.h>

int main() {
	initscr();
	halfdelay(3);
	int xx, yy, py, px, jump;
	int test = 0;
	char output = ' ';
	char player = '@';
	getmaxyx(stdscr, yy, xx);
	noecho();
	FILE *fptr;

	// создание карты
	char map[yy][xx];
	for (int i = 0; i < yy; i++) {
		for (int g = 0; g < xx; g++) {
			map[i][g] = ' ';
		}
	}
	fptr = fopen("save1.txt", "r");
	if (fptr != NULL) { 
		for (int i = 0; i < yy; i++) {
			for (int g = 0; g < xx; g++)
				if (feof(fptr) == 0)
					map[i][g] = fgetc(fptr);
		}
    } 
	else if (fptr == NULL) {
		for (int i = 0; i < xx; i++) {
			map[yy/2][i] = '#';
		}
		map[yy/2-1][15] = '#';
		map[yy/2-1][3] = '#';
		map[yy/2-3][5] = '#';
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
	int dy = yy/2-2;
	int dx = xx/2;
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
				dx++;
			if (output == 'a')
				dx--;
			if (output == 'w')
				dy--;
			if (output == 's')
				dy++;
			mvprintw(dy, dx, "%c", dltchar);

			if (output == 'f')
				map[dy][dx] = ' ';
		}


		//сохранялово
		if (output == 'g') {
			fptr = fopen("save1.txt", "w");
			for (int i = 0; i < yy; i++) {
				for (int g = 0; g < xx; g++)
					fprintf(fptr, "%c", map[i][g]);
			}
			fclose(fptr);
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
