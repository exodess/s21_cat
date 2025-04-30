CC = gcc
CFLAGS = -Wall -Wextra -Werror -c

all : build
	
build : s21_cat.o list.o s21_cat_flags.o
	$(CC) -o ~/s21_cat s21_cat.o list.o s21_cat_flags.o
	rm *.o 
	./tools/build.sh s21_cat
	
s21_cat.o : s21_cat.c
	$(CC) $(CFLAGS) s21_cat.c

list.o : tools/list.c
	$(CC) $(CFLAGS) tools/list.c

flags.o : s21_cat_flags.c
	$(CC) $(CFLAGS) s21_cat_flags.c

test : 
	./tools/test_cat.sh 

clean: 
	rm *.o
