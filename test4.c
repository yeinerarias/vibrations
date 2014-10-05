 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <stdlib.h>

jmp_buf env_sc, env_1, env_2,env_3, env_4, env_5, env_crear; 
static void scheduler(int signum); 
int h1,h2,h3,h4,h5=0;
static long double acc_h1,acc_h2, acc_h3, acc_h4, acc_h5=0;
int end_h1,end_h2,end_h3,end_h4,end_h5;


//cochinadas de Yeier

int porcentajehilo1 = 1, porcentajehilo2 = 2, porcentajehilo3 = 4, porcentajehilo4 = 6, porcentajehilo5 = 11;
int porcentajehilo1actual = 0, porcentajehilo2actual = 0, porcentajehilo3actual = 0, porcentajehilo4actual = 0, porcentajehilo5actual = 0;
long double pi_hilo1, pi_hilo2, pi_hilo3, pi_hilo4, pi_hilo5;
int end_hilo1 = 0, end_hilo2 = 0, end_hilo3 = 0, end_hilo4 = 0, end_hilo5 = 0;

static void scheduler(int signum){ 
	while(1){
        sigsetjmp(env_sc,1);
		int r = rand() % 5;
		switch (r) {
		case 0:
		system("clear");
	    //printf("hola soy el scheduler \n");
	    printf("Hilo 1: %Le   ***\n", (1+acc_h1)*2.0);
	    printf("Hilo 2: %Le \n", (1+acc_h2)*2.0);
	    printf("Hilo 3: %Le \n", (1+acc_h3)*2.0);
	    printf("Hilo 4: %Le \n", (1+acc_h4)*2.0);
	    printf("Hilo 5: %Le \n", (1+acc_h5)*2.0);
			if(end_h1==0) siglongjmp(env_1,1);
		case 1: 
		system("clear");
	    //printf("hola soy el scheduler \n");
	    printf("Hilo 1: %Le \n", (1+acc_h1)*2.0);
	    printf("Hilo 2: %Le   ***\n", (1+acc_h2)*2.0);
	    printf("Hilo 3: %Le \n", (1+acc_h3)*2.0);
	    printf("Hilo 4: %Le \n", (1+acc_h4)*2.0);
	    printf("Hilo 5: %Le \n", (1+acc_h5)*2.0);
			if(end_h2==0) siglongjmp(env_2,1); 
		case 2 : 
		system("clear");
	    //printf("hola soy el scheduler \n");
	    printf("Hilo 1: %Le \n", (1+acc_h1)*2.0);
	    printf("Hilo 2: %Le \n", (1+acc_h2)*2.0);
	    printf("Hilo 3: %Le   ***\n", (1+acc_h3)*2.0);
	    printf("Hilo 4: %Le \n", (1+acc_h4)*2.0);
	    printf("Hilo 5: %Le \n", (1+acc_h5)*2.0);
			if(end_h3==0) siglongjmp(env_3,1);
		case 3: 
		system("clear");
	    //printf("hola soy el scheduler \n");
	    printf("Hilo 1: %Le \n", (1+acc_h1)*2.0);
	    printf("Hilo 2: %Le \n", (1+acc_h2)*2.0);
	    printf("Hilo 3: %Le \n", (1+acc_h3)*2.0);
	    printf("Hilo 4: %Le   ***\n", (1+acc_h4)*2.0);
	    printf("Hilo 5: %Le \n", (1+acc_h5)*2.0);
			if(end_h4==0) siglongjmp(env_4,1);
		case 4: 
		system("clear");
	    //printf("hola soy el scheduler \n");
	    printf("Hilo 1: %Le \n", (1+acc_h1)*2.0);
	    printf("Hilo 2: %Le \n", (1+acc_h2)*2.0);
	    printf("Hilo 3: %Le \n", (1+acc_h3)*2.0);
	    printf("Hilo 4: %Le \n", (1+acc_h4)*2.0);
	    printf("Hilo 5: %Le   ***\n", (1+acc_h5)*2.0);
			if(end_h5==0) siglongjmp(env_5,1);
		}
	}
        
}

static void _scheduler(){
       
       sigsetjmp(env_sc,2);

               //printf("hola soy el scheduler \n");
               system("clear");
               int r = rand() % 5;
               switch (r) {
               case 0:
                               printf("Se esta ejecutando el hilo 1 \nPorcentaje = %d\n",porcentajehilo1);
                               siglongjmp(env_1,1);
               case 1:
                               printf("Se esta ejecutando el hilo 2 \nPorcentaje = %d\n",porcentajehilo2);
                          siglongjmp(env_2,1);
               case 2 :
                               printf("Se esta ejecutando el hilo 3 \nPorcentaje = %d\n",porcentajehilo3);
                          siglongjmp(env_3,1);
               case 3:
                               printf("Se esta ejecutando el hilo 4 \nPorcentaje = %d\n",porcentajehilo4);  
                          siglongjmp(env_4,1);
               case 4:
                               printf("Se esta ejecutando el hilo 5 \nPorcentaje = %d\n",porcentajehilo1);
                          siglongjmp(env_5,1);
       }
}

void hilo1(){
sigsetjmp(env_1,1);
if (h1 ==0) {
}
else{
end_h1=0;
static int  i=0;
static int n=30000;
static float j=0;
static long double acc=1.0;
 acc_h1=0.0;
while(1){
        int returned_from_longjump=1;
	   
		if ((returned_from_longjump = sigsetjmp(env_1,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  	if (end_h1==0){
			for(i=1;i<n+1;i++){
				sigsetjmp(env_1,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				acc=acc/(2*i+1);
				acc_h1=acc_h1+acc;
				}
			 
			  end_h1=1;
			  
			}  
          
	    }
      }
         
  } 
 
     
void hilo2(){
sigsetjmp(env_2,1);
if (h2 ==0) {
}
else{

static int end=0;
static int  i=0;
static int n=15000;
static float j=0;
static long double acc=1.0;
 acc_h2=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_2,1)) ==0){
	  		siglongjmp(env_sc,1);}
	  		if (end==0){
			for(i=1;i<n+1;i++){
				sigsetjmp(env_2,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				acc=acc/(2*i+1);
				acc_h2=acc_h2+acc;
				}
			 
			  end_h2=1;
			  
			}
  
	    }
      }
         
  } 


void hilo3(){
sigsetjmp(env_3,1);
if (h3 ==0) {
}
else{

end_h3=0;
static int  i=0;
static int n=12000;
static float j=0;
static long double acc=1.0;
 acc_h3=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_3,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h3==0){
			for(i=1;i<n+1;i++){
				sigsetjmp(env_3,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				acc=acc/(2*i+1);
				acc_h3=acc_h3+acc;
				}
			 
			  end_h3=1;
			  
			}
  
	    }
      }
         
  } 

void hilo4(){
sigsetjmp(env_4,1);
if (h4 ==0) {
}
else{

end_h4=0;
static int  i=0;
static int n=32000;
static float j=0;
static long double acc=1.0;
 acc_h4=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_4,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h4==0){
			for(i=1;i<n+1;i++){
				sigsetjmp(env_4,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				acc=acc/(2*i+1);
				acc_h4=acc_h4+acc;
				}
			 
			  end_h4=1;
			  
			}
  
	    }
      }
} 

void hilo5(){
sigsetjmp(env_5,1);
if (h5==0) {
}
else{

end_h5=0;
static int  i=0;
static int n=33000;
static float j=0;
static long double acc=1.0;
 acc_h5=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_5,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h5==0){
			for(i=1;i<n+1;i++){
				sigsetjmp(env_5,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				acc=acc/(2*i+1);
				acc_h5=acc_h5+acc;
				}
			 
			  end_h5=1;
			  
			}
  
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


void _hilo1(){
               if (sigsetjmp(env_1,2) == 0){
                       printf("ya me cree hilo 1\n");
                       siglongjmp(env_crear,1);}
               static float j;
               static int i=0;
               static long double acc=1.0;
               static long double acc_aux=0.0;
               static int n = 30000;
               while(1){
                       i=0;
                       acc=1.0;
                       acc_aux=0.0;
                       n = 30000;
                       for(i=1;i<n+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               acc=acc/(2*i+1);
                               acc_aux=acc_aux+acc;
                               if ((i % (int)(n*porcentajehilo1/(100)) == 0) ||(i == n)){
                                       if(i == n){end_hilo1 = 1;}
                                       pi_hilo1 = (1+acc_aux)*2.0;
                                       if (sigsetjmp(env_1,2) == 0){
                                               siglongjmp(env_sc,1);}
                               }
                       }
               }
       }
 
 void _hilo2(){
               if (sigsetjmp(env_2,2) == 0){
                       printf("ya me cree hilo 2\n");
                       siglongjmp(env_crear,1);}
               static float j;
               static int i=0;
               static long double acc=1.0;
               static long double acc_aux=0.0;
               static int n = 30000;
               while(1){
                       i=0;
                       acc=1.0;
                       acc_aux=0.0;
                       n = 30000;
                       //printf("estoy corriendo hilo 1\n");
                       //sleep(5);
                       for(i=1;i<n+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               acc=acc/(2*i+1);
                               acc_aux=acc_aux+acc;
                               if ((i % (int)(n*porcentajehilo2/(100)) == 0) ||(i == n)){
                                       if(i == n){end_hilo2 = 1;}
                                       pi_hilo2 = (1+acc_aux)*2.0;
                                       if (sigsetjmp(env_2,2) == 0){
                                               siglongjmp(env_sc,1);}
                               }
                       }
               }
       }
void _hilo3(){
               if (sigsetjmp(env_3,2) == 0){
                       printf("ya me cree hilo 3\n");
                       siglongjmp(env_crear,1);}
               static float j;
               static int i=0;
               static long double acc=1.0;
               static long double acc_aux=0.0;
               static int n = 30000;
               while(1){
                       i=0;
                       acc=1.0;
                       acc_aux=0.0;
                       n = 30000;
                       //printf("estoy corriendo hilo 1\n");
                       //sleep(5);
                       for(i=1;i<n+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               acc=acc/(2*i+1);
                               acc_aux=acc_aux+acc;
                               if ((i % (int)(n*porcentajehilo3/(100)) == 0) ||(i == n)){
                                       if(i == n){end_hilo3 = 1;}
                                       pi_hilo3 = (1+acc_aux)*2.0;
                                       if (sigsetjmp(env_3,2) == 0){
                                               siglongjmp(env_sc,1);}
                               }
                       }
               }
       }

 void _hilo4(){
               if (sigsetjmp(env_4,2) == 0){
                       printf("ya me cree hilo 4\n");
                       siglongjmp(env_crear,1);}
               static float j;
               static int i=0;
               static long double acc=1.0;
               static long double acc_aux=0.0;
               static int n = 30000;
               while(1){
                       i=0;
                       acc=1.0;
                       acc_aux=0.0;
                       n = 30000;
                       //printf("estoy corriendo hilo 1\n");
                       //sleep(5);
                       for(i=1;i<n+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               acc=acc/(2*i+1);
                               acc_aux=acc_aux+acc;
                               if ((i % (int)(n*porcentajehilo4/(100)) == 0) ||(i == n)){
                                       if(i == n){end_hilo4 = 1;}
                                       pi_hilo4 = (1+acc_aux)*2.0;
                                       if (sigsetjmp(env_4,2) == 0){
                                               siglongjmp(env_sc,1);}
                               }
                       }
               }
       }
void _hilo5(){
       if (sigsetjmp(env_5,2) == 0){
               printf("ya me cree hilo 5\n");
                 siglongjmp(env_crear,1);}
       static float j;
       static int i=0;
       static long double acc=1.0;
       static long double acc_aux=0.0;
       static int n = 30000;
       while(1){
               i=0;
               acc=1.0;
               acc_aux=0.0;
               n = 30000;
               //printf("estoy corriendo hilo 1\n");
               //sleep(5);
               for(i=1;i<n+1;i++){
                       acc=1.0;
                       for (j=2*i;j>i;j--){
                               acc*=j/(4*(j-i));
                       }
                       acc=acc/(2*i+1);
                       acc_aux=acc_aux+acc;
                       if ((i % (int)(n*porcentajehilo5/(100)) == 0) ||(i == n)){
                               if(i == n){end_hilo5 = 1;}
                               pi_hilo5 = (1+acc_aux)*2.0;
                               if (sigsetjmp(env_5,2) == 0){
                                       siglongjmp(env_sc,1);}
                       }
               }
       }
}

 

void crearhilo1(){
       if (!sigsetjmp(env_crear,1))
       {_hilo1();}
}
void crearhilo2(){
       if (!sigsetjmp(env_crear,1))
       {_hilo2();}
}
void crearhilo3(){
       if (!sigsetjmp(env_crear,1))
       {_hilo3();}
}
void crearhilo4(){
       if (!sigsetjmp(env_crear,1))
       {_hilo4();}
}
void crearhilo5(){
       if (!sigsetjmp(env_crear,1))
       {_hilo5();}
}






































int main() {
srand(time(NULL));
int modo=1;
if (modo) {
h1=crear_hilo(0);
h2=crear_hilo(1);
h3=crear_hilo(2);
h4=crear_hilo(3);
h5=crear_hilo(4);
 struct sigaction sa;
 struct itimerval timer;

 /* Install timer_handler as the signal handler for SIGALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &scheduler;
 sigaction (SIGALRM, &sa, NULL);

 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 200000;
 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = 200000;
 /* Start a real timer. It counts down whenever this process is
   executing. */
 setitimer (ITIMER_REAL, &timer, NULL);
}
else {
crearhilo1();
crearhilo2();
crearhilo3();
crearhilo4();
crearhilo5();
_scheduler();
}




while(1);
return 1;
}



