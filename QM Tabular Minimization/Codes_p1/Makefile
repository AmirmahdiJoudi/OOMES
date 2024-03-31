CC := g++
SYSC_FLAGS = -I$(CPATH) -L$(LD_LIBRARY_PATH) -lsystemc-2.3.1 -m64 -O3 -pthread -g
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} pps.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

pps.out: CA3.o sc_functional.o sc_functionalTB.o
	$(CC) $(SYSC_FLAGS) ${OUT_DIR}CA3.o ${OUT_DIR}sc_functional.o ${OUT_DIR}sc_functionalTB.o -o pps.out

CA3.o: ${SRC_DIR}CA3.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}CA3.cpp -o ${OUT_DIR}CA3.o

sc_functional.o: ${HDR_DIR}sc_functional.h ${SRC_DIR}sc_functional.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}sc_functional.cpp -o ${OUT_DIR}sc_functional.o

sc_functionalTB.o: ${HDR_DIR}sc_functionalTB.h ${SRC_DIR}sc_functionalTB.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}sc_functionalTB.cpp -o ${OUT_DIR}sc_functionalTB.o

clean:
	rm -r ${OUT_DIR}
	rm pps.out
	rm Assignment.vcd
