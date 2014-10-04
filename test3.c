 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <stdlib.h>

jmp_buf env_sc, env_1, env_2,env_3, env_4, env_5; 
static void scheduler(); 
int h1,h2,h3,h4,h5=0;


static void scheduler(){ 
        sigsetjmp(env_sc,1);
	    printf("hola soy el scheduler \n");
	    
		srand(time(NULL));
		int r = rand() % 5;
		switch (r) {
		case 0:
			siglongjmp(env_1,1);
		case 1: 
			siglongjmp(env_2,1); 
		case 2 : 
			siglongjmp(env_3,1);
		case 3: 
			siglongjmp(env_4,1);
		case 4: 
			siglongjmp(env_5,1);
	}
        
}


void hilo1(){
sigsetjmp(env_1,1);
if (h1 ==0) {
}
else{
int cont=0;
while(1){

	
        int returned_from_longjump=1;
	    if (cont==2){
		if ((returned_from_longjump = sigsetjmp(env_1,1)) ==0){
            
			cont=0;
	  		siglongjmp(env_sc,1);}
		}
            printf("soy el hilo 1 \n");
	     sleep(1);
	     cont++;
	    }
      }
         
  } 
 
     
void hilo2(){
sigsetjmp(env_2,1);
if (h2 ==0) {
}
else{
int cont=0;
while(1){

	
           int returned_from_longjump=1;
	    if (cont==2){
		if ((returned_from_longjump = sigsetjmp(env_2,1)) ==0){
       
			cont=0;
	  		siglongjmp(env_sc,1);}
		}
            printf("soy el hilo 2 \n");
	     sleep(1);
	     cont++;
	    }
      }
         
  } 


void hilo3(){
sigsetjmp(env_3,1);
if (h3 ==0) {
}
else{
int cont=0;
while(1){

	
           int returned_from_longjump=1;
	    if (cont==2){
		if ((returned_from_longjump = sigsetjmp(env_3,1)) ==0){
                        
			cont=0;
	  		siglongjmp(env_sc,1);}
		}
            printf("soy el hilo 3 \n");
	     sleep(1);
	     cont++;
	    }
      }
         
  } 

void hilo4(){
sigsetjmp(env_4,1);
if (h4 ==0) {
}
else{
int cont=0;
while(1){

	
           int returned_from_longjump=1;
	    if (cont==2){
		if ((returned_from_longjump = sigsetjmp(env_4,1)) ==0){
                        
			cont=0;
	  		siglongjmp(env_sc,1);}
		}
            printf("soy el hilo 4 \n");
	     sleep(1);
	     cont++;
	    }
      }
         
  } 

void hilo5(){
sigsetjmp(env_5,1);
if (h5==0) {
}
else{
int cont=0;
while(1){

	
           int returned_from_longjump=1;
	    if (cont==2){
		if ((returned_from_longjump = sigsetjmp(env_5,1)) ==0){
                        
			cont=0;
	  		siglongjmp(env_sc,1);}
		}
            printf("soy el hilo 5 \n");
	     sleep(1);
	     cont++;
	    }
      }
         
  } 

int crear_hilo(int ID){
switch (ID){
case 0: 
        hilo1();
      
case 1: 
        hilo2();
case 2: 
        hilo3();
      
case 3: 
        hilo4();
case 4: 
        hilo5();
      

                

}
return 1;
}



int main() {
h1=crear_hilo(0);
h2=crear_hilo(1);
h3=crear_hilo(2);
h4=crear_hilo(3);
h5=crear_hilo(4);

scheduler();
return 1;
}



