CC := g++
SYSC_FLAGS = -I$(CPATH) -L$(LD_LIBRARY_PATH) -lsystemc-2.3.1 -m64 -O3 -pthread -g
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} channels.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

channels.out: CA5.o GrayScaler.o channel_interface.o EdgeDetector.o
	$(CC) $(SYSC_FLAGS) ${OUT_DIR}CA5.o ${OUT_DIR}GrayScaler.o ${OUT_DIR}channel_interface.o ${OUT_DIR}EdgeDetector.o -o channels.out

CA5.o: ${SRC_DIR}CA5.cpp ${HDR_DIR}GrayScaler.h ${HDR_DIR}System.h
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}CA5.cpp -o ${OUT_DIR}CA5.o

channel_interface.o: ${HDR_DIR}channel_interface.h ${SRC_DIR}channel_interface.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}channel_interface.cpp -o ${OUT_DIR}channel_interface.o

GrayScaler.o: ${HDR_DIR}GrayScaler.h ${SRC_DIR}GrayScaler.cpp ${HDR_DIR}channel_interface.h
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}GrayScaler.cpp -o ${OUT_DIR}GrayScaler.o

EdgeDetector.o: ${HDR_DIR}EdgeDetector.h ${SRC_DIR}EdgeDetector.cpp ${HDR_DIR}channel_interface.h
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}EdgeDetector.cpp -o ${OUT_DIR}EdgeDetector.o

clean:
	rm -r ${OUT_DIR}
	rm channels.out
	rm gray_pixels.txt
	rm edge_detected.txt