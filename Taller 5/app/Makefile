
NVCC = nvcc

all: app

%.o : %.cu
        $(NVCC) -c $< -o $@

app : app.o
        $(NVCC) $^ -o $@

clean:
        rm -rf *.o *.a app


