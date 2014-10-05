 #include <stdio.h>
 #include <time.h>
 #include <stdlib.h>
 #include <setjmp.h>
 #include <signal.h>
 #include <unistd.h>
 #include <sys/time.h>

jmp_buf env_sc, env_1, env_2, env_3, env_4, env_5, env_crear; static void scheduler(); void crearhilo(); void hilo1(); void hilo2(); void hilo3(); void hilo4(); void hilo5();

static void scheduler(){ 
	sigsetjmp(env_sc,2);
 
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
	if (sigsetjmp(env_1,2) == 0){
		printf("ya me cree hilo 1\n"); 
	  	siglongjmp(env_crear,1);}
	static int cont=0;
	while(1){
		printf("estoy corriendo hilo 1\n"); 
	    if (cont==2){
			if (sigsetjmp(env_1,2) == 0){
				cont=0;
				siglongjmp(env_sc,1);}
			}
			sleep(1);
			++cont;
	    }
}

void hilo2(){
	if (sigsetjmp(env_2,2) == 0){
		printf("ya me cree hilo 2\n"); 
	  	siglongjmp(env_crear,1);}
	static int cont=0;
	while(1){
		printf("estoy corriendo hilo 2\n"); 
	    if (cont==2){
			if (sigsetjmp(env_2,2) == 0){
				cont=0;
				siglongjmp(env_sc,1);}
			}
			sleep(1);
			++cont;
	    }
}

void hilo3(){
	if (sigsetjmp(env_3,2) == 0){
		printf("ya me cree hilo 3\n"); 
	  	siglongjmp(env_crear,1);}
	static int cont=0;
	while(1){
		printf("estoy corriendo hilo 3\n"); 
	    if (cont==2){
			if (sigsetjmp(env_3,2) == 0){
				cont=0;
				siglongjmp(env_sc,1);}
			}
			sleep(1);
			++cont;
	    }
}

void hilo4(){
	if (sigsetjmp(env_4,2) == 0){
		printf("ya me cree hilo 4\n"); 
	  	siglongjmp(env_crear,1);}
	static int cont=0;
	while(1){
		printf("estoy corriendo hilo 4\n"); 
	    if (cont==2){
			if (sigsetjmp(env_4,2) == 0){
				cont=0;
				siglongjmp(env_sc,1);}
			}
			sleep(1);
			++cont;
	    }
}

void hilo5(){
	if (sigsetjmp(env_5,2) == 0){
		printf("ya me cree hilo 5\n"); 
	  	siglongjmp(env_crear,1);}
	static int cont=0;
	while(1){
		printf("estoy corriendo hilo 5\n"); 
	    if (cont==2){
			if (sigsetjmp(env_5,2) == 0){
				cont=0;
				siglongjmp(env_sc,1);}
			}
			sleep(1);
			++cont;
	    }
}

void crearhilo1(){
	if ((sigsetjmp(env_crear,1)) == 0)
	{hilo1();}
}
void crearhilo2(){
	if ((sigsetjmp(env_crear,1)) == 0)
	{hilo2();}
}
void crearhilo3(){
	if ((sigsetjmp(env_crear,1)) == 0)
	{hilo3();}
}
void crearhilo4(){
	if ((sigsetjmp(env_crear,1)) == 0)
	{hilo4();}
}
void crearhilo5(){
	if ((sigsetjmp(env_crear,1)) == 0)
	{hilo5();}
}


int main() {
	crearhilo1();
	crearhilo2();
	crearhilo3();
	crearhilo4();
	crearhilo5();
	scheduler();
	return(0);
}


