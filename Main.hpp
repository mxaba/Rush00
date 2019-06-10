
#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>
# include <string>
# include <stdlib.h>
# include "Playground.hpp"
# include "Object.hpp"
# include "Enemy.hpp"
# include "Champ.hpp"
# include "Jet.hpp"
# include "Bullet.hpp"

# define KEY_ESC 27

int     difficultyMode(int i);
void    game(int i, Playground& pl);
void    printLogo(Playground pl);
void    printMenu(Playground & pl);
void    menu(void);

#endif
