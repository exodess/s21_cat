#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "s21_cat_flags.h"
#include "../common/list.h"
// #include "../common/colors.h" // окрашивание вывода

#define _GNU_SOURCE

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
	
	if(list_file -> name == NULL) 
		push(&list_file, "-");
	
// 	printf("|b|E|n|s|T|v|\n");
// 	for(int i = 0; i < COUNT_GNU_FLAGS; i++) printf("|%d", modes[i]);
// 	puts("|");
// 
// 	printList(list_file);


	while(list_file -> name != NULL) {
		if(strcmp(list_file -> name, "-") == 0) fp = stdin;

		if((fp == stdin) || (fp = fopen(list_file -> name, "r")) != NULL) {
			left = '\n';
			while((here = fgetc(fp)) != EOF) {
				res = 1;
				// очередность вызова функций влияет на работоспособность программы!
				if(modes[strchr(FLAGS, 'b') - FLAGS]) flag_b(&count, left, here);
				// if(modes[strchr(FLAGS, 'n') - FLAGS]) flag_n(&count, left);
		
				if(modes[strchr(FLAGS, 'T') - FLAGS]) res = flag_T(here);
				if(modes[strchr(FLAGS, 'v') - FLAGS]) res = res && flag_v(here);
				if(modes[strchr(FLAGS, 's') - FLAGS]) res = res && flag_s(left, here, &flag);
				if(modes[strchr(FLAGS, 'n') - FLAGS] && res) flag_n(&count, left);
				if(modes[strchr(FLAGS, 'E') - FLAGS] && res) flag_E(here);
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
	int rez = 0, j = 0;
	int * list_index = malloc(argc * sizeof(int));

	for(int i = 0; i < argc; i++) list_index[i] = -1;

	for(int i = 0; i < COUNT_GNU_FLAGS; i++) {
		long_options[i].name = GNU_FLAGS[i];
		long_options[i].has_arg = no_argument;
		long_options[i].flag = &modes[i];
		long_options[i].val = 0;
	}
	long_options[COUNT_GNU_FLAGS].name = NULL;
	long_options[COUNT_GNU_FLAGS].has_arg = 0;
	long_options[COUNT_GNU_FLAGS].flag = NULL;
	long_options[COUNT_GNU_FLAGS].val = 0;

	while((rez = getopt_long(argc, argv, FLAGS, long_options, &list_index[j])) != -1) {
		if(rez) { // короткое название
			for(int i = 0; i < COUNT_GNU_FLAGS; i++)
				modes[i] += (modes[i]) ? 0 : (rez == FLAGS[i]);	
			if(rez == 'e') 
				modes[strchr(FLAGS, 'E') - FLAGS] = modes[strchr(FLAGS, 'v') - FLAGS] = 1;
			if(rez == 't')
				modes[strchr(FLAGS, 'T') - FLAGS] = modes[strchr(FLAGS, 'v') - FLAGS] = 1;

		}
		j++;
	}	

	for(int i = (argc - 1); i > 0; i--) 
		if((argv[i][0] == '-' && strlen(argv[i]) == 1) || argv[i][0] != '-') 
			push(root, argv[i]);
	
}


void processing_modes(int modes[COUNT_GNU_FLAGS])
{
	// -bn -> -b
	if(modes[strchr(FLAGS, 'b') - FLAGS]) modes[strchr(FLAGS, 'n') - FLAGS] = 0;

	
}
