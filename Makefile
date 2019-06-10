
NAME = ft_retro
SRC = main.cpp Playground.cpp Object.cpp Enemy.cpp Jet.cpp Bullet.cpp Champ.cpp
FLG = -Wall -Wextra -Werror 
OBJ = $(SRC:.cpp=.o)
CC = clang++
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLG) -o $(NAME) $(OBJ) -lncurses

%.o: %.cpp
	$(CC) -c -o $@ $<

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all fclean clean all
