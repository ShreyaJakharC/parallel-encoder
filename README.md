# Parallel Encoder

## Objective

A command-line run-length encoder in C that concatenates one or more files and outputs a compressed binary stream to STDOUT. I learned and gained the skills to complete this project from my operating systems course.

Reinforce multithreaded-style design (Milestone 2), POSIX threading concepts, and core C skills—file I/O, mutex/condition synchronization, and data encoding—while building a high-performance RLE compressor.

## Tech Stack

- **Language:** C  
- **Build Tools:** GCC, Make 
- **Environment:** Linux shell  
- **APIs:** `fopen`, `fgetc`, `fwrite`, POSIX threads (`pthread_create`, `pthread_mutex`, `pthread_cond`)

## Features

- **Sequential & Parallel Modes**  
  - **Sequential**: Processes files end-to-end in a single thread.  
  - **Parallel**: (-j N) dispatches encoding tasks to a thread pool, merging results seamlessly.  
- **Run-Length Encoding (RLE)**  
  Stores each byte plus a 1-byte count, splitting runs at 255.  
- **File Concatenation**  
  Merges multiple inputs into one continuous RLE stream.  
- **Binary Inspection**  
  Compatible with `xxd` for verifying output.

## Key Takeaways

- **File I/O in C**  
  Utilized `fopen()`, `fgetc()`, and `fwrite()` for robust binary processing.

- **Run-Length Encoding**  
  Implemented efficient RLE with proper handling of 1-byte count overflow at 255.

- **Thread Pools & Synchronization**  
  Designed a worker pool using `pthread_mutex_t` and `pthread_cond_t` to parallelize tasks without race conditions.

- **Command-Line Tool Workflow**  
  Honed Linux shell skills, GCC builds, Makefiles, and `xxd`-based debugging.

## Usage

```bash
# Compile
gcc -o nyuenc nyuenc.c   # or: make

# Sequential encoding
./nyuenc file1.txt file2.txt > output.enc

# Parallel encoding with 4 workers
./nyuenc -j 4 file1.txt file2.txt > output.enc

# Inspect
xxd output.enc
