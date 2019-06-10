
#include "Jet.hpp"

Jet::Jet(int n, std::string form) {
	mMax = n;
	mId = 0;
	mJets = new Jet[n]();
	for (int i = 0; i < n; i++) {
		mJets[i].setForm(form);
		mJets[i].setDir(0, -1);
		mJets[i].setHP(0);
	}
}

Jet::Jet(void):Object() {
	mMax = 0;
	mId = 0;
	mJets = NULL;
	mHP = 0;
	return;
}


Jet::Jet(Jet const & src):Object(src) {
	*this = src;
	return;
}

Jet::~Jet(void) {
	if (mJets) {
		delete [] mJets;
		mJets = NULL;
	}
	return;
}

Jet* Jet::getJet(void)const { return (mJets); }

int	Jet::getIndex(void)const { return (mId); }

int	Jet::getMax(void)const { return (mMax); }

int	Jet::checkMDisp(void) {
	int		i = 0;
	while (i < mMax) {
		if (mJets[i].getHP() == 0)
			return i;
		i++;
	}
	return -1;
}

void Jet::start(int xPos, int yPos, int inp) {
	int		i = checkMDisp();
	if (inp == 32 && i >= 0) {
		mJets[i].setPosition(xPos + 1, yPos - 1);
		mJets[i].setHP(1);
	}
}

void Jet::checkDamage(Enemy* horde, int n, Playground& pl) {
	int center;
	int centerV;
	for (int i = 0; i < mMax; i++) {
		for (int e = 0; e < n; e++) {
			if (mJets[i].getHP() > 0 && horde[e].getHP() > 0) {
				if (abs(mJets[i].getY() - horde[e].getY()) <= 3) {
					center = horde[e].getX() + (horde[e].getsizeX() / 3);
					centerV = mJets[i].getX();
					centerV -= center;
					if (abs(centerV) <= 2) {
						mJets[i].collide(horde[e]);
						mJets[i].explode(pl, 1);
						horde[e].die(pl);
						mJets[i].setHP(0);
					}
				}
			}
		}
	}
}

void Jet::printIt(Playground& pl)const {
	start_color();
	init_pair(7,COLOR_YELLOW,COLOR_BLACK);
	attron(COLOR_PAIR(7));
	for (int i = 0; i < mMax; i++)
		mJets[i].Object::printIt(pl);
	attroff(COLOR_PAIR(7));
}

void Jet::move(Playground& pl) {
	for (int i = 0; i < mMax; i++) {
		if (mJets[i].getY() < 0) {
			mJets[i].setHP(0);
		}
		mJets[i].Object::move(pl);
	}
}

Jet& Jet::operator=(Jet const & rhs) {
	Object::operator=(rhs);
	return (*this);
}

void Jet::printCharge(Playground & pl) {
	int i = 0;
	int min = 0;

	while (i < mMax) {
		if (mJets[i].getHP() == 0)
			min++;
		i++;
	}
	start_color();
	init_pair(5,COLOR_GREEN,COLOR_BLACK);
	init_pair(6,COLOR_RED,COLOR_BLACK);
	init_pair(7,COLOR_YELLOW,COLOR_BLACK);
	init_pair(18,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(18));

	mvwprintw(pl.getWindow(), pl.getY() - 22 + i , pl.getX() - 38 , "             _________ ");
	mvwprintw(pl.getWindow(), pl.getY() - 21 + i , pl.getX() - 38 , "            | AMMO  * |");
	mvwprintw(pl.getWindow(), pl.getY() - 20 + i , pl.getX() - 38 , "            |_________|");

	attroff(COLOR_PAIR(18));

	if (min > mMax - (mMax / 3))
		attron(COLOR_PAIR(5));
	else if (min > mMax - (2 * mMax / 3))
		attron(COLOR_PAIR(7));
	else
		attron(COLOR_PAIR(6));

	for (i = 1; i < mMax + 1; i++)
		if ( i == mMax)
			mvwprintw(pl.getWindow(), pl.getY() - 12 + i , pl.getX() - 14 , "|____________");
		else
			mvwprintw(pl.getWindow(), pl.getY() - 12 + i , pl.getX() - 14 , "| ");
	
	for (i = 1; i < mMax + 1; i++)
		mvwprintw(pl.getWindow(), pl.getY() - 12 + i , pl.getX() - 2 , "| ");

	while ( min > 0) {
		mvwprintw(pl.getWindow(), pl.getY() - mMax - 1 -  (min - mMax) , pl.getX() - 12, "@@@@@@@@@");
		min--;
	}
	attroff(COLOR_PAIR(5));
	attroff(COLOR_PAIR(6));
	attroff(COLOR_PAIR(7));
}
