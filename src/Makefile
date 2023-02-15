all: clear build

build: build_program_1 build_program_2

build_program_1:
	cd program_1 && \
	make all

build_program_2:
	cd program_2 && \
	make all

clear_program_1:
	cd program_1 && \
	make clear

clear_program_2:
	cd program_2 && \
	make clear

clear: clear_program_1 clear_program_2
