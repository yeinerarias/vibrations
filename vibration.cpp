/*
 Copyright (C) 2014  Cagdas Caglak cagdascaglak@gmail.com http://expcodes.blogspot.com.tr/

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "ADXL345.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fftw3.h>
#include <pthread.h>

#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#include <sched.h>
#include <sys/mman.h>

using namespace cacaosd_bbb_i2c;
using namespace cacaosd_adxl345;

#include "fft&filtro.h"

#define MY_PRIORITY (99)
struct sched_param param;
using namespace std;
	
int main();

int main()
{
	adxl.initialize();
	adxl.setLowPowerEnabled(0); //Operación normal (nivel de ruido bajo)
	adxl.setRate(ADXL345_RATE_1600); // Idd = 90 uA
	adxl.setRange(0x3); // +-16g 
	adxl.setFullResolution(1); // 4mg para +-16g 13 bits
	
	in_x = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	in_x2 = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	
	in_y = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	in_y2 = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	
	in_z = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	in_z2 = (long double*)fftwl_malloc ( sizeof ( long double ) * n );
	
	nc = ( n / 2 ) + 1;

	out_x = (fftwl_complex*)fftwl_malloc ( sizeof ( fftwl_complex ) * nc );
	out_y = (fftwl_complex*)fftwl_malloc ( sizeof ( fftwl_complex ) * nc );
	out_z = (fftwl_complex*)fftwl_malloc ( sizeof ( fftwl_complex ) * nc );
	
	l = 0;
	
	setuptimer();
	
   while(end_prog){
		sleep(1000);
	}
	
	 /*
	Release the memory associated with the plans.
    */
    
	fftwl_destroy_plan ( plan_forward_x );
    fftwl_destroy_plan ( plan_forward_y );
    fftwl_destroy_plan ( plan_forward_z );
    
    /*
	Release the memory.
	*/
	
	fftwl_free ( in_x );
	fftwl_free ( in_x2 );
	fftwl_free ( out_x );
	
	fftwl_free ( in_y );
	fftwl_free ( in_y2 );
	fftwl_free ( out_y );
	
	fftwl_free ( in_z );
	fftwl_free ( in_z2 );
	fftwl_free ( out_z );
	
	return 0;
}
