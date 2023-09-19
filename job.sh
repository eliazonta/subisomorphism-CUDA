#!/bin/bash

#SBATCH --partition=edu5
#SBATCH --tasks=1
#SBATCH --cpus-per-task=1
#SBATCH --gres=gpu:1
#SBATCH --nodes=1

#SBATCH --job-name=GPU-isomorphism
#SBATCH --output=out/iso-%x.%j.out
#SBATCH --error=out/iso-%x.%j.err

module load cuda/12.1
srun ./bin/name
