SHELL=bash
RM=rm -rf
MKDIR=mkdir -p

CXX=clang++
CXXFLAGS=-Wall -Werror -Wextra -pedantic -std=c++20 -Iinc
LDFLAGS=

OUT_DIR=out
BUILD_DIR=$(OUT_DIR)/build
SRC_DIR=src
INC_DIR=inc

SRC=$(shell find src -type f -name "*.cxx")
OBJ=$(SRC:$(SRC_DIR)/%.cxx=$(BUILD_DIR)/%.o)
DEP=$(OBJ:.o=.d)

NAME=$(OUT_DIR)/gfx

all: $(NAME)

-include $(DEP)

$(NAME): $(OBJ)
	$(MKDIR) $(dir $@)
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cxx
	$(MKDIR) $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean:
	$(RM) $(OUT_DIR)

re: fclean all

.PHONY: all clean fclean re
