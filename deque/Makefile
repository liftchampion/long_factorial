NAME = factorial
SRC = $(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
CC = g++
CFLAGS = --std=c++1z -Wall -Wextra
HDR = big_int.h factorial.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HDR)
	$(CC) $(CFLAGS) -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -f $(OBJ)

re: fclean all