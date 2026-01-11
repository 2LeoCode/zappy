NAME=raylib

STATIC_TARGET=lib$(NAME).a
SHARED_TARGET=lib$(NAME).so

RM=rm -rf
CP=cp -r

TARGET_TYPE?=static
BUILD_TYPE?=release

ifeq ($(TARGET_TYPE),static)
	TARGET=$(STATIC_TARGET)
else
	ifeq ($(TARGET_TYPE),shared)
		TARGET=$(SHARED_TARGET)
		CXXFLAGS+=-fPIC
	endif
endif

ifeq ($(BUILD_TYPE),release)
	RAYLIB_BUILD_MODE=RELEASE
else
	ifeq ($(BUILD_TYPE),debug)
		RAYLIB_BUILD_MODE=DEBUG
	endif
endif


all: $(NAME)

$(NAME): $(TARGET)

$(TARGET): src/$(TARGET)
	$(CP) $< $@

src/$(STATIC_TARGET):
	$(MAKE) -C src RAYLIB_LIBTYPE=STATIC RAYLIB_BUILD_MODE=$(RAYLIB_BUILD_MODE)

src/$(SHARED_TARGET):
	$(MAKE) -C src RAYLIB_LIBTYPE=SHARED RAYLIB_BUILD_MODE=$(RAYLIB_BUILD_MODE)

clean:
	$(MAKE) clean -C src

fclean: clean
	$(RM) $(STATIC_TARGET) $(SHARED_TARGET)

re: fclean all
