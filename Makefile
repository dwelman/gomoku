NAME = gomoku

SRC_FILES = *.cpp

SRC = $(addprefix src/, $(SRC_FILES))

OBJ = $(SRC:.cpp=.o)

CFLAG = -std=c++11 -Wall -Werror -Wextra -lncurses

INCLUDES = -I includes/

all: $(NAME)

$(NAME):
	@g++ -std=c++11 $(INCLUDES) -c $(SRC)
	@echo "OBJECTS CREATED"
	@/bin/mv -f *.o src
	@g++ $(CFLAG) $(INCLUDES) -o $(NAME) $(OBJ)
	@echo "PROJECT CREATED"

clean:
	@/bin/rm -f $(OBJ)
	@echo "OBJECTS CLEANED"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "ALL FILES CLEANED"

re: fclean all