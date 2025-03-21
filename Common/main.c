
#include <stdio.h>
#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif


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
                        #ifdef _WIN32
			mvprintw(yy/2-1, xx/2-21, "to erase a slot, try to manually delete it");
                        #else
			mvprintw(yy/2-1, xx/2-12, "type 'x' to erase a slot");
                        #endif
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

                #ifdef _WIN32
                #else
		//menustatus 2 - удаление слотов сохранения
		else if (menustatus == 2) {
			mvprintw(yy/2-5, xx/2-5, "BASHCUBEIM");

			mvprintw(yy/2-3, xx/2-9, "type 'h' for help!");
			mvprintw(yy/2-2, xx/2-17, "select a slot to erase! (type 1-4)");
			mvprintw(yy/2-1, xx/2-13, "type 'x' to select a slot!");
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
                #endif

		
		//menustatus 3 - help menu
		if (menustatus == 3) {
			mvprintw(yy/2-5, xx/2-5, "BASHCUBEIM");

			mvprintw(yy/2-3, xx/2-15, "type 'h' to close this message");

			mvprintw(yy/2-1, xx/2-8, "w,a,d - movement");
			mvprintw(yy/2, xx/2-7, "b - build mode");
			mvprintw(yy/2+1, xx/2-9, "z,c - change block");
			mvprintw(yy/2+2, xx/2-8, "f - place  block");
			mvprintw(yy/2+3, xx/2-8, "x - delete  mode");
			mvprintw(yy/2+4, xx/2-7, "r - debug info");
			mvprintw(yy/2+5, xx/2-4, "g - save");
                        #ifdef _WIN32
                        #else
			mvprintw(yy/2+7, xx/2-16, "you can change these in cfg.txt!");
                        #endif
		}

		// оутпуты всякие
		#ifdef _WIN32
		#else
		output = getch();
		if (output == 'x') {
			if (menustatus == 2) {
				menustatus = 1;
			} else {
				menustatus = 2;
				output = ' ';
			}
		}
		else
                #endif
                    if (output == 'h') {
			if (menustatus == 3) {
				menustatus = 1;
			} else {
				menustatus = 3;
				output = ' ';
			}
		}
		else if (output == '1') {
			#ifdef _WIN32
			menustatus = 0;
			slotselected = 1;
			output = ' ';
			#else
			if (menustatus == 2) {
				remove("save1.txt");
				s1ex = 0;
			} else {
				menustatus = 0;
				slotselected = 1;
				output = ' ';
			}
                	#endif
		}
		else if (output == '2') {
			#ifdef _WIN32
			menustatus = 0;
			slotselected = 2;
			output = ' ';
			#else
			if (menustatus == 2) {
				remove("save2.txt");
				s2ex = 0;
			} else {
				menustatus = 0;
				slotselected = 2;
				output = ' ';
			}
                	#endif
		}
		else if (output == '3') {
			#ifdef _WIN32
			menustatus = 0;
			slotselected = 3;
			output = ' ';
			#else
			if (menustatus == 2) {
				remove("save3.txt");
				s3ex = 0;
			} else {
				menustatus = 0;
				slotselected = 3;
				output = ' ';
			}
                	#endif
		}
		else if (output == '4') {
			#ifdef _WIN32
			menustatus = 0;
			slotselected = 4;
			output = ' ';
			#else
			if (menustatus == 2) {
				remove("save4.txt");
				s4ex = 0;
			} else {
				menustatus = 0;
				slotselected = 4;
				output = ' ';
			}
                	#endif
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
	short devmode = 0;
	short jumppower = 0;
	short buildmode = 0;
	short deletemode = 0;

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
			buildmode = 1;
			deletemode = 0;
			output = ' ';
		}
		if (buildmode && !deletemode && output == cfg[5])
			buildmode = 0;
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
			buildmode = 0;
			deletemode = 1;
			output = ' ';
		}
		if (deletemode && output == cfg[6])
			deletemode = 0;
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
		if (output == cfg[10] && devmode == 1) 
			devmode = 0;
		else if (output == cfg[10] && devmode == 0)
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
