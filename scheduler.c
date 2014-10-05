#include <stdio.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

jmp_buf env; 

static void signal_handler();

int main()
{
	 int returned_from_longjump, processing = 1;
	 unsigned int time_interval = 1;
	 returned_from_longjump = sigsetjmp(env,1);
		 switch (returned_from_longjump)     {
		   case SIGINT:
			 printf("longjumped from interrupt %d\n",SIGINT);
			 break;
		   case SIGALRM:
			 printf("longjumped from alarm %d\n",SIGALRM);
			 break;
		 }
	 signal(SIGINT, signal_handler);
	 signal(SIGALRM, signal_handler);
	 alarm(time_interval);
	 while (processing)        {
	   printf(" waiting for you to INTERRUPT (cntrl-C) ...\n");
	   sleep(1);
	 }       /* end while forever loop */
	 return 1;
}

static void signal_handler(int sig)
{
	 switch (sig)     {
	   case SIGINT:
			   siglongjmp(env,sig);
							 /* break never reached */
	   case SIGALRM:  
					  
			siglongjmp(env,sig);
							/* break never reached */

	 }
}
