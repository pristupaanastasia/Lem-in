NAME = lem-in

MAKE = make
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror
SRC = *.c

HEADER = lem_in.h


all: $(NAME)

$(NAME): $(LIB)
		gcc -O3 -I $(HEADER) $(LIB)  -o  $(NAME) $(SRC) -g

$(LIB):
		$(MAKE) -C ./libft/

clean:
		$(MAKE) clean -C ./libft
		rm -f $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		rm -f $(NAME)

re: fclean all
