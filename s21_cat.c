#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "s21_cat_flags.h"
#include "tools/list.h"

#define _GNU_SOURCE 
#define MODEFL(ch) modes[strchr(FLAGS, *#ch) - FLAGS] // просмотр значения конкретного флага в массиве modes

void processing_modes(int modes[COUNT_GNU_FLAGS]);
void processing_input(int argc, char * argv[], 
					struct option [COUNT_GNU_FLAGS], int [COUNT_GNU_FLAGS], 
					LIST **);

int main(int argc, char *argv[])
{

	LIST * list_file;
	FILE * fp = NULL;
	struct option long_options[COUNT_GNU_FLAGS + 1];
	char left, here;
	unsigned long long count = 1;
	int res = 0, flag = 0;
	int modes[COUNT_GNU_FLAGS] = {0};
	//				|<-	   COUNT_MODES    ->|
	// 				|		  ------		|
	// int modes =  | b | E | n | s | T | v |

	init(&list_file);
	
	processing_input(argc, argv, long_options, modes, &list_file);
	processing_modes(modes);

	while(list_file -> name != NULL) {
		if(strcmp(list_file -> name, "-") == 0) fp = stdin;

		if((fp == stdin) || (fp = fopen(list_file -> name, "r")) != NULL) {
			left = '\n';
			while((here = fgetc(fp)) != EOF) {
				res = 1;
				// очередность вызова функций влияет на работоспособность программы!
				if(MODEFL(b)) flag_b(&count, left, here);
				if(MODEFL(T)) res = flag_T(here);
				if(MODEFL(v)) res = res && flag_v(here);
				if(MODEFL(s)) res = res && flag_s(left, here, &flag);
				if(MODEFL(n) && res) flag_n(&count, left);
				if(MODEFL(E) && res) flag_E(here);

				if(res) printf("%c", here);
				left = here;
			}

			if(fp != stdin) fclose(fp);
		}
		else
		#ifdef COLORS_H
			fprintf(stderr, "%s[Не удалось открыть файл %s]%s\n", ORANGE, list_file -> name, ESC);
		#else 
			fprintf(stderr, "[Не удалось открыть файл %s]\n", list_file -> name);
		#endif
		free(pop(&list_file));
	}
	
	destroy(&list_file);
}

void processing_input(int argc, char * argv[],
					struct option long_options[COUNT_GNU_FLAGS], int modes[COUNT_GNU_FLAGS],
					LIST ** root)
{	
	int rez = 0;
	int opt_index;

	for(int i = 0; i < COUNT_GNU_FLAGS; i++) {
		long_options[i].name = GNU_FLAGS[i];
		long_options[i].has_arg = no_argument;
		long_options[i].flag = &modes[i];
		long_options[i].val = 1;
	}
	long_options[COUNT_GNU_FLAGS].name = NULL;
	long_options[COUNT_GNU_FLAGS].has_arg = 0;
	long_options[COUNT_GNU_FLAGS].flag = NULL;
	long_options[COUNT_GNU_FLAGS].val = 0;

	while((rez = getopt_long(argc, argv, FLAGS, long_options, &opt_index)) != -1) {
		if(rez) { // короткое название
			for(int i = 0; i < COUNT_GNU_FLAGS; i++)
				modes[i] += (modes[i]) ? 0 : (rez == FLAGS[i]);	

			if(rez == 'e') MODEFL(E) = MODEFL(v) = 1;
			if(rez == 't') MODEFL(T) = MODEFL(v) = 1;
		}
	}	

	for(int i = (argc - 1); i > 0; i--) 
		if((argv[i][0] == '-' && strlen(argv[i]) == 1) || argv[i][0] != '-') 
			push(root, argv[i]);

	if((*root) -> name == NULL) 
		push(root, "-");
}


void processing_modes(int modes[COUNT_GNU_FLAGS])
{
	// -bn -> -b
	if(MODEFL(b)) 
		MODEFL(n) = 0;
}
