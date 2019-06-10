
#include "Object.hpp"

Object::Object(void):mPosX(0), mPosY(0), mDirX(0), mDirY(0), mSpeed(0),
mSizeX(0), mForm(""), mHP(1) { return; }

Object::Object(int posX, int posY, int dirX, int dirY, int speed, int hp, std::string form): mPosX(posX), mPosY(posY), mDirX(dirX), mDirY(dirY), mSpeed(speed),
mForm(form), mHP(hp) {
	mSizeX = mForm.size();
	return;
}

Object::Object(Object const & src) {
	*this = src;
	return;
}

Object::~Object(void) { return; }

void			Object::setHP(int i) { mHP = i; }

int 			Object::getX(void)const { return (mPosX); }

int 			Object::getY(void) const { return (mPosY); }

int 			Object::getDirX(void)const { return (mDirX); }

int 			Object::getdirY(void)const { return (mDirY); }

int 			Object::getSpeed(void)const { return (mSpeed); }

int				Object::getsizeX(void)const { return (mSizeX); }

int				Object::getHP(void)const { return (mHP); }

std::string&	Object::getForm(void)const { return ((std::string&)mForm); }

void					Object::setPosition(int x, int y) {
	mPosX = x;
	mPosY = y;
	return;
}

void					Object::setDir(int x, int y) {
	mDirX = x;
	mDirY = y;
	return;
}

void					Object::setSpeed(int s) {
	mSpeed = s;
	return;
}

void					Object::setForm(std::string form) {
	mForm = form;
	mSizeX = form.size();
	return;
}

void					Object::explode(Playground& pl, int f) {
	start_color();
	init_pair(19, COLOR_GREEN, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_RED);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	init_pair(7, COLOR_YELLOW, COLOR_BLACK);
	refresh();
	if (f == 1) {
	attron(COLOR_PAIR(19));
	mvwprintw(pl.getWindow(), mPosY + 1, mPosX + 10, "+ 10");
	attroff(COLOR_PAIR(19));
	setScore();

	}
	refresh();
	attron(COLOR_PAIR(9));
	mvwprintw(pl.getWindow(), mPosY - 1, mPosX, ".!,");
	mvwprintw(pl.getWindow(), mPosY, mPosX, "-*-");
	mvwprintw(pl.getWindow(), mPosY + 1, mPosX, "'|`");
	attroff(COLOR_PAIR(9));
	refresh();
	attron(COLOR_PAIR(7));
	mvwprintw(pl.getWindow(), mPosY - 1, mPosX - 1, "\\ | /");
	mvwprintw(pl.getWindow(), mPosY, mPosX - 1, "- * -");
	mvwprintw(pl.getWindow(), mPosY + 1, mPosX - 1, "'/ | \\");
	attroff(COLOR_PAIR(7));
	pl.printBorder();
	attron(COLOR_PAIR(6));
	mvwprintw(pl.getWindow(), mPosY - 2, mPosX - 1, ". . .");
	mvwprintw(pl.getWindow(), mPosY - 1, mPosX, "\\|/");
	attron(COLOR_PAIR(7));
	mvwprintw(pl.getWindow(), mPosY, mPosX - 2, "`--+--'");
	attroff(COLOR_PAIR(7));
	attron(COLOR_PAIR(6));
	mvwprintw(pl.getWindow(), mPosY + 1, mPosX, " /|\\ ");
	mvwprintw(pl.getWindow(), mPosY + 2, mPosX - 1, "' | '");
	attroff(COLOR_PAIR(6));
	refresh();
}

void					Object::move(Playground& pl) {
	if (mHP > 0) {
		if (mPosY > pl.getY() || mPosY < 0)
			this->setPosition(rand() % pl.getX(), 0);
		if (mPosX - mSizeX < 0 || mPosX + mSizeX > pl.getX())
			this->setDir(-this->getDirX(), this->getdirY());
		mPosX += mDirX;
		mPosY += mDirY;
	}
}

void				Object::printIt(Playground& pl)const {
	if (mPosX >= 0 && mPosX <= pl.getX() && mPosY > 0 && mPosY < pl.getY() && mHP > 0)
		mvwprintw(pl.getWindow(), mPosY, mPosX, mForm.data());
}

void				Object::collide(Object& obj) {
	mHP -= 1;
	obj.mHP -= 1;
}

void	Object::setScore(void) { mScore += 10; }

void	Object::setZeroScore(void) { mScore = 0; }

int	Object::getScore(void) { return mScore; }

Object& Object::operator=(Object const & rhs) {
	mPosX = rhs.getX();
	mPosY = rhs.getY();
	mDirX = rhs.getDirX();
	mDirY = rhs.getdirY();
	mSpeed = rhs.getSpeed();
	mSizeX = rhs.getsizeX();
	mForm = rhs.getForm();
	mHP = rhs.getHP();
	return (*this);
}

int Object::mScore = 0;
