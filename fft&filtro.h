#include <stdio.h> /* for printf */ 
#include <stdint.h> /* for uint64 definition */ 
#include <stdlib.h> /* for exit() definition */ 
#include <time.h> /* for clock_gettime */ 
#define BILLION 1000000000L 
#define PI 3.141592653589793

long double *in_z, *in_z2, *in_y, *in_y2, *in_x, *in_x2; // Input FFTW

int n = 32768; //Samples
float ns = 52.4288; //Time
float frec;

fftwl_complex *out_z; // Output FFTW_Z
fftwl_plan plan_forward_z;

fftwl_complex *out_y; // Output FFTW_Y
fftwl_plan plan_forward_y;

fftwl_complex *out_x; // Output FFTW_X
fftwl_plan plan_forward_x;

double z_out, z_h[4], z_in;
double y_out, y_h[4], y_in;
double x_out, x_h[4], x_in;

int l, nc, ffts = 0, end_prog = 1, in_change = 0, j = 0;

char fftsc[10];

pthread_t tid;

FILE *f_z, *f_y, *f_x;
FILE *acc_z, *acc_y, acc_x;

uint64_t diff; struct timespec startx, endx; /* measure monotonic time */ 

char filedata_z [50] = "fftwz_";
char fileacc_z [50] = "accz_";
char filedata_y [50] = "fftwy_";
char fileacc_y [50] = "accy_";
char filedata_x [50] = "fftwx_";
char fileacc_x [50] = "accx_";

void sampling();
void setuptimer();
void *fftw(void *vargp);

BBB_I2C i2c;
ADXL345 adxl(i2c);

void sampling(int signal)
{
	clock_gettime(CLOCK_MONOTONIC, &endx); /* mark the end time */ 
	diff = BILLION * (endx.tv_sec - startx.tv_sec) + endx.tv_nsec - startx.tv_nsec; 
	clock_gettime(CLOCK_MONOTONIC, &startx); /* mark start time */ 
	//printf("elapsed time = %llu nanoseconds\n", (long long unsigned int) diff/1000); /* now re-do this and measure CPU time */ /* the time spent sleeping will not count (but there is a bit of overhead */ 
	
	x_in = adxl.getAccelerationX() * 3.90625;
	y_in = adxl.getAccelerationY() * 3.90625;
	z_in = adxl.getAccelerationZ() * 3.90625;
	
	x_h[0] = x_in + 0.8865483 * x_h[3] - 2.7563006 * x_h[2] + 2.8686094 * x_h[1];
	x_out = 0.0371263 * x_h[3] - 0.0731174 * x_h[2] + 0.0371341 * x_h[1];
	
	y_h[0] = y_in + 0.8865483 * y_h[3] - 2.7563006 * y_h[2] + 2.8686094 * y_h[1];
	y_out = 0.0371263 * y_h[3] - 0.0731174 * y_h[2] + 0.0371341 * y_h[1];
	
	z_h[0] = z_in + 0.8865483 * z_h[3] - 2.7563006 * z_h[2] + 2.8686094 * z_h[1];
	z_out = 0.0371263 * z_h[3] - 0.0731174 * z_h[2] + 0.0371341 * z_h[1];
	
	if(in_change) {
		in_x2[l] = x_out;
		in_y2[l] = y_out;
		in_z2[l] = z_out;
	}
	else {
		in_x[l] = x_out;
		in_y[l] = y_out;
		in_z[l] = z_out;
	}
	l++;
	if(l == n){in_change = !in_change; l = 0; pthread_create(&tid, NULL, fftw, NULL);}
	
	x_h[3] = x_h[2];
	x_h[2] = x_h[1];
	x_h[1] = x_h[0];
	
	y_h[3] = y_h[2];
	y_h[2] = y_h[1];
	y_h[1] = y_h[0];
	
	z_h[3] = z_h[2];
	z_h[2] = z_h[1];
	z_h[1] = z_h[0];
}

void setuptimer()
{
	struct sigaction sa;
	struct itimerval timer;
	
	struct sched_param param;
	int sts;
	
	param.sched_priority = sched_get_priority_max(SCHED_FIFO);
	
	if(sched_setscheduler(0, SCHED_FIFO, &param) == -1) {
			perror("sched_setscheduler failed");
			exit(-1);
	}
	
	memset (&sa, 0, sizeof (sa));
	sa.sa_handler = &sampling;
	sigaction (SIGALRM, &sa, NULL);

	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 1600;

	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 1600;

	setitimer (ITIMER_REAL, &timer, NULL);
} 


void *fftw(void *vargp)
{
	ffts++;
	
	if(in_change)
	{
		plan_forward_z = fftwl_plan_dft_r2c_1d ( n, in_z, out_z, FFTW_ESTIMATE );
		plan_forward_y = fftwl_plan_dft_r2c_1d ( n, in_y, out_y, FFTW_ESTIMATE );
		plan_forward_x = fftwl_plan_dft_r2c_1d ( n, in_x, out_x, FFTW_ESTIMATE );
	}
	else
	{
		plan_forward_z = fftwl_plan_dft_r2c_1d ( n, in_z2, out_z, FFTW_ESTIMATE );
		plan_forward_y = fftwl_plan_dft_r2c_1d ( n, in_y2, out_y, FFTW_ESTIMATE );
		plan_forward_x = fftwl_plan_dft_r2c_1d ( n, in_x2, out_x, FFTW_ESTIMATE );
	}
	
	fftwl_execute ( plan_forward_z );
	fftwl_execute ( plan_forward_y );
	fftwl_execute ( plan_forward_x );
	
	//fftwl_destroy_plan ( plan_forward_z );
	//fftwl_destroy_plan ( plan_forward_y );
	
	printf ( "\n" );
	printf ( "Almacenando Datos\n" );
	
	strcpy(filedata_z, "files/fftwz_");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(filedata_z,strcat(fftsc,".txt"));
	f_z = fopen(filedata_z, "w");
	
/*	strcpy(fileacc_z, "files/accz_");
	strcpy(fftsc, "");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(fileacc_z,strcat(fftsc,".txt"));
	acc_z = fopen(fileacc_z, "w");*/
	
	strcpy(filedata_y, "files/fftwy_");
	strcpy(fftsc, "");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(filedata_y,strcat(fftsc,".txt"));
	f_y = fopen(filedata_y, "w");
	
/*	strcpy(fileacc_y, "files/accy_");
	strcpy(fftsc, "");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(fileacc_y,strcat(fftsc,".txt"));
	acc_y = fopen(fileacc_y, "w");*/
	
	strcpy(filedata_x, "files/fftwx_");
	strcpy(fftsc, "");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(filedata_x,strcat(fftsc,".txt"));
	f_x = fopen(filedata_x, "w");
	
/*	strcpy(fileacc_x, "files/accx_");
	strcpy(fftsc, "");
	//snprintf(fftsc, 10, "%d", ffts);
	snprintf(fftsc, sizeof(fftsc), "%d", ffts);
	strcat(fileacc_y,strcat(fftsc,".txt"));
	acc_x = fopen(fileacc_x, "w");*/

	j = 0;
	for ( j = 1; j < 800; j++ )
	{
		frec = (float)j/ns;
		fprintf(f_z,"%f\t%f\n",frec,sqrt(pow(out_z[j][0]/n,2)+pow(out_z[j][1]/n,2))); //Espectro de Fourier
		fprintf(f_y,"%f\t%f\n",frec,sqrt(pow(out_y[j][0]/n,2)+pow(out_y[j][1]/n,2))); //Espectro de Fourier
		fprintf(f_x,"%f\t%f\n",frec,sqrt(pow(out_x[j][0]/n,2)+pow(out_x[j][1]/n,2))); //Espectro de Fourier
		//fprintf(f,"%f\t%f\n",frec,pow(out[j][0]/n,2)+pow(out[j][1]/n,2)); //Espectro de potencia o densidad espectral
		//printf ( "  %4d  %12f  %12f\n", j, out[j][0], out[j][1] );
		//printf("Angulo: %12f\n", tan((out[j-1][1])/(out[j-1][0]))); // Ángulo
		/*if(in_change)
		{
			fprintf(acc_z,"%f\t%Lf\n",((float)j)/1000, in_z[j]); 
			fprintf(acc_y,"%f\t%Lf\n",((float)j)/1000, in_y[j]);
		}
		else
		{
			fprintf(acc_z,"%f\t%Lf\n",((float)j)/1000, in_z2[j]); 
			fprintf(acc_y,"%f\t%Lf\n",((float)j)/1000, in_y2[j]);
		}*/
	}
	fclose(f_z);
	fclose(f_y);
	fclose(f_x);
	/*for ( j = 1000; j < n; j++ )
	{
		if(in_change)
		{
			fprintf(acc_z,"%f\t%Lf\n",((float)j)/1000, in_z[j]);
			fprintf(acc_y,"%f\t%Lf\n",((float)j)/1000, in_y[j]);
			usleep(50);
		}
		else
		{
			fprintf(acc_z,"%f\t%f\n",((float)j)/1000, in_z2[j]);
			fprintf(acc_y,"%f\t%f\n",((float)j)/1000, in_y2[j]);
			usleep(50);
		}
	}
	fclose(acc_z);
	fclose(acc_y);
	fclose(acc_y);*/
	printf ( "Datos Almacenandos\n" );
	system("sync");
	return NULL;
	//end_prog = 0;
	//system("gnuplot -p -e \"plot '/home/ebridge-vibracion/Programas/fftfiltro/data.txt'\"");
	//system("gnuplot -p -e \"plot 'data.txt' with lines \"");
}

/*
double z_out[8];
double z_in[7];
double y_out[8];
double y_in[7];
double x_out[8];
double x_in[7];
*/

/*	z_out[0] = 4.7560945*z_out[1] - 9.0538584*z_out[2] + 8.6228299*z_out[3] - 4.1085607*z_out[4] + 0.7834925*z_out[5]+ 0.00000001949*z_in[0] + 0.0000005*z_in[1] + 0.0000012*z_in[2]+ 0.0000004*z_in[3] + 0.00000001657*z_in[4];  // n = 5
	y_out[0] = 4.7560945*y_out[1] - 9.0538584*y_out[2] + 8.6228299*y_out[3] - 4.1085607*y_out[4] + 0.7834925*y_out[5]+ 0.00000001949*y_in[0] + 0.0000005*y_in[1] + 0.0000012*y_in[2]+ 0.0000004*y_in[3] + 0.00000001657*y_in[4];  // n = 5
	x_out[0] = 4.7560945*x_out[1] - 9.0538584*x_out[2] + 8.6228299*x_out[3] - 4.1085607*x_out[4] + 0.7834925*x_out[5]+ 0.00000001949*x_in[0] + 0.0000005*x_in[1] + 0.0000012*x_in[2]+ 0.0000004*x_in[3] + 0.00000001657*x_in[4];  // n = 5
*/	

/*	
	z_out[5] = z_out[4];
	z_out[4] = z_out[3];
	z_out[3] = z_out[2];
	z_out[2] = z_out[1];
	z_out[1] = z_out[0];
	
	y_out[5] = y_out[4];
	y_out[4] = y_out[3];
	y_out[3] = y_out[2];
	y_out[2] = y_out[1];
	y_out[1] = y_out[0];
	
	x_out[5] = x_out[4];
	x_out[4] = x_out[3];
	x_out[3] = x_out[2];
	x_out[2] = x_out[1];
	x_out[1] = x_out[0];
	
	z_in[4] = z_in[3];
	z_in[3] = z_in[2];
	z_in[2] = z_in[1];
	z_in[1] = z_in[0];
	
	y_in[4] = y_in[3];
	y_in[3] = y_in[2];
	y_in[2] = y_in[1];
	y_in[1] = y_in[0];
	
	x_in[4] = x_in[3];
	x_in[3] = x_in[2];
	x_in[2] = x_in[1];
	x_in[1] = x_in[0];
	*/
