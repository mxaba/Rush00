
#ifndef OBJECT_HPP
# define OBJECT_HPP

# include <unistd.h>
# include "Playground.hpp"
# include <string>

class Object {
public:
	Object(void);
	Object(int posX, int posY, int dirX, int dirY, int speed, int hp, std::string form);
	Object(Object const & src);
	virtual					~Object(void);
	int 					getX(void)const;
	int 					getY(void)const;
	int 					getDirX(void)const;
	int 					getdirY(void)const;
	int 					getSpeed(void)const;
	int						getsizeX(void)const;
	int						getsizeY(void)const;
	std::string&			getForm(void)const;
	int						getHP(void)const;
	void					setHP(int i);
	void					setPosition(int x, int y);
	void					setDir(int x, int y);
	void					setSpeed(int s);
	void					setForm(std::string form);
	void					move(Playground& pl);
	virtual void			printIt(Playground& pl)const;
	virtual void			collide(Object& obj);
	void					explode(Playground& pl, int f);
	void					setScore(void);
	void					setZeroScore(void);
	int						getScore(void);
	Object& operator=(Object const & rhs);

protected:
	int			mPosX;
	int			mPosY;
	int			mDirX;
	int			mDirY;
	int			mSpeed;
	int			mSizeX;
	std::string	mForm;
	int			mHP;
	int static	mScore;
};

#endif

