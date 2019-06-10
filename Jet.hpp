
#ifndef JET_HPP
# define JET_HPP

# include "Object.hpp"
# include "Champ.hpp"
# include "Enemy.hpp"
# include "Playground.hpp"

class Jet:public Object {
public:
	Jet(int n, std::string form);
	Jet(Jet const & src);
	~Jet(void);
	Jet* getJet(void)const;
	int	getIndex(void)const;
	int	getMax(void)const;
	void printIt(Playground& pl)const;
	void move(Playground& pl);
	void start(int xPos, int yPos, int inp);
	void checkDamage(Enemy*, int n, Playground& pl);
	void printCharge(Playground & pl);
	Jet& operator=(Jet const & rhs);
	int			checkMDisp(void);

private:
	Jet(void);
	Jet* mJets;
	int		 mMax;
	int		 mId;
};

#endif

