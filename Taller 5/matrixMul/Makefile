NVCC = nvcc

all: matrixMul

%.o : %.cu
        $(NVCC) -c $< -o $@

matrixMul : matrixMul.o
        $(NVCC) $^ -o $@

clean:
        rm -rf *.o *.a matrixMul

