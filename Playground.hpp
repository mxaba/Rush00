
#ifndef PLAYGROUND_HPP
# define PLAYGROUND_HPP

# include <cstdlib>
# include <ncurses.h>

class Playground {
public:
	Playground(void);
	Playground(Playground const & src);
	~Playground(void);
	void	takeWindSize(void);
	int		getX(void)const;
	int		getY(void)const;
	WINDOW*	getWindow(void)const;
	void	printBorder();
	void	setClr(int i);
	Playground& operator=(Playground const & rhs);

protected:
	int		mSizex;
	int		mSizey;
	WINDOW* mWind;
	int		clr;
};

#endif

