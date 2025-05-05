##
## EPITECH PROJECT, 2025
## PSU-ftrace
## File description:
## Makefile
##

GREEN      	= \033[1;32m
RED        	= \033[1;31m
ILC			= \033[3m
ORANGE     	= \033[38;5;214m
RST		   	= \033[0m

###############################################################################

CC         	= gcc

CFLAGS   	= -I./include -std=gnu17 -O3
		  # -g3 \
          # -Wall -Wextra -Werror -pedantic -Wconversion \
		  # -O3

###############################################################################

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

NAME  	= ftrace

all: $(NAME)

ftrace: $(SRC_OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRC_OBJ)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(NAME)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

###############################################################################

COV_FLAGS  = -fprofile-arcs -ftest-coverage

TESTS_DIR   = tests
UNIT_BIN    = unit_tests

SRC_NOMAIN  = $(filter-out $(SRC_DIR)/main.c, $(SRC))
SRC_OBJ_NOMAIN = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_NOMAIN))

TESTS_SRC   = $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJ   = $(patsubst $(TESTS_DIR)/%.c, $(OBJ_DIR)/tests/%.o, $(TESTS_SRC))

CFLAGS += $(COV_FLAGS)
LDFLAGS += -lgcov

tests_run: $(SRC_OBJ_NOMAIN) $(TESTS_OBJ)
	@$(CC) $(TESTS_DIR)/binary/elf_bin.c -o $(TESTS_DIR)/elf_bin64
	@$(CC) -m32 $(TESTS_DIR)/binary/elf_bin.c -o $(TESTS_DIR)/elf_bin32
	@$(CC) $(CFLAGS) $(LDFLAGS) -lcriterion -o $(UNIT_BIN) $^
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(UNIT_BIN)$(RST)\n"
	@./$(UNIT_BIN)
	@echo ""
	@gcovr -r . --exclude tests/ > coverage.txt
	@cat coverage.txt
	@printf "$(GREEN)[🧪] TESTING:   $(RST) $(ILC)$(UNIT_BIN)$(RST)\n"

$(OBJ_DIR)/tests/%.o: $(TESTS_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🧪] TESTING:  $(RST) $(ILC)$<$(RST)\n"

###############################################################################

clean:
	@rm -rf lib/$(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f *.gcda *.gcno */*.gcda */*.gcno
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

###############################################################################

fclean: clean
	@rm -f $(NAME) vgcore* $(UNIT_BIN) $(TESTS_DIR)/elf_bin*
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

###############################################################################

re: fclean all

###############################################################################

.PHONY: all ftrace clean fclean re
