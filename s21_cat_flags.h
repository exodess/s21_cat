#ifndef CAT_FLAGS_H
#define CAT_FLAGS_H

#define COUNT_FLAGS 8
#define COUNT_GNU_FLAGS 6	

#define GNU_FLAG_B "number-nonblank"
#define GNU_FLAG_E "show-ends"
#define GNU_FLAG_N "number"
#define GNU_FLAG_S "squeeze-blank"
#define GNU_FLAG_T "show-tabs"
#define GNU_FLAG_V "show-nonprinting"


#define FLAGS "bEnsTvet"
	// -t = -vT
	// -e = -vE

char * GNU_FLAGS[COUNT_GNU_FLAGS] = {	GNU_FLAG_B, 
				   						GNU_FLAG_E, 
										GNU_FLAG_N, 
										GNU_FLAG_S,
										GNU_FLAG_T,
										GNU_FLAG_V	};
void flag_b(unsigned long long * , char, char);
void flag_E(char);
void flag_n(unsigned long long *, char);
int flag_s(char, char, int *);
int flag_T(char);
int flag_v(char);
int func(unsigned char);

#endif
