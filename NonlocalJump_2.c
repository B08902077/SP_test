// calculate Fibonacci sequences by nonlocal jump
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <setjmp.h>
#include <unistd.h>
#define digit_Limit 2400000

jmp_buf jmpbuf;

typedef struct bigNum{
	char digit[digit_Limit];
}bigNum;

void init_Num(bigNum *F){
	for(int i = 0; i < 2; i++){
		memset(F[i].digit, 0, sizeof(bigNum));
	}
}

void print(int times, bigNum *N){
#ifdef DEBUG
	printf("F[%d] = %s\n", times, N->digit);
	return;
#endif
	printf("F[%d] = ", times);
	for(int i = strlen(N->digit)-1; i >= 0; i--)	putchar(N->digit[i]);
	putchar('\n');
}

void add_operation(bigNum *F){
	int num = F[0].digit[0] - '0' + F[1].digit[0] - '0';
	int cur_digit = 0;
	int digit_max = strlen(F[1].digit);
#ifdef DEBUG
	printf("cur_digit = %d and num = %d\n", cur_digit, num);
#endif
	while(num != 0 || cur_digit < digit_max){
		F[1].digit[cur_digit] = (char) (num % 10) + '0';
		num /= 10;
		cur_digit++;
		if(cur_digit >= digit_Limit){
			exit(-1);
		}
		if(F[0].digit[cur_digit])	num += F[0].digit[cur_digit] - '0';
		if(F[1].digit[cur_digit])	num += F[1].digit[cur_digit] - '0';
#ifdef DEBUG
		printf("cur_digit = %d and num = %d\n", cur_digit, num);
#endif
	}
	if(cur_digit < digit_Limit)	F[1].digit[cur_digit] = '\0';
}

void F_func(bigNum *F, int limit, int times){
	print(times, &(F[0]));
	bigNum temp = F[1];
	if(times < limit){
		add_operation(F);
		F[0] = temp;
		longjmp(jmpbuf, times+1);
	}
	return;
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("argc error\n");
		exit(0);
	}
	bigNum F[2];
	init_Num(F);
	F[0].digit[0] = '1';
	F[1].digit[0] = '1';
	int limit = atoi(argv[1]);
	int jmpVal = setjmp(jmpbuf);
	F_func(F, limit, jmpVal);
	return 0;
}
