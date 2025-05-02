PURPLE    = \033[0;35m
BLUE      = \033[0;34m
GREEN     = \033[0;32m
RED       = \033[0;31m
YELLOW    = \033[0;33m
RESET     = \033[0m

NAME = minishell

SRC = $(shell find src/*.c)
OBJS = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)🔧 Compiling Into Something...$(RESET)"
	@$(CC) $(OBJS) -o $(NAME) -lreadline
	@touch .manda

clean:
	@echo "$(YELLOW)🧹 Cleaning the objects files...$(RESET)"
	@rm -rf .manda
	@rm -rf $(OBJS)

fclean: clean
	@echo "$(RED)💫 finishing the cleaning...$(RESET)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re