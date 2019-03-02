GCC = gcc
OMP = -fopenmp

build:
	${GCC} serial.c -o saxpySerial ${OMP}
	${GCC} parallel.c -o saxpyParallel ${OMP}
	./saxpySerial
	./saxpyParallel