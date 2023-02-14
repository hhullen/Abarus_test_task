COMPILER=g++
STD=--std=c++17
BUILD_FILES=main.cc \
			app1.h \
			inputter.h \
			buffer.h \
			connector.h
EXECUTABLE=program_1

all: clear build

build:
	$(COMPILER) $(STD) $(BUILD_FILES) -o $(EXECUTABLE)

clear:
	rm -rf a.out *.gch $(EXECUTABLE)