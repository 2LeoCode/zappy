SHELL=bash
RM=rm -rf

all: client server gfx

client:
	$(MAKE) -C programs/client BUILD_DIR=../../out/build/client OUT_DIR=../../out

server:
	$(MAKE) -C programs/server BUILD_DIR=../../out/build/server OUT_DIR=../../out

gfx:
	$(MAKE) -C programs/gfx BUILD_DIR=../../out/build/gfx OUT_DIR=../../out

clean:
	$(RM) out/build

fclean:
	$(RM) out

re: fclean all

.PHONY: all client server gfx clean fclean re
