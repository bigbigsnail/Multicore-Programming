# Multicore-Programming

## Programming Assignment 4
Implement matrix multiplication with CUDA. Two matrices are each of size N x N. Compute the resultant matrix so that each element is computed by a seperated thread.

## How to run the programs
### Compile the programs
The program is based on c and CUDA programming. We test & run the program on TACC Stampede machine.
	- Command for compiling:
			 
        nvcc -o matrix_mul CUDA.cu

### Run

To run these programs, run the output file after compiling step, using command:
			
      $<Program_path>/<output_name> <num_of_threads>

To run the program, first go into the directory where the ‘TournamentLock’ is, then using following command. The number stands for the number of threads.

      ./matrix_mul




