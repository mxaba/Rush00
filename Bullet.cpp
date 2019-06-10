
#include "Bullet.hpp"

Bullet::Bullet(int n, std::string form) {
	mMax = n;
	mId = 0;
	mBull = new Bullet[n]();
	for (int i = 0; i < n; i++) {
		mBull[i].setForm(form);
		mBull[i].setDir(0, -1);
		mBull[i].setHP(0);
	}
}

Bullet::Bullet(void):Object() {
	mMax = 0;
	mId = 0;
	mBull = NULL;
	mHP = 0;
	return;
}


Bullet::Bullet(Bullet const & src): Object(src) {
	*this = src;
	return;
}

Bullet::~Bullet(void) {
	if (mBull) {
		delete [] mBull;
		mBull = NULL;
	}
	return;
}

Bullet* Bullet::getBull(void)const { return (mBull); }

int 	Bullet::getId(void)const { return (mId); }

int		Bullet::getMax(void)const { return (mMax); }

int		Bullet::checkMDisp(void) {
	int		i = 0;
	while (i < mMax) {
		if (mBull[i].getHP() == 0)
			return i;
		i++;
	}
	return -1;
}

void		Bullet::start(int xPos, int yPos, int inp) {
	int i = checkMDisp();
	if (inp == 10 && i >= 0) {
		mBull[i].setPosition(xPos + 1, yPos - 1);
		mBull[i].setHP(1);
	}
}

void		Bullet::checkDamage(Enemy* horde, int n, Playground& pl) {
	int center;
	int centerV;
	for (int i = 0; i < mMax; i++) {
		for (int e = 0; e < n; e++) {
			if (mBull[i].getHP() > 0 && horde[e].getHP() > 0) {
				if (abs(mBull[i].getY() - horde[e].getY()) <= 3) {
					center = horde[e].getX() + (horde[e].getsizeX() / 3);
					centerV = mBull[i].getX();
					centerV -= center;
					if (abs(centerV) <= 2) {
						mBull[i].explode(pl, 1);
						horde[e].die(pl);
					}
				}
			}
		}
	}
}

void		Bullet::printIt(Playground& pl)const {
	start_color();
	init_pair(7,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(7));

	for (int i = 0; i < mMax; i++)
		mBull[i].Object::printIt(pl);
	attroff(COLOR_PAIR(7));
}

void		Bullet::move(Playground& pl) {
	for (int i = 0; i < mMax; i++) {
		if (mBull[i].getY() < 0) {
			mBull[i].setHP(0);
		}
		mBull[i].Object::move(pl);
	}
}

Bullet& Bullet::operator=(Bullet const & rhs) {
	Object::operator=(rhs);
	return (*this);
}

void		Bullet::printCharge(Playground & pl) {
	int i = 0;
	int min = 0;
	while (i < mMax) {
		if (mBull[i].getHP() == 0)
			min++;
		i++;
	}

	start_color();
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	init_pair(6,COLOR_RED,COLOR_BLACK);
	init_pair(7,COLOR_YELLOW,COLOR_BLACK);
	init_pair(18,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(18));

	mvwprintw(pl.getWindow(), pl.getY() - 18 + i , pl.getX() - 38 , "             _________ ");
	mvwprintw(pl.getWindow(), pl.getY() - 17 + i , pl.getX() - 38 , "            | BOMB [] |");
	mvwprintw(pl.getWindow(), pl.getY() - 16 + i , pl.getX() - 38 , "            |_________|");

	attroff(COLOR_PAIR(18));

	if (min > mMax - (mMax / 3) || min == mMax)
		attron(COLOR_PAIR(5));
	else if (min > mMax - (2 * mMax / 3) || min == mMax / 2)
		attron(COLOR_PAIR(7));
	else
		attron(COLOR_PAIR(6));

	for (i = 1; i < mMax + 1; i++)
		if (i == mMax)
			mvwprintw(pl.getWindow(), pl.getY() - 16 + i , pl.getX() - 14 , "|____________");
		else
			mvwprintw(pl.getWindow(), pl.getY() - 16 + i , pl.getX() - 14 , "| ");
	
	for (i = 1; i < mMax + 1; i++)
		mvwprintw(pl.getWindow(), pl.getY() - 16 + i , pl.getX() - 2 , "| ");

	while (min > 0) {
		mvwprintw(pl.getWindow(), pl.getY() - mMax - 13 -  (min - mMax) , pl.getX() - 12, "@@@@@@@@@");
		min--;
	}
	attroff(COLOR_PAIR(5));
	attroff(COLOR_PAIR(6));
	attroff(COLOR_PAIR(7));
}
