OBJECTS = *.o
SRC = libft/*.c\
		src/error.c\
		src/main.c\
		src/list.c\
		src/algorithm.c\
		src/tetriminos.c

FLAGS = -Wall -Wextra -Werror 
NAME = fillit
LIB = libft/libft.a

all: $(NAME)

$(NAME):
	make -C libft/
	gcc $(FLAGS) $(SRC) -o $(NAME) $(LIB)

sanitize:
	gcc $(FLAGS) $(SRC) -o $(NAME) -g

lldb:
	gcc -g $(SRC) $(LIB)

cleanlldb:
	rm $(NAME)
	rm -r $(NAME).dSYM

runlldb:
	lldb ./a.out

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(LIB)
	rm -f $(NAME)

re: fclean all
