
#include "Champ.hpp"
#include <iostream>

Champ::Champ(void):Object() { return; }

Champ::Champ(Playground& pl):Object((pl.getX() / 2), (pl.getY() - 5), 0, 0, 1, 3, "//*\\\\") { return; }

Champ::Champ(Champ const & src):Object(src) {
	*this = src;
	return;
}

Champ::~Champ(void) { return; }

void				Champ::printIt(Playground& pl)const {
	start_color();
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	attron(COLOR_PAIR(5));
	if (mPosX >= 0 && mPosX <= pl.getX() && mPosY > 0 && mPosY < pl.getY() && mHP > 0)
		mvwprintw(pl.getWindow(), mPosY, mPosX, mForm.data());
	attroff(COLOR_PAIR(5));
}


void Champ::inputDirection(int ch) {
	this->input = 1;
	if (ch == 259 || ch == 258)
		ch == 258 ? mDirY += 1 : mDirY -= 1;
	else if (ch == 260 || ch == 261)
		ch == 261 ?  mDirX += 2 : mDirX -= 2;
	if (mDirX < -2)
		mDirX = -2;
	if (mDirX > 2)
		mDirX = 2;
	if (mDirY < -1)
		mDirY = -1;
	if (mDirY > 1)
		mDirY = 1;
}

void Champ::move(Playground& pl) {
	this->input = !this->input;
	mPosY += (mDirY * mSpeed);
	mPosX += (mDirX * mSpeed);
	if (mPosY <= 0)
		mPosY = 1;
	if (mPosY >= pl.getY() - 1)
		mPosY = pl.getY() - 1;
	if (mPosX <= 0)
		mPosX = 1;
	if (mPosX >= pl.getX() - 1)
		mPosX = pl.getX() - 2;
	if (this->input)
	 	this->setDir(0, 0);
}

void		Champ::printLives(Playground & pl)const {
	start_color();
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	init_pair(6,COLOR_RED,COLOR_BLACK);
	init_pair(7,COLOR_YELLOW,COLOR_BLACK);
	init_pair(18,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(18));

	mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 1, pl.getX() - 40 , "                _________ ");
	mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 2, pl.getX() - 40 , "               | LIFE :  |");
	mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 3 , pl.getX() - 40 , "               |_________|");
	attroff(COLOR_PAIR(18));
	if (mHP == 3) {
		attron(COLOR_PAIR(5));

		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 1 , pl.getX() - 10 , "   _____ ");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 2 , pl.getX() - 10 , "  |  3  |");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 3 , pl.getX() - 10 , "  |_____|");
		attroff(COLOR_PAIR(5));
	} else if (mHP == 2) {
		attron(COLOR_PAIR(7));
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 1 , pl.getX() - 10 , "   _____ ");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 2 , pl.getX() - 10 , "  |  2  |");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 3 , pl.getX() - 10 , "  |_____|");
		attroff(COLOR_PAIR(7));
	} else {	attron(COLOR_PAIR(6));
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 1 , pl.getX() - 10 , "   _____ ");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 2 , pl.getX() - 10 , "  |  1  |");
		mvwprintw(pl.getWindow(), pl.getY() - pl.getY() + 3 , pl.getX() - 10 , "  |_____|");
		attroff(COLOR_PAIR(6));
		//refresh();
	}
}

void Champ::checkEnemies(Enemy* horde, int N, Playground& pl) {
	int center;
	int centerv;
	for (int i = 0; i < N; i++) {
		if (horde[i].getY() == mPosY) {
			center = horde[i].getX() - (horde[i].getsizeX() / 2);
			centerv = mPosX - (mSizeX / 2);
			centerv -= center;
			if (abs(centerv) <= mSizeX) {
				mHP -= 1;
				pl.setClr(2);
				pl.printBorder();
				horde[i].die(pl);
				pl.setClr(0);
			}
		}
	}
}

Champ& Champ::operator=(Champ const & rhs) {
	Object::operator=(rhs);
	return (*this);
}
