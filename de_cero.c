 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <stdlib.h>
 #include <ncurses.h>


jmp_buf env_struct [5];
static void scheduler(int signum); 

static long double acc_h1,acc_h2;
int end_h1,end_h2,end_h3,end_h4,end_h5;
static int r=-1;


int porcentajehilo1 = 1, porcentajehilo2 = 2, porcentajehilo3 = 4, porcentajehilo4 = 6, porcentajehilo5 = 11;
int n_1=30000, n_2=30000, n_3, n_4, n_5=30000; 
int quantum = 0;
int porcentajehilo1actual = 0, porcentajehilo2actual = 0, porcentajehilo3actual = 0, porcentajehilo4actual = 0, porcentajehilo5actual = 0;
int end_hilo1 = 0, end_hilo2 = 0, end_hilo3 = 0, end_hilo4 = 0, end_hilo5 = 0;

static void scheduler(int signum){ 
	if (r != -1){
		if(sigsetjmp(env_struct[r],1)==0){
		    printf("no vengo de un salto, pi1 es %Le \n",(1+acc_h1)*2.0);
		    printf("no vengo de un salto, pi2 es %Le \n",(1+acc_h2)*2.0);
		    r=rand() % 2;
		    siglongjmp(env_struct[r],1);
		   
	}
	else{
	   }
	}
	else{
	r=rand() % 2;
	printf(" va el hilo %d \n",1+ r);
	siglongjmp(env_struct[r],1);}
}


void hilo1(){
end_h1=0;
static int  i=0;
static float j=0;
static long double acc=1.0;
 acc_h1=0.0;

if (end_h1==0){
	
	for(i=1;i<n_1+1;i++){
		acc=1.0;
		for (j=2*i;j>i;j--){
			acc*=j/(4*(j-i));
			}
		porcentajehilo1actual = i*57/n_1;
		acc=acc/(2*i+1);
		acc_h1=acc_h1+acc;

		}
	 
	  end_h1=1;
	  
	}    
 } 
     
void hilo2(){
end_h2=0;
static int  i=0;
static float j=0;
static long double acc=1.0;
acc_h2=0.0;

if (end_h2==0){

	for(i=1;i<n_2+1;i++){
		acc=1.0;
		for (j=2*i;j>i;j--){
			acc*=j/(4*(j-i));
			}
		porcentajehilo2actual = i*57/n_2;
		acc=acc/(2*i+1);
		acc_h2=acc_h2+acc;
		
		}
  
	end_h2=1;
	}
        
 } 




void crear_hilos(){

	if ( sigsetjmp(env_struct[0],1)!=0 )	{
	hilo1();
	printf ("chao mundo_1");
	return;
	}
	
	if (sigsetjmp(env_struct[1],1)!=0) 	{
	printf("hola mundo_2 \n");
	hilo2();
	printf ("chao mundo_2 \n");
	return;}
}


int main() {
		srand(time(NULL));

		struct sigaction sa;
		struct itimerval timer;
	
		memset (&sa, 0, sizeof (sa));
		sa.sa_handler = &scheduler;
		sigaction (SIGALRM, &sa, NULL);

		timer.it_value.tv_sec = 0;
		timer.it_value.tv_usec = 100000;
		/* ... and every 250 msec after that. */
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_usec = 100000;
		/* Start a real timer. It counts down whenever this process is
		executing. */
		setitimer (ITIMER_REAL, &timer, NULL);
	
		crear_hilos();
		
	
while(1);
return 1;
}
