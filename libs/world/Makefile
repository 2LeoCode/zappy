SHELL=bash
RM=rm -rf
AR=ar rcs
MKDIR=mkdir -p

NAME=world

CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -Wpedantic -std=c++20 -MMD -fPIC -Iinc
LDFLAGS=

OBJ_DIR=.obj
SRC_DIR=src
INC_DIR=inc

SRC=$(shell find src -type f -name "*.cxx")
OBJ=$(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)
DEP=$(OBJ:.o=.d)

all: $(NAME)

-include $(DEP)

$(NAME): lib$(NAME).so

lib$(NAME).so: $(OBJ)
	$(CXX) -fPIC -shared $^ -o $@

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) lib$(NAME).so

re: fclean all

.PHONY: all clean fclean re $(NAME)
