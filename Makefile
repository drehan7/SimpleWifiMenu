CC=gcc
CFLAGS=-Wall -pedantic -Wextra -fcommon
LDFLAGS=-Isrc -lraylib
SRC=src
SOURCES=$(wildcard $(SRC)/*.c)
HEADERS=$(wildcard $(SRC)/*.h)
OBJ=Objs
OBJECTS=$(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SOURCES))
TARGET=out

build: $(TARGET)

clean:
	rm -r $(OBJ)/*
	@#

.PHONY: build clean

##

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(CFLAGS) $^ -o $@
	@echo "Build Successful!"

$(OBJECTS): $(SOURCES) $(HEADERS)
	@echo Compiling $^
	# FILE=$(patsubst $(OBJ)/%.o,$(SRC)/%.c,$@)
	# @mkdir -p $(@D)
	# $(CC) $(CFLAGS) $< -o $@
	$(CC) $(CFLAGS) -c $(patsubst $(OBJ)/%.o,$(SRC)/%.c,$@) -o $@
