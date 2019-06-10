
#include <numeric>
#include "Main.hpp"

int		hight_score = 0;

int		difficultyMode(int i) {
	if (i == 0)
		return 30;
	else if (i == 1)
		return 100;
	else
		return 300;
}

void	printDead(Playground & pl, Champ ch) {
	(void)ch;
	start_color();
	init_pair(6 ,COLOR_MAGENTA ,COLOR_BLACK);
	init_pair(12 ,COLOR_WHITE ,COLOR_BLACK);
	attron(COLOR_PAIR(6));
	int y = 10;                       
  mvprintw(y++, 27, "               \\`*-.");                    
  mvprintw(y++, 27, "               )  _`-.   ");              
  mvprintw(y++, 27, "              .  : `. .       ");         
  mvprintw(y++, 27, "              : _   '  \\       ");        
  mvprintw(y++, 27, "              ; *` _.   `*-._        ");  
  mvprintw(y++, 27, "              `-.-'          `-.       ");
  mvprintw(y++, 27, "                ;       `       `.     ");
  mvprintw(y++, 27, "                :.       .        \\    ");
  mvprintw(y++, 27, "                . \\  .   :   .-'   .   ");
  mvprintw(y++, 27, "                '  `+.;  ;  '      :   ");
  mvprintw(y++, 27, "                :  '  |    ;       ;-. ");
  mvprintw(y++, 27, "                ; '   : :`-:     _.`* ;");
  mvprintw(y++, 27, "             .*' /  .*' ; .*`- +'  `*' ");
   mvprintw(y+=3, 27, "            `*-*   `*-*  `*-*' ");
	attron(COLOR_PAIR(12));
   mvprintw(y++, 27, "________________________________________");
   mvprintw(y++, 27, "|          SORRY, YOU ARE DEAD          |");
   mvprintw(y++, 27, "|_______________________________________|");
   attron(COLOR_PAIR(12));

	attroff(COLOR_PAIR(6));
	refresh();
	if (COLS != 50 || LINES != 100)
	{
		system("printf '\e[8;50;100t'");
		sleep(4);
		 refresh();
	}
	sleep(4);
}

void	game(int i, Playground& pl) {
	nodelay(stdscr, TRUE);
	i = difficultyMode(i);
	Champ		champ(pl);
	Enemy enemy = Enemy(i, "[-*-]");
	Jet jet = Jet(10, "*");
	Bullet bullet = Bullet(2, "[]");
	enemy.randomBoom(pl);
	int	inp = 0;
	champ.setZeroScore();
	while (inp != KEY_ESC && champ.getHP() > 0) {
		clear();
		pl.takeWindSize();
		pl.printBorder();
		inp = getch();
		jet.start(champ.getX(), champ.getY(), inp);
		bullet.start(champ.getX(), champ.getY(), inp);
		jet.checkDamage(enemy.getHorde(), enemy.getNum(), pl);
		bullet.checkDamage(enemy.getHorde(), enemy.getNum(), pl);
		champ.checkEnemies(enemy.getHorde(), enemy.getNum(), pl);
		champ.printLives(pl);
		jet.printCharge(pl);
		bullet.printCharge(pl);
		if (champ.getHP() > 0) {
			enemy.printIt(pl);
			jet.move(pl);
			bullet.move(pl);
			jet.printIt(pl);
			bullet.printIt(pl);
			champ.printIt(pl);
			champ.inputDirection(inp);
			wrefresh(pl.getWindow());
			champ.move(pl);
			champ.printIt(pl);
			enemy.move(pl);
		}
		while(getch() != ERR);
		usleep(60000);
	}
	if (champ.getHP() <= 0) {
		clear();
		printDead(pl, champ);
	}
	if (champ.getScore() > hight_score)
		hight_score = champ.getScore();

}

void	printLogo(Playground pl) {
	start_color();
	init_pair(1,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(4, 32, " ____________________________________");
	mvprintw(5, 32, "|           SPACE INVADERS           |");
	mvprintw(6, 32, "|____________________________________|");
	attroff(COLOR_PAIR(1));
}

void	printMenu(Playground & pl) {
	int inp = 0;
	int i = 0;

	while (getch() != ERR);
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_GREEN,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_RED);
	while(inp != KEY_ESC) {
		refresh();
		if (COLS < 50 || LINES < 100)
			system("printf '\e[8;50;100t'");
		refresh();
		nodelay(stdscr, FALSE);
		clear();
		printLogo(pl);
		attron(COLOR_PAIR(2));
		if (i == 0) {
			attron(COLOR_PAIR(3));
			mvprintw(8, 47, " ______ ");
			mvprintw(9, 47, "| EASY |");
			mvprintw(10, 47, "|______|");

			attroff(COLOR_PAIR(3));
			attron(COLOR_PAIR(2));
		} else {
			mvprintw(8, 47, " ______ ");
			mvprintw(9, 47, "| EASY |");
			mvprintw(10, 47, "|______|");
		}
		
		if (i == 1) {
			attron(COLOR_PAIR(3));
			mvprintw(15, 47, " ______ ");
			mvprintw(16, 47, "| NORM |");
			mvprintw(17, 47, "|______|");

			attroff(COLOR_PAIR(3));
			attron(COLOR_PAIR(2));
		} else {
			mvprintw(15, 47, " ______ ");
			mvprintw(16, 47, "| NORM |");
			mvprintw(17, 47, "|______|");
		}
		
		if (i == 2) {
			attron(COLOR_PAIR(3));
			mvprintw(22, 47, " ______ ");
			mvprintw(23, 47, "| HARD |");
			mvprintw(24, 47, "|______|");

			attroff(COLOR_PAIR(3));
			attron(COLOR_PAIR(2));
		} else {
			mvprintw(22, 47, " ______ ");
			mvprintw(23, 47, "| HARD |");
			mvprintw(24, 47, "|______|");
		}
		
		if (i == 3) {
			attron(COLOR_PAIR(3));
			mvprintw(29, 47, " ______ ");
			mvprintw(30, 47, "| EXIT |");
			mvprintw(31, 47, "|______|");

			attroff(COLOR_PAIR(3));
			attron(COLOR_PAIR(2));
		} else {
			mvprintw(29, 47, " ______ ");
			mvprintw(30, 47, "| EXIT |");
			mvprintw(31, 47, "|______|");
		}
		attroff(COLOR_PAIR(2));

		inp = getch();
		if (inp == 259) {
			i--;
			if (i == -1)
				i = 3;
		} else if (inp == 258) {
			i++;
			if (i == 4)
				i = 0;
		} else if (inp == 10) {
			if (i >= 0 && i < 3)
				game(i, pl);
			else
				return;
		}
		refresh();
	}
}

void	menu(void) {
	srand(time(NULL));
	Playground pl;
	clear();
	start_color();
	init_pair(1,COLOR_BLUE,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	printLogo(pl);
	printMenu(pl);
	attroff(COLOR_PAIR(1));
	refresh();
}

int main(void) {
	menu();
}
