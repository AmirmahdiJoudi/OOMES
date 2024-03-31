CC := g++ --std=c++11
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} fault.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

fault.out: CA2.o wire.o gate.o compiler.o logic.o functions.o fc.o fs.o
	$(CC) ${OUT_DIR}CA2.o ${OUT_DIR}wire.o ${OUT_DIR}gate.o ${OUT_DIR}compiler.o  ${OUT_DIR}logic.o ${OUT_DIR}functions.o ${OUT_DIR}fc.o ${OUT_DIR}fs.o -o fault.out

CA2.o: ${SRC_DIR}CA2.cpp ${HDR_DIR}wire.h ${HDR_DIR}gate.h ${HDR_DIR}compiler.h ${HDR_DIR}logic.h ${HDR_DIR}fc.h ${HDR_DIR}fs.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}CA2.cpp -o ${OUT_DIR}CA2.o

wire.o: ${HDR_DIR}wire.h ${SRC_DIR}wire.cpp
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}wire.cpp -o ${OUT_DIR}wire.o

gate.o: ${HDR_DIR}gate.h ${SRC_DIR}gate.cpp
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}gate.cpp -o ${OUT_DIR}gate.o

compiler.o: ${HDR_DIR}compiler.h ${SRC_DIR}compiler.cpp ${HDR_DIR}functions.h ${HDR_DIR}logic.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}compiler.cpp -o ${OUT_DIR}compiler.o

logic.o: ${HDR_DIR}logic.h ${SRC_DIR}logic.cpp ${HDR_DIR}functions.h ${HDR_DIR}gate.h ${HDR_DIR}fc.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}logic.cpp -o ${OUT_DIR}logic.o

functions.o: ${HDR_DIR}functions.h ${SRC_DIR}functions.cpp ${HDR_DIR}magic_values.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}functions.cpp -o ${OUT_DIR}functions.o

fc.o: ${HDR_DIR}fc.h ${SRC_DIR}fc.cpp ${HDR_DIR}wire.h ${HDR_DIR}gate.h ${HDR_DIR}fs.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}fc.cpp -o ${OUT_DIR}fc.o

fs.o: ${HDR_DIR}fs.h ${SRC_DIR}fs.cpp ${HDR_DIR}wire.h ${HDR_DIR}gate.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}fs.cpp -o ${OUT_DIR}fs.o

clean:
	rm -r ${OUT_DIR}
	rm fault.out
	rm fc_output_file.txt
	rm fs_output_file.txt
