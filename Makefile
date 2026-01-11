SHELL=bash
RM=rm -rf

PROGRAMS_DIR=programs
LIBS_DIR=libs

PROGRAM_NAMES=client gfx server
PROGRAMS=$(foreach name,$(PROGRAM_NAMES), $(PROGRAMS_DIR)/$(name)/$(name))

LIB_NAMES=zappy utils tcp
LIBS=$(foreach name,$(LIB_NAMES), $(LIBS_DIR)/$(name)/lib$(name).so)

BUILD_TYPE?=release

all: $(PROGRAMS)

$(PROGRAM_NAMES): $(PROGRAMS)

$(PROGRAMS):
	$(MAKE) -C $(dir $@) BUILD_TYPE=$(BUILD_TYPE)

$(PROGRAM_NAMES:%=start-%): start-%: %
	./$(PROGRAMS_DIR)/$</$< $(ARGS)

$(PROGRAM_NAMES:%=clean-%): clean-%:
	$(MAKE) -C $(@:clean-%=$(PROGRAMS_DIR)/%) fclean

$(PROGRAM_NAMES:%=fclean-%): fclean-%:
	$(MAKE) -C $(@:clean-%=$(PROGRAMS_DIR)/%) fclean

clean fclean:
	$(foreach bin, $(PROGRAMS) $(LIBS), $(MAKE) -C $(dir $(bin)) $@;)

re: fclean all

.PHONY: all clean fclean re $(foreach prog, $(PROGRAM_NAMES), $(prog) start-$(prog) clean-$(prog) fclean-$(prog))
