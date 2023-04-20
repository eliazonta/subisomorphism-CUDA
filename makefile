CUDA_HOME=/usr/local/cuda-12.1
NVCC = ${CUDA_HOME}/bin/nvcc
CC = c++
NVCC_FLAG = -std=c++14
GPU_ARCH = -arch=sm_70 -m64
# GPU_ARCH := -arch=sm_52 # try
LIBS = -L${CUDA_HOME}/lib64
OPT = -std=c++14 -O3
#OPT = -O3 -g

# name
NN := main
INCLUDE := dep.h
BIN_FOLDER := bin
SRC_FOLDER := src
OBJ_FOLDER := obj
BATCH_OUT_FOLDER := out
INCLUDE_FOLDER := include


OBJS := $(OBJ_FOLDER)/$(NN)
MAIN := $(NN).cu

################################################

all : $(BIN_FOLDER)/$(NN)


debug : OPT += -DDEBUG -g
debug : NVCC_FLAG += -G
debug : all

$(BIN_FOLDER)/$(NN) : $(SRC_FOLDER)/${MAIN}
	@mkdir -p $(@D)	
	@mkdir -p $(BATCH_OUT_FOLDER)
	$(NVCC) $^ -o $@ $(GPU_ARCH) $(NVCC_FLAG) $(LIBS) $(OPT)

clean:
	rm -r $(BIN_FOLDER) $(OBJ_FOLDER)/*.o

clean_batch_outputs:
	rm -r $(BATCH_OUT_FOLDER)
