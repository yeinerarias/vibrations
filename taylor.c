 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <stdlib.h>
 #include <math.h>


 
 long double pi_taylor(int n){
	int i=0;
	float j;
	long double acc=1.0;
	long double acc_aux=0.0;
	for(i=1;i<n+1;i++){
		j=2*i;
		acc=1.0;
		for (j;j>i;j--){
			acc*=j/(4*(j-i));
			}
		acc=acc/(2*i+1);
		acc_aux=acc_aux+acc;
		}
	  
	  acc_aux=(1+acc_aux)*2.0;
	  printf("%Le", acc_aux);
	 return acc;
	 }
 
 

int main() {
int n=30000;
long double acc=0.0;
acc=pi_taylor(n);
}
