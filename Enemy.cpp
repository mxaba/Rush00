
#include "Enemy.hpp"

Enemy::Enemy(void):Object() {
	mHorde = NULL;
	mNum = 0;
	mHP = 1;
	return;
}

Enemy::Enemy(int n) {
	mHorde = new Enemy[n]();
	mNum = n;
	mHP = 1;
	return;
}

Enemy::Enemy(int n, std::string form) {
	mHorde = new Enemy[n]();
	mNum = n;
	for (int i = 0; i < n; i++)
		mHorde[i].setForm(form);
	return;
}

Enemy::Enemy(Enemy const & src):Object(src) {
	*this = src;
	return;
}

Enemy::~Enemy(void) {
	if (mHorde) {
		delete [] mHorde;
		mHorde = NULL;
	}
	return;
}

Enemy* Enemy::getHorde(void)const { return (mHorde); }

int			 Enemy::getNum(void)const { return (mNum); }

void		 Enemy::randomBoom(Playground& pl) {
	for (int a = 0; a < mNum; a++) {
		int		i = 0;
		i = rand() % 8;

		if (i == 4)
			i = 0;
		else if (i < 4 && i >= 2)
			i = -1;
		else if (i < 2)
			i = -2;
		else if (i >= 7)
			i = 1;
		else
			i = 2;

		mHorde[a].setPosition(rand() % (pl.getX() - mSizeX), rand() % (pl.getY() / 4));
		mHorde[a].setDir(i, 1);
		mHorde[a].setHP(1);
		mHorde[a].setSpeed(0);
	}
}

void		 Enemy::respawn(void) {
	for (int i = 0; i < mNum; i++)
		mHP = 1;
}

void		Enemy::die(Playground& pl) {
	int		i = 0;
	i = rand() % 8;

	if (i == 4)
		i = 0;
	else if (i < 4 && i >= 2)
		i = -1;
	else if (i < 2)
		i = -2;
	else if (i >= 7)
		i = 1;
	else
		i = 2;

	this->Object::explode(pl, 0);
	refresh();
	usleep(10);
	this->setPosition(rand() % (pl.getX() - mSizeX), 0);
	this->setDir(i, 1);
	this->setSpeed(0);
	this->setHP(1);
}

void		Enemy::printIt(Playground& pl)const {
	start_color();
	init_pair(8,COLOR_CYAN, COLOR_BLACK);
	attron(COLOR_PAIR(8));
	for (int i = 0; i < mNum; i++)
		mHorde[i].Object::printIt(pl);
	attroff(COLOR_PAIR(8));
}

void		Enemy::move(Playground& pl) {
	int		i = 0;
	i = rand() % 8;

	if (i == 4)
		i = 0;
	else if (i < 4)
		i = -1;
	else
		i = 1;

	this->setDir(i, 1);

	for (int i = 0; i < mNum; i++)
		mHorde[i].Object::move(pl);
}

Enemy* Enemy::getHorde(void) { return (mHorde); }

int			Enemy::getNum(void) { return (mNum); }

Enemy& Enemy::operator=(Enemy const & rhs) {
	mHorde = rhs.getHorde();
	mNum = rhs.getNum();
	return (*this);
}
