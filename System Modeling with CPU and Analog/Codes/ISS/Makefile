CC = g++ -std=c++14
SYSC_AMS_FLAGS = -I$(CPATH) -L/usr/local/systemc-ams-2.3/lib-linux64 -L/usr/local/systemc-2.3.1/lib-linux64 -lsystemc-ams-2.3 -lsystemc-2.3.1 -m64 -O3 -pthread -lm
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} embSys.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

embSys.out: CA6.o squareWave.o Sensor1.o ADC.o tdf2de.o register.o sensor1FrontEnd.o Sensor2.o sensor2FrontEnd.o timer.o Display.o bus_interface.o embSys1.o
	$(CC) $(SYSC_AMS_FLAGS) ${OUT_DIR}CA6.o ${OUT_DIR}squareWave.o ${OUT_DIR}Sensor1.o ${OUT_DIR}ADC.o ${OUT_DIR}tdf2de.o ${OUT_DIR}register.o ${OUT_DIR}sensor1FrontEnd.o ${OUT_DIR}Sensor2.o ${OUT_DIR}sensor2FrontEnd.o ${OUT_DIR}timer.o ${OUT_DIR}Display.o ${OUT_DIR}bus_interface.o ${OUT_DIR}embSys1.o $(CXXFLAGS) $(SYSC_AMS_FLAGS) -o embSys.out

CA6.o: ${SRC_DIR}CA6.cpp ${HDR_DIR}squareWave.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}CA6.cpp -o ${OUT_DIR}CA6.o

squareWave.o: ${SRC_DIR}squareWave.cpp ${HDR_DIR}squareWave.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}squareWave.cpp -o ${OUT_DIR}squareWave.o

Sensor1.o: ${SRC_DIR}Sensor1.cpp ${HDR_DIR}Sensor1.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}Sensor1.cpp -o ${OUT_DIR}Sensor1.o

ADC.o: ${SRC_DIR}ADC.cpp ${HDR_DIR}ADC.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}ADC.cpp -o ${OUT_DIR}ADC.o

tdf2de.o: ${SRC_DIR}tdf2de.cpp ${HDR_DIR}tdf2de.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}tdf2de.cpp -o ${OUT_DIR}tdf2de.o

register.o: ${SRC_DIR}register.cpp ${HDR_DIR}register.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}register.cpp -o ${OUT_DIR}register.o

sensor1FrontEnd.o: ${SRC_DIR}sensor1FrontEnd.cpp ${HDR_DIR}sensor1FrontEnd.h ${HDR_DIR}register.h ${HDR_DIR}tdf2de.h ${HDR_DIR}Sensor1.h ${HDR_DIR}squareWave.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}sensor1FrontEnd.cpp -o ${OUT_DIR}sensor1FrontEnd.o

Sensor2.o: ${SRC_DIR}Sensor2.cpp ${HDR_DIR}Sensor2.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}Sensor2.cpp -o ${OUT_DIR}Sensor2.o

sensor2FrontEnd.o: ${SRC_DIR}sensor2FrontEnd.cpp ${HDR_DIR}sensor2FrontEnd.h ${HDR_DIR}register.h ${HDR_DIR}tdf2de.h ${HDR_DIR}Sensor2.h ${HDR_DIR}squareWave.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}sensor2FrontEnd.cpp -o ${OUT_DIR}sensor2FrontEnd.o

Display.o: ${SRC_DIR}Display.cpp ${HDR_DIR}Display.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}Display.cpp -o ${OUT_DIR}Display.o

timer.o: ${SRC_DIR}timer.cpp ${HDR_DIR}timer.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}timer.cpp -o ${OUT_DIR}timer.o

bus_interface.o: ${HDR_DIR}bus_interface.h ${SRC_DIR}bus_interface.cpp
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}bus_interface.cpp -o ${OUT_DIR}bus_interface.o

Memory.o: ${HDR_DIR}Memory.h ${SRC_DIR}Memory.cpp
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}Memory.cpp -o ${OUT_DIR}Memory.o

embSys1.o: ${HDR_DIR}embSys1.h ${SRC_DIR}embSys1.cpp ${HDR_DIR}Memory.h ${HDR_DIR}sayacInstruction.h
	$(CC) $(CXXFLAGS) $(SYSC_AMS_FLAGS) -c -g ${SRC_DIR}embSys1.cpp -o ${OUT_DIR}embSys1.o


clean:
	rm -r ${OUT_DIR}
	rm embSys.out