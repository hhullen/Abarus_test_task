COMPILER=g++
STD=--std=c++17
BUILD_FILES=main.cc \
			app2.h \
			server.h
EXECUTABLE=program_2

all: clear build

build:
	$(COMPILER) $(STD) $(BUILD_FILES) -o $(EXECUTABLE)

clear:
	rm -rf a.out *.gch $(EXECUTABLE)