#!/bin/bash

#SBATCH --partition=gsp2306
#SBATCH --tasks=1
#SBATCH --cpus-per-task=1
#SBATCH --gres=gpu:1
#SBATCH --nodes=1

#SBATCH --job-name=GPU-subisomorphism
#SBATCH --output=out/iso-%x.%j.out
#SBATCH --error=out/iso-%x.%j.err

ml CUDA/12.1
mkdir -p bin
srun ./bin/GPU-subisomorphism
