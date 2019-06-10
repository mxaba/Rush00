
#include "Main.hpp"

Playground::Playground(void):clr(0) {
	initscr();
	system("printf '\e[8;50;100t'");
	mWind = stdscr;
	noecho();
	curs_set(FALSE);
	raw();
	keypad(stdscr, TRUE);
	getmaxyx(mWind, mSizey, mSizex);
	nodelay(stdscr, TRUE);
	if (has_colors() == FALSE) {
		endwin();
		std::cout << "your terminal window doesn't have colors." << std::endl;
		exit(1);
	}
	return;
}

Playground::Playground(Playground const & src) {
	*this = src;
	return;
}

Playground::~Playground(void) {
	endwin();
	return;
}

void	Playground::setClr(int i) { clr = i; }

int 	Playground::getX(void)const { return(mSizex - 1); }

int 	Playground::getY(void)const { return(mSizey - 1); }

WINDOW* Playground::getWindow(void)const { return(mWind); }

void	Playground::printBorder() {
	if (clr == 1) {
		start_color();
		init_pair(12, COLOR_GREEN, COLOR_GREEN);
		attron(COLOR_PAIR(12));
	}

	if (clr == 2) {
		start_color();
		init_pair(14, COLOR_RED, COLOR_RED);
		attron(COLOR_PAIR(14));
	}

	for (int i = 0; i < mSizex; i++)
		mvprintw(getX(), i, "-");
	for (int i = 0; i < mSizex; i++)
		mvprintw(getY(), i, "-");
	for (int i = 0; i < mSizex; i++)
		mvprintw(i, 0, "|");
	for (int i = 0; i < mSizex; i++)
		mvprintw(i, getX(), "|");
	attroff(COLOR_PAIR(14));
	attroff(COLOR_PAIR(12));
}

void 	Playground::takeWindSize(void) {
	getmaxyx(mWind, mSizey, mSizex);
	if (mSizey < 50 || mSizex < 100)
		system("printf '\e[8;50;100t'");
	printBorder();
	refresh();
}

Playground& Playground::operator=(Playground const & rhs) {
	mSizex = rhs.getX() + 1;
	mSizey = rhs.getY() + 1;
	mWind = rhs.getWindow();
	return (*this);
}
