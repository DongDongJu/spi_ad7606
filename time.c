#include <sys/time.h>
#include <stdio.h>
int main(){
clock_t start_point, end_point;

start_point = clock();


while(1){
	end_point = clock();
	if((double)(end_point - start_point)/CLOCKS_PER_SEC > 10)
		printf("Exe time : %f sec\n", ((double)(end_point - start_point)/CLOCKS_PER_SEC));
	else
		printf("%f\n",(double)(end_point - start_point)/CLOCKS_PER_SEC);
}
}
