CC := g++ --std=c++11
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} sv_compiler.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

sv_compiler.out: CA1.o compiler.o logic.o gate.o functions.o
	$(CC) ${OUT_DIR}CA1.o ${OUT_DIR}compiler.o ${OUT_DIR}logic.o ${OUT_DIR}gate.o ${OUT_DIR}functions.o $(CCFLAGS) -o sv_compiler.out

CA1.o: ${SRC_DIR}CA1.cpp
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}CA1.cpp -o ${OUT_DIR}CA1.o

compiler.o: ${HDR_DIR}compiler.h ${SRC_DIR}compiler.cpp ${HDR_DIR}logic.h ${HDR_DIR}functions.h ${HDR_DIR}wire.h ${HDR_DIR}magic_values.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}compiler.cpp -o ${OUT_DIR}compiler.o

logic.o: ${HDR_DIR}logic.h ${SRC_DIR}logic.cpp ${HDR_DIR}gate.h ${HDR_DIR}wire.h ${HDR_DIR}magic_values.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}logic.cpp -o ${OUT_DIR}logic.o

gate.o: ${HDR_DIR}gate.h ${SRC_DIR}gate.cpp ${HDR_DIR}wire.h ${HDR_DIR}magic_values.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}gate.cpp -o ${OUT_DIR}gate.o

functions.o: ${HDR_DIR}functions.h ${SRC_DIR}functions.cpp ${HDR_DIR}magic_values.h
	$(CC) $(CXXFLAGS) -c ${SRC_DIR}functions.cpp -o ${OUT_DIR}functions.o

clean:
	rm -r ${OUT_DIR}
	rm sv_compiler.out
	rm output_file.txt
