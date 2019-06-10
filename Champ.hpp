
#ifndef CHAMP_HPP
# define CHAMP_HPP

# include "Enemy.hpp"
# include "Champ.hpp"

class Champ:public Object {
public:
	Champ(Playground& pl);
	Champ(Champ const & src);
	~Champ(void);
	void inputDirection(int);
	void checkEnemies(Enemy*, int, Playground& pl);
	void move(Playground& pl);
	void printIt(Playground& pl)const;
	void printLives(Playground & pl)const;
	Champ& operator=(Champ const & rhs);
	int input;

private:
	Champ(void);
	std::string _name;
};

#endif

