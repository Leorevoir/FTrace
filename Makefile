##
## EPITECH PROJECT, 2025
## PSU-ftrace
## File description:
## Makefile
##

CC         	= gcc

CFLAGS   	= -I./include -std=gnu17 -g3 \
          -Wall -Wextra -Werror -pedantic -Wconversion
		  # -O3

LDFLAGS   	= -lelf

SRC_DIR  	= src
OBJ_DIR		= objects

SRC     = $(wildcard $(SRC_DIR)/*.c) \
		  $(wildcard $(SRC_DIR)/parse/*.c) \
		  $(wildcard $(SRC_DIR)/utils/*.c) \
		  $(wildcard $(SRC_DIR)/ftrace/*.c) \
		  $(wildcard $(SRC_DIR)/ftrace/nm/*.c) \
		  $(wildcard $(SRC_DIR)/ftrace/strace/*.c) \
		  $(wildcard $(SRC_DIR)/ftrace/strace/display/*.c)

SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

PROGRAMS  	= ftrace

GREEN      	= \033[1;32m
RED        	= \033[1;31m
ILC			= \033[3m
ORANGE     	= \033[38;5;214m
RST		   	= \033[0m

all: $(PROGRAMS)

ftrace: $(SRC_OBJ)
	@$(CC) $(CFLAGS) -o $(PROGRAMS) $(SRC_OBJ) $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(PROGRAMS)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

clean:
	@rm -rf lib/$(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

fclean: clean
	@rm -f $(PROGRAMS) vgcore*
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

re: fclean all

.PHONY: all ftrace clean fclean re
