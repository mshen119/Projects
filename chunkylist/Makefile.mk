CXX = g++

CXXFLAGS = -Wall -Wno-uninitialized

BINARIES = main

COMMON_OBJECT_FILES = MyChunkyNode.o main.o MyChunkyList.o

all: ${BINARIES}

main: ${COMMON_OBJECT_FILES}
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@


clean:
	/bin/rm -f ${BINARIES} *.o