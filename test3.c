 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>

jmp_buf env_sc, env_1; static void scheduler(); void hilo();
int h1=0;
static void scheduler(){ 
	float x=0.123112;
        sigsetjmp(env_sc,1));
	if(h1 !=0) {
	printf("hola soy el scheduler \n");
	siglongjmp(env_1,1); }

         else  hilo();
        
        
	}


void hilo(){
	int cont=0;
	h1=1;
	while(1){
           int returned_from_longjump=1;
	    if (cont==5){
		if ((returned_from_longjump = sigsetjmp(env_1,1)) ==0){
			cont=0;
	  		siglongjmp(env_1,1);}
		}
            printf("soy el hilo");
	    // sleep(1);
	     cont++;
	    }
}

void hilo2(){
	int cont=0;
	while(1){
           int returned_from_longjump=1;
	    if (cont==5){
		if ((returned_from_longjump = sigsetjmp(env_1,1)) ==0){
			cont=0;
	  		scheduler();}
		}
            printf("soy el hilo2");
	    // sleep(1);
	     cont++;
	    }
}


int main() {
scheduler();
}



