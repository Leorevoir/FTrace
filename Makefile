##
## EPITECH PROJECT, 2025
## Ftrace
## File description:
## Makefile
##

GREEN   = \033[1;32m
RED     = \033[1;31m
ILC 	= \033[3m
ORANGE  = \033[38;5;214m
RST     = \033[0m

CC		= gcc
CFLAGS  = -I./include -std=gnu17 \
		  -Wall -Wextra -Werror -pedantic -Wconversion -g3
LDFLAGS = -lelf

SRC_DIR = src
OBJ_DIR = objects

NAME    = ftrace

SRC     = $(wildcard $(SRC_DIR)/*.c)
SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(SRC_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $^ $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(NAME)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

re: fclean all

.PHONY: all $(NAME) clean fclean re
