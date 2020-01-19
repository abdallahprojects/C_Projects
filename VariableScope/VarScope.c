
#include <stdio.h>
int global = 5; //.bss
void fun(void);
void fun2(void);

int main(void){
	int ret = 0;
	volatile int t;
	static int loc_main;
	//printf("hello world \n\r");
	fun();
	fun2();
	printf("The addess of global is %p \n",&global);
	//sfun();
//  printf("T value is:%d \n",t);
	return ret;
	
}


void fun2(void){
	static int x;
	//printf("X value is %d \n",x);
	printf("The address of x %p \n",&x);
}

void fun(void){
	int st_var;
	printf("The address of st_var is %p \n",&st_var);
	st_var = st_var + 1;
	//printf("Addess of st_var = %d \n",st_var);
	
}

// variable scope
// variable life time (application life time)