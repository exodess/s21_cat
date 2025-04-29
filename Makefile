CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all : run

run: s21_cat
	./s21_cat
	
s21_cat : s21_cat.o list.o s21_cat_flags.o
	$(CC) -o s21_cat s21_cat.o list.o s21_cat_flags.o
	rm *.o

s21_cat.o : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c

list.o : ../common/list.c
	$(CC) $(CFLAGS) ../common/list.c

flags.o : s21_cat_flags.c
	$(CC) $(CFLAGS) s21_cat_flags.c

test : 
	./test_cat.sh
clean: 
	rm *.o

test_cat : s21_cat
	
