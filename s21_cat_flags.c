#include <stdio.h>
#include <ctype.h>
// #include "../common/colors.h"

void flag_b(unsigned long long * counter, char left, char here)
{
	if(here != '\n' && left == '\n')
		printf("%6llu\t", (*counter)++);

	// баг: если оставить пустую строчку с TAB, то засчитается как непустая
}

void flag_E(char left)
{
	if(left == '\n')
	#ifdef COLORS_H
		printf("%s$%s", BLUE, ESC);
	#else 
		printf("$");
	#endif
}

void flag_n(unsigned long long * counter, char here)
{
	if(here	== '\n') printf("%6llu\t", (*counter)++);
}

int flag_s(char left, char here, int * flag)
{
	int oldflag = *flag;
	*flag = (here == '\n' && here == left);
	
	return (here == '\n' && here == left && oldflag) ? 0 : 1;	
}

int flag_T(char here)
{	
	int res = 1;
	if(here == '\t') {
		#ifdef COLORS_H
			printf("%s^I%s", ORANGE, ESC);
		#else 
			printf("^I");
		#endif
		res = 0;
	}
	return res;
}


int func(unsigned char temp)
{
	int res = 0;
	if(temp < 32 && temp != '\n' && temp != '\t') printf("^%c", 64 + temp);
	else res = 1;

	return res;

}

int flag_v(char here)
{
	unsigned char temp = (unsigned char) here;
	int res = 0;
	
	func(temp);

	if(temp == 127) printf("^?");
	else if(temp > 127) {
		temp = temp - 128;
		printf("M-");
		if(func(temp)) printf("%c", temp);
	}
	else res = 1;
	
	return res;
}
