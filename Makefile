 #Copyright (C) 2014  Cagdas Caglak http://expcodes.blogspot.com.tr/

 #This program is free software: you can redistribute it and/or modify
 #it under the terms of the GNU General Public License as published by
 #the Free Software Foundation, either version 3 of the License, or
 #(at your option) any later version.

 #This program is distributed in the hope that it will be useful,
 #but WITHOUT ANY WARRANTY; without even the implied warranty of
 #MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 #GNU General Public License for more details.

 #You should have received a copy of the GNU General Public License
 #along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
ECHO=@echo
ECHO_N=@echo -n


EXEC_ADXL345=vibration
EXEC_valores=valores

#CXXFLAGS= "--sysroot=$(SDKTARGETSYSROOT)" -I/home/yeiner/yocto/poky-daisy-11.0.0/beaglebonert/tmp/sysroots/beaglebone/usr/include
CXXFLAGS= "--sysroot=$(SDKTARGETSYSROOT)" -I/home/yarias/Dropbox/ebridge/Maestria/include
#CXXFLAGS= "--sysroot=$(SDKTARGETSYSROOT)" -I/home/yeiner/Dropbox/ebridge/Maestria/include 

all:  $(EXEC_ADXL345) $(EXEC_valores)
	@mkdir -p obj
	@mv *.o obj
#-L/home/yeiner/yocto/poky-daisy-11.0.0/beaglebonert/tmp/sysroots/beaglebone/usr/lib

	
$(EXEC_ADXL345): vibration.o BBB_I2C.o ADXL345.o
	$(ECHO) "$(EXEC_ADXL345) building..."
	@$(CXX) $(CXXFLAGS) vibration.o BBB_I2C.o ADXL345.o -o $(EXEC_ADXL345) -lpthread -lm -lfftw3l -lrt 

$(EXEC_valores): valores.o BBB_I2C.o ADXL345.o
	$(ECHO) "$(EXEC_valores) building..."
	@$(CXX) $(CXXFLAGS) valores.o BBB_I2C.o ADXL345.o -o $(EXEC_valores) -lpthread -lm -lfftw3l -lrt 

	
TestADXL345.o: vibration.cpp
	@$(CXX) -c $(CXXFLAGS) vibration.cpp

valores.o: valores.cpp
	@$(CXX) -c $(CXXFLAGS) valores.cpp
	

ADXL345.o: ADXL345.cpp
	@$(CXX) -c $(CXXFLAGS) ADXL345.cpp
	


clean:
	$(ECHO) "Clean."
	@rm -rf *.o $(EXEC_ARDUINO) $(EXEC_MPU6050) $(EXEC_ADXL345) $(EXEC_HMC5883L) $(EXEC_valores) obj
