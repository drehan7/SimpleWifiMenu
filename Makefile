CC=gcc
CFLAGS=-Isrc -lraylib -Wall -pedantic

#DEPS

# %.o: %.c #$(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)

default:
	$(CC) -o out src/main.c $(CFLAGS)

clean:
	rm out
