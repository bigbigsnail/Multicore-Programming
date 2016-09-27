# Multicore-Programming

## Programming Assignment 1
Implement n-thread mutual exclusion using:
 - Tournament Algorithm
 - Test-And-Set Instruction
 - Test-Test-And-Set Instruction
 
 Programs for each method contains two public functions: 
- lock()
- unlock()
 
## How to run the programs
### Compile the programs
The program is based on C++ 11 library, tested under gcc 4.9.3 and Apple LLVM clang.
	- Using GCC to compile:
			 
        g++ -std=c++11 <MyProgram>.cpp -o <output_name> -lpthread -lrt 
	 
  - Using macOS with Apple LLVM:
			  
        clang++ -std=c++11 -stdlib=libc++ <MyProgram>.cpp -o <output_name> -lpthread

### Run

The programs take a input number as the number of threads you want to use.
To run these programs, run the output file after compiling step, using command:
			
      $<Program_path>/<output_name> <num_of_threads>

&emsp;&emsp;For example:

&emsp;For the program Tournament Algorithm, compile command is:
			
      g++ -std=c++11 Tournament.cpp -o TournamentLock -lpthread -lrt

To run the program, first go into the directory where the ‘TournamentLock’ is, then using following command. The number stands for the number of threads.

      ./TournamentLock 4 

### On TACC machine
 On TACC machine, we can use bash file to run program with command:
			
      sbatch <myscript>.sh
      
- Tournament_run.sh is used to run Tournament Algorithm program
- TAS_run.sh is used to run Test-And-Set Program
- TTAS_run.sh is used to run Test-Test-And-Set Program



