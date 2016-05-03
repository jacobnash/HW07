#Matthew Greci, ECE 335, HW_5, Dr. Nava
CC=gcc
OPTS=-Wall -Werror
COPTS=-c

fork:  fork.c
	./create_file.sh
	$(CC) $(OPTS) fork.c csapp.c -lpthread -o $@

clean:
	rm -f fork *.o
