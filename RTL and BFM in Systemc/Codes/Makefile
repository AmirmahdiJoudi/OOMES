CC := g++
SYSC_FLAGS = -I$(CPATH) -L$(LD_LIBRARY_PATH) -lsystemc-2.3.1 -m64 -O3 -pthread -g
CXXFLAGS = -Wall -I./headers
MK_DIR = mkdir -p
OUT_DIR = outputs/
SRC_DIR = sources/
HDR_DIR = headers/

all: ${OUT_DIR} sc_rtl.out

${OUT_DIR}:
	${MK_DIR} ${OUT_DIR}

sc_rtl.out: CA4.o memory.o memory_timer.o counter.o register.o datapath.o controller.o stack_handlerTB.o functional_memory_timer.o functional_stack_handler.o
	$(CC) $(SYSC_FLAGS) ${OUT_DIR}CA4.o ${OUT_DIR}memory.o ${OUT_DIR}memory_timer.o ${OUT_DIR}counter.o ${OUT_DIR}register.o ${OUT_DIR}datapath.o ${OUT_DIR}controller.o ${OUT_DIR}stack_handlerTB.o ${OUT_DIR}functional_memory_timer.o ${OUT_DIR}functional_stack_handler.o -o sc_rtl.out

CA4.o: ${SRC_DIR}CA4.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}CA4.cpp -o ${OUT_DIR}CA4.o

memory.o: ${HDR_DIR}memory.h ${SRC_DIR}memory.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}memory.cpp -o ${OUT_DIR}memory.o

memory_timer.o: ${HDR_DIR}memory_timer.h ${SRC_DIR}memory_timer.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}memory_timer.cpp -o ${OUT_DIR}memory_timer.o

functional_memory_timer.o: ${HDR_DIR}functional_memory_timer.h ${SRC_DIR}functional_memory_timer.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}functional_memory_timer.cpp -o ${OUT_DIR}functional_memory_timer.o

counter.o: ${HDR_DIR}counter.h ${SRC_DIR}counter.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}counter.cpp -o ${OUT_DIR}counter.o

register.o: ${HDR_DIR}register.h ${SRC_DIR}register.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}register.cpp -o ${OUT_DIR}register.o

datapath.o: ${HDR_DIR}datapath.h ${SRC_DIR}datapath.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}datapath.cpp -o ${OUT_DIR}datapath.o

controller.o: ${HDR_DIR}controller.h ${SRC_DIR}controller.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}controller.cpp -o ${OUT_DIR}controller.o

stack_handlerTB.o: ${HDR_DIR}stack_handlerTB.h ${HDR_DIR}stack_handler.h ${SRC_DIR}stack_handlerTB.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}stack_handlerTB.cpp -o ${OUT_DIR}stack_handlerTB.o

functional_stack_handler.o: ${HDR_DIR}functional_stack_handler.h ${SRC_DIR}functional_stack_handler.cpp
	$(CC) $(CXXFLAGS) $(SYSC_FLAGS) -c ${SRC_DIR}functional_stack_handler.cpp -o ${OUT_DIR}functional_stack_handler.o

clean:
	rm -r ${OUT_DIR}
	rm sc_rtl.out
	rm StackHandlerTestBench.vcd
