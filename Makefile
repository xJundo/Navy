##
## EPITECH PROJECT, 2023
## my_printf
## File description:
## The main Makefile of our project
##

COLORS = $$(seq 1 7 | shuf -n 1)
RED = $$(tput setaf $(COLORS))
GREEN = $$(tput setaf $(COLORS))
YELLOW = $$(tput setaf $(COLORS))
RESET = $$(tput sgr0)
MAKEFLAGS += --no-print-directory

CFLAGS = -I./include -Werror -Wpedantic -Wextra
CFLAGS += -g -g3 -lm
#CFLAGS += -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio
LFLAGS = -L./lib -lmy -llist
TEST_FLAGS = --coverage -lcriterion -lgcov

SRC	=	src/main.c
SRC += src/users.c
SRC += src/main_game.c
SRC += src/check_info.c
SRC += src/my_str_to_word_array2.c
SRC += src/check_file.c
SRC += src/my_navy.c
SRC += src/handle_sigs.c
SRC += src/do_binary.c

OBJ	=	$(SRC:.c=.o)

NAME = my_navy

all: libmy liblist test
	@echo "$(RESET)"

libmy:
	@echo "$(RED)------------------"
	@echo "$(RED)doing libmy"
	@make -s -C ./lib/my/
	@echo "$(RED)------------------"

liblist:
	@echo "$(RED)------------------"
	@echo "$(GREEN)doing liblist"
	@make -s -C ./lib/list/
	@echo "$(RED)------------------"


test: $(OBJ)
	@gcc $(SRC) -o $(NAME) -g3 $(CFLAGS) $(LFLAGS)

valgrind: $(OBJ)
	@gcc $(SRC) -g3 $(CFLAGS) $(LFLAGS)
	@valgrind -s ./$(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

clean_lib:
	@make fclean -C./lib/my/
	@make fclean -C./lib/list/
	@make fclean -C./tests/

re:	clean_lib fclean all

unit_tests: re
	make unit_tests -C ./tests/

tests_run: re
	make -C ./tests/
	@gcovr
