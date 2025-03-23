#include <stdio.h>
#ifdef _WIN32
#include <curses.h>
#else
#include <ncurses.h>
#endif

int menu(int yy, int xx, FILE *fptr1) {
	short menustatus = 1;
	int slotselected = 0;
	char menuoutput = ' ';
    short s1ex = 0, s2ex = 0, s3ex = 0, s4ex = 0;

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


    //цикл меню лол
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
			mvprintw(yy/2+7, xx/2-16, "you can change these in cfg.txt!");
		}

		// оутпуты всякие
		menuoutput = getch();
		if (menuoutput == 'x') {
			if (menustatus == 2) {
				menustatus = 1;
			} else {
				menustatus = 2;
				menuoutput = ' ';
			}
		}
        if (menuoutput == 'h') {
			if (menustatus == 3) {
				menustatus = 1;
			} else {
				menustatus = 3;
				menuoutput = ' ';
			}
		}
		else if (menuoutput == '1') {
            #ifdef _WIN32
			menustatus = 0;
			slotselected = 1;
			menuoutput = ' ';
            #else
            if (menustatus == 2) {
				remove("save1.txt");
				s1ex = 0;
			} else {
				menustatus = 0;
				slotselected = 1;
				menuoutput = ' ';
			}
            #endif
		}
		else if (menuoutput == '2') {
            #ifdef _WIN32
			menustatus = 0;
			slotselected = 2;
			menuoutput = ' ';
            #else
            if (menustatus == 2) {
				remove("save2.txt");
				s2ex = 0;
			} else {
				menustatus = 0;
				slotselected = 2;
				menuoutput = ' ';
			}
            #endif
		}
		else if (menuoutput == '3') {
            #ifdef _WIN32
			menustatus = 0;
			slotselected = 3;
			menuoutput = ' ';
            #else
            if (menustatus == 2) {
				remove("save3.txt");
				s3ex = 0;
			} else {
				menustatus = 0;
				slotselected = 3;
				menuoutput = ' ';
			}
            #endif
		}
		else if (menuoutput == '4') {
            #ifdef _WIN32
			menustatus = 0;
			slotselected = 4;
			menuoutput = ' ';
            #else
            if (menustatus == 2) {
				remove("save4.txt");
				s4ex = 0;
			} else {
				menustatus = 0;
				slotselected = 4;
				menuoutput = ' ';
			}
            #endif
		}
		else if (menuoutput == 'q')
			break;
		clear();
	}
    return (slotselected);
}
