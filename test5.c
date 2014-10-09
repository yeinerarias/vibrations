 #include <stdio.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>
 #include <time.h>
 #include <stdlib.h>
 #include <ncurses.h>

jmp_buf env_sc,env_1, env_2,env_3, env_4, env_5, env_crear; 
jmp_buf env_struct [5];
static void scheduler(int signum); 
int h1,h2,h3,h4,h5=0;
static long double acc_h1,acc_h2, acc_h3, acc_h4, acc_h5=0;
int end_h1,end_h2,end_h3,end_h4,end_h5;
int r=-1;


int porcentajehilo1 = 1, porcentajehilo2 = 2, porcentajehilo3 = 4, porcentajehilo4 = 6, porcentajehilo5 = 11;
int n_1, n_2, n_3, n_4, n_5; 
int quantum = 0;
int porcentajehilo1actual = 0, porcentajehilo2actual = 0, porcentajehilo3actual = 0, porcentajehilo4actual = 0, porcentajehilo5actual = 0;
int end_hilo1 = 0, end_hilo2 = 0, end_hilo3 = 0, end_hilo4 = 0, end_hilo5 = 0;

static void scheduler(int signum){ 
		int i;
		
			system("clear");
			printf("Hilo 1: %Le   ",(1+acc_h1)*2.0);
			for(i = 0; i < porcentajehilo1actual;i++)
			{printf("|");}
			printf("\n");
			printf("Hilo 2: %Le   ", (1+acc_h2)*2.0);
			for(i = 0; i < porcentajehilo2actual;i++)
			{printf("*");}
			printf("\n");
			printf("Hilo 3: %Le   ", (1+acc_h3)*2.0);
			for(i = 0; i < porcentajehilo3actual;i++)
			{printf("*");}
			printf("\n");
			printf("Hilo 4: %Le   ", (1+acc_h4)*2.0);
			for(i = 0; i < porcentajehilo4actual;i++)
			{printf("*");}
			printf("\n");
			printf("Hilo 5: %Le   ", (1+acc_h5)*2.0);
			for(i = 0; i < porcentajehilo5actual;i++)
			{printf("*");}
			printf("\n");
		
	if (r!=-1){
		if (( sigsetjmp(env_struct[r],1)==0)) { 
			r =0;//rand() % 5;
	        sigsetjmp(env_struct[r],1);
		}
		
	}

  else{
	r = 0;//rand() % 5;
	sigsetjmp(env_struct[r],1);
      }
	
	
	
	/*switch (r) {
		case 0:
		 sigsetjmp(env_struct[0],1);
		case 1: 
			if(end_h2==0) sigsetjmp(env_struct[1],1); 
		case 2 : 
			if(end_h3==0) sigsetjmp(env_struct[2],1);
		case 3: 
			if(end_h4==0) sigsetjmp(env_struct[3],1);
		case 4: 
			if(end_h5==0) sigsetjmp(env_struct[4],1);
		}*/
	
		
	}
       
	
        

/*
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
*/
void hilo1(){
printf("entre miher\n");

end_h1=0;
static int  i=0;
static float j=0;
static long double acc=1.0;
 acc_h1=0.0;

if (end_h1==0){
	for(i=1;i<n_1+1;i++){
		sigsetjmp(env_1,1);
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
sigsetjmp(env_2,1);
if (h2 ==0) {
}
else{

static int end=0;
static int  i=0;
static float j=0;
static long double acc=1.0;
 acc_h2=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_2,1)) ==0){
	  		siglongjmp(env_sc,1);}
	  		if (end==0){
			for(i=1;i<n_2+1;i++){
				sigsetjmp(env_2,1);
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
      }
         
  } 

void hilo3(){
sigsetjmp(env_3,1);
if (h3 ==0) {
}
else{

end_h3=0;
static int  i=0;
static float j=0;
static long double acc=1.0;
 acc_h3=0.0;
while(1){
       int returned_from_longjump=1;
		if ((returned_from_longjump = sigsetjmp(env_3,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h3==0){
			for(i=1;i<n_3+1;i++){
				sigsetjmp(env_3,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				porcentajehilo3actual = i*57/n_3;
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
static float j=0;
static long double acc=1.0;
 acc_h4=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_4,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h4==0){
			for(i=1;i<n_4+1;i++){
				sigsetjmp(env_4,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				porcentajehilo4actual = i*57/n_4;
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
static float j=0;
static long double acc=1.0;
 acc_h5=0.0;
while(1){


       int returned_from_longjump=1;
	 
		if ((returned_from_longjump = sigsetjmp(env_5,1)) ==0){
			
	  		siglongjmp(env_sc,1);}
	  		if (end_h5==0){
			for(i=1;i<n_5+1;i++){
				sigsetjmp(env_5,1);
				acc=1.0;
				for (j=2*i;j>i;j--){
					acc*=j/(4*(j-i));
					}
				porcentajehilo5actual = i*57/n_5;
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
	   while(1){
			   i=0;
			   acc=1.0;
			   acc_h1=0.0;
			   for(i=1;i<n_1+1;i++){
					   acc=1.0;
					   for (j=2*i;j>i;j--){
							   acc*=j/(4*(j-i));
					   }
					   porcentajehilo1actual = i*57/n_1;
					   acc=acc/(2*i+1);
					   acc_h1=acc_h1+acc;
					   if ((i % (int)(n_1*porcentajehilo1/(100)) == 0) ||(i == n_1)){
							   if(i == n_1){end_hilo1 = 1;}
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
	   while(1){
			   i=0;
			   acc=1.0;
			   acc_h2=0.0;
			   //printf("estoy corriendo hilo 1\n");
			   //sleep(5);
			   for(i=1;i<n_2+1;i++){
					   acc=1.0;
					   for (j=2*i;j>i;j--){
							   acc*=j/(4*(j-i));
					   }
					   porcentajehilo2actual = i*57/n_2;
					   acc=acc/(2*i+1);
					   acc_h2=acc_h2+acc;
					   if ((i % (int)(n_2*porcentajehilo2/(100)) == 0) ||(i == n_2)){
							   if(i == n_2){end_hilo2 = 1;}
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
               while(1){
                       i=0;
                       acc=1.0;
                       acc_h3=0.0;
                       //printf("estoy corriendo hilo 1\n");
                       //sleep(5);
                       for(i=1;i<n_3+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               porcentajehilo3actual = i*57/n_3;
                               acc=acc/(2*i+1);
                               acc_h3=acc_h3+acc;
                               if ((i % (int)(n_3*porcentajehilo3/(100)) == 0) ||(i == n_3)){
                                       if(i == n_3){end_hilo3 = 1;}
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
               while(1){
                       i=0;
                       acc=1.0;
                       acc_h4=0.0;
                       //printf("estoy corriendo hilo 1\n");
                       //sleep(5);
                       for(i=1;i<n_4+1;i++){
                               acc=1.0;
                               for (j=2*i;j>i;j--){
                                       acc*=j/(4*(j-i));
                               }
                               porcentajehilo4actual = i*57/n_4;
                               acc=acc/(2*i+1);
                               acc_h4=acc_h4+acc;
                               if ((i % (int)(n_4*porcentajehilo4/(100)) == 0) ||(i == n_4)){
                                       if(i == n_4){end_hilo4 = 1;}
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
       while(1){
               i=0;
               acc=1.0;
               acc_h5=0.0;
               //printf("estoy corriendo hilo 1\n");
               //sleep(5);
               for(i=1;i<n_5+1;i++){
                       acc=1.0;
                       for (j=2*i;j>i;j--){
                               acc*=j/(4*(j-i));
                       }
                       porcentajehilo5actual = i*57/n_5;
                       acc=acc/(2*i+1);
                       acc_h5=acc_h5+acc;
                       if ((i % (int)(n_5*porcentajehilo5/(100)) == 0) ||(i == n_5)){
                               if(i == n_5){end_hilo5 = 1;}
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

void crear_hilos(){
	if ( sigsetjmp(env_struct[0],1)) 	{
	hilo1();
	return;
	}
	/*if ( sigsetjmp(env_struct[01)) 	{
	hilo2();
	return;}*/
}
int main() {
	
	srand(time(NULL));
	int modo=-1;
	while(modo != 0 && modo != 1)
	{
		printf("¿Modo de trabajo 1 (expropiativo) 0 (no expropiativo)?\n");
		scanf("%x",&modo);
	}
	if(modo){
		printf("Inserte el Quantun en Milisegundos\n");
		scanf("%d",&quantum);
		quantum *= 1000;
	}
	else{
		printf("Porcentaje de Trabajo Hilo 1\n");
		scanf("%d",&porcentajehilo1);
		printf("Porcentaje de Trabajo Hilo 2\n");
		scanf("%d",&porcentajehilo2);
		printf("Porcentaje de Trabajo Hilo 3\n");
		scanf("%d",&porcentajehilo3);
		printf("Porcentaje de Trabajo Hilo 4\n");
		scanf("%d",&porcentajehilo4);
		printf("Porcentaje de Trabajo Hilo 5\n");
		scanf("%d",&porcentajehilo5);
	}
	printf("Unidades de Trabajo para el Hilo 1\n");
	scanf("%d",&n_1);
	n_1 *= 50;
	
	printf("Unidades de Trabajo para el Hilo 2\n");
	scanf("%d",&n_2);
	n_2 *= 50;

	printf("Unidades de Trabajo para el Hilo 3\n");
	scanf("%d",&n_3);
	n_3 *= 50;
	
	printf("Unidades de Trabajo para el Hilo 4\n");
	scanf("%d",&n_4);
	n_4 *= 50;
	
	printf("Unidades de Trabajo para el Hilo 5\n");
	scanf("%d",&n_5);
	n_5 *= 50;	
	
	if (modo) {
	    crear_hilos();
	
		/*
		h1=crear_hilo(0);
		h2=crear_hilo(1);
		h3=crear_hilo(2);
		h4=crear_hilo(3);
		h5=crear_hilo(4);*/
		
		struct sigaction sa;
		struct itimerval timer;
		
		
		/* Install timer_handler as the signal handler for SIGALRM. */
		memset (&sa, 0, sizeof (sa));
		sa.sa_handler = &scheduler;
		sigaction (SIGALRM, &sa, NULL);

		/* Configure the timer to expire after 250 msec... */
		timer.it_value.tv_sec = 0;
		timer.it_value.tv_usec = quantum;
		/* ... and every 250 msec after that. */
		timer.it_interval.tv_sec = 0;
		timer.it_interval.tv_usec = quantum;
		/* Start a real timer. It counts down whenever this process is
		executing. */
		setitimer (ITIMER_REAL, &timer, NULL);
		//scheduler(0);
	}
	else {
		crearhilo1();
		crearhilo2();
		crearhilo3();
		crearhilo4();
		crearhilo5();
		scheduler(0);
	}
	
while(1);
	return 1;
}



