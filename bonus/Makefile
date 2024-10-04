##
## EPITECH PROJECT, 2023
## B-SYN-400-MPL-4-1-abstractVM-owen1.bolling
## File description:
## Makefile
##

SRC_DIRS = 		./src

BIN = serverJ2T3

DEBUG = no

ifeq ($(DEBUG),yes)
	CFLAGS += -g3
endif

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")

OBJS = $(SRCS:.cpp=.o)

CPPFLAGS = $(shell find ./include -type d | awk '{printf "-I%s ", $$0}')
CPPFLAGS += -g3 -Iinclude

CRITERION = --coverage -lcriterion

LDLIBS = -lpthread

CC = g++

all : $(BIN)

$(BIN) : $(OBJS)
	@$(CC) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS) $(CRITERION)

%.o :	%.cpp
	@echo "\e[92;1m[\e[36;1m⏳ \e[92;1m] \
\e[1;32mCompiling\e[1;35m $< \e[1;32m...\e[1;0m"
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
	@echo "	\e[32;1m✔ \e[34m\"\e[1;35m$(@)\e[34m\" \
\e[1;32mSuccessfully compiled !"

re : fclean all

fclean : clean
	@ $(RM) -rf $(BIN)
	@ $(RM) -rf unit_tests

clean :
	@ $(RM) -rf $(OBJS)
	@ $(RM) -rf *.gcda
	@ $(RM) -rf *.gcno