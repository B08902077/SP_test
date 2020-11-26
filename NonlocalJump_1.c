#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <unistd.h>
#define jump_limit 20
#define loop_limit 10

jmp_buf jmpbuf;

void func(int r){
	if(r < jump_limit){
		longjmp(jmpbuf, r+1);
	}
	return;
}

int main(){
	int jmpVal = setjmp(jmpbuf);
	printf("setjmp already\n"); // longjmp goes back to setjmp, so this code will run 20 times
	do{
		printf("jmpVal = %d\n", jmpVal);
		func(jmpVal);
	}while(jmpVal < loop_limit); // here if loop_limit > jump_limit, then it's infinite while loop
	return 0;
}
