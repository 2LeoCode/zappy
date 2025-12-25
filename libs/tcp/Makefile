SHELL=bash
RM=rm -rf
AR=ar rcs
MKDIR=mkdir -p

NAME=tcp
LIB_NAMES=utils

LIBS_ROOT=../../libs
SRC_DIR=src
INC_DIR=inc
OBJ_DIR=.obj
LIB_DIRS=$(LIB_NAMES:%=$(LIBS_ROOT)/%)

LIB=$(foreach name,$(LIB_NAMES), $(LIBS_ROOT)/$(name)/lib$(name).so)
SRC=$(shell find src -type f -name "*.cxx")
OBJ=$(SRC:$(SRC_DIR)/%.cxx=$(OBJ_DIR)/%.o)
DEP=$(OBJ:.o=.d)

OBJ_DIRS=$(sort $(dir $(OBJ)))

CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -Wpedantic -std=c++20 -MMD -fPIC -I$(INC_DIR) $(LIB_DIRS:%=-I%/$(INC_DIR))
LDFLAGS=$(LIB_DIRS:%=-L%) $(LIB_NAMES:%=-l%) -Wl,-rpath,'$(shell printf '$(lib_dirs:%=$$origin/%:)' | tr -d ' ')'


all: $(NAME)

-include $(DEP)

$(LIB):
	$(MAKE) -C $(dir $@) INC_DIR=$(INC_DIR)

$(NAME): lib$(NAME).so

lib$(NAME).so: $(OBJ) $(LIB)
	$(CXX) -fPIC -shared $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cxx | $(OBJ_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIRS):
	$(MKDIR) $@

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) lib$(NAME).so

re: fclean all

.PHONY: all clean fclean re $(NAME)
