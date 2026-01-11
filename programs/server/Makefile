SHELL=bash

NAME=server

STATIC_LIB_NAMES=
SHARED_LIB_NAMES=zappy tcp

SRC_ROOT=src
INC_ROOT=inc
OBJ_ROOT=.obj
LIB_ROOT=../../libs

STATIC_LIB_DIRS=$(STATIC_LIB_NAMES:%=$(LIB_ROOT)/%)
SHARED_LIB_DIRS=$(SHARED_LIB_NAMES:%=$(LIB_ROOT)/%)

STATIC_LIB=$(foreach lib,$(STATIC_LIB_NAMES), $(LIB_ROOT)/$(lib)/lib$(lib).a)
SHARED_LIB=$(foreach lib,$(SHARED_LIB_NAMES), $(LIB_ROOT)/$(lib)/lib$(lib).so)
LIB=$(STATIC_LIB) $(SHARED_LIB)

LIB=$(foreach name,$(LIB_NAMES), $(LIB_ROOT)/$(name)/lib$(name).so)
SRC=$(shell find $(SRC_ROOT) -type f -name "*.cxx")
OBJ=$(SRC:$(SRC_ROOT)/%.cxx=$(OBJ_ROOT)/%.o)
DEP=$(OBJ:.o=.d)

LIB_DIRS=$(STATIC_LIB_DIRS) $(SHARED_LIB_DIRS)
OBJ_DIRS=$(sort $(dir $(OBJ)))

RM=rm -rf
MKDIR=mkdir -p

CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -Wpedantic -std=c++20 -MMD -I$(INC_ROOT) -I$(SRC_ROOT) $(LIB_DIRS:%=-I%/$(INC_ROOT))
LDFLAGS=$(LIB_DIRS:%=-L%) $(STATIC_LIB_NAMES:%=-l:lib%.a) $(SHARED_LIB_NAMES:%=-l:lib%.so) -Wl,-rpath,'$(shell printf '$(SHARED_LIB_DIRS:%=$$ORIGIN/%:)' | tr -d ' ')'

BUILD_TYPE?=release

ifeq ($(BUILD_TYPE),release)
	CXXFLAGS+=-O2 -DNDEBUG
else
	ifeq ($(BUILD_TYPE),debug)
		CXXFLAGS+=-ggdb -g3
	endif
endif


all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ) $(LIB)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ): $(OBJ_ROOT)/%.o: $(SRC_ROOT)/%.cxx | $(OBJ_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIRS):
	$(MKDIR) $@

$(STATIC_LIB):
	$(MAKE) -C $(dir $@) BUILD_TYPE=$(BUILD_TYPE) TARGET_TYPE=static

$(SHARED_LIB):
	$(MAKE) -C $(dir $@) BUILD_TYPE=$(BUILD_TYPE) TARGET_TYPE=shared

clean:
	$(RM) $(OBJ_ROOT)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
