CC = gcc

CFLAGS = -ggdb3 -gdwarf-4 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow

SRC = ../src

OBJS = $(SRC)/stdprompt.o

.PHONY: clean

%: %.c $(OBJS)
	$(CC) $(CFLAGS) $< $(OBJS) -o $@ -lm

$(SRC)/stdprompt.o: $(SRC)/stdprompt.c $(SRC)/stdprompt.h
	$(CC) $(CFLAGS) -c $(SRC)/stdprompt.c -o $@

clean:
	rm -f $(OBJS)
