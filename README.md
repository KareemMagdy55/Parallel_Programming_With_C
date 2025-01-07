# Parallel Programming with C

## Description

This repository contains a collection of C programs and examples that demonstrate various techniques in parallel programming. It covers multiple parallel programming models and libraries, providing practical examples to help you understand and implement parallelism in C.

## Contents

- **Pthreads Examples:** Utilize POSIX threads for multithreading in C programs.
- **OpenMP Examples:** Implement shared-memory parallelism using OpenMP directives.
- **MPI Programs:** Explore distributed computing with the Message Passing Interface.
- **Synchronization Mechanisms:** Learn about mutexes, semaphores, and barriers.
- **Parallel Algorithms:** Study and implement algorithms optimized for parallel execution.

## Features

- **Hands-On Examples:** Each section contains ready-to-run code samples.
- **Step-by-Step Tutorials:** Guides to help you set up your environment and understand the code.
- **Performance Analysis:** Insight into the benefits and challenges of parallel programming.
- **Modular Code Structure:** Easily navigate and understand each example.

## Getting Started

### Prerequisites

- **C Compiler:** GCC or any C compiler that supports parallel programming libraries.
- **Parallel Libraries:**
  - **Pthreads:** Usually included with standard C libraries.
  - **OpenMP:** Support typically included with modern compilers.
  - **MPI:** Install an MPI implementation like MPICH or OpenMPI.

### Clone the Repository

```bash
git clone https://github.com/KareemMagdy55/Parallel_Programming_With_C.git
cd Parallel_Programming_With_C
```

### Building and Running Examples

Navigate to the desired example directory and follow the instructions provided in the README or comments within the code files.

#### Example: Running an OpenMP Program

1. **Navigate to the OpenMP example:**

   ```bash
   cd OpenMP/MatrixMultiplication
   ```

2. **Compile the program:**

   ```bash
   gcc -fopenmp -o matrix_mul matrix_mul.c
   ```

3. **Run the executable:**

   ```bash
   ./matrix_mul
   ```

## Contributing

Contributions are welcome! If you have examples, bug fixes, or enhancements, please fork the repository and submit a pull request.

## License

This project is licensed under the MIT License.

## Contact

For questions or suggestions, feel free to reach out to [KareemMagdy55](https://github.com/KareemMagdy55).

---

Feel free to explore the repository to enhance your understanding of parallel programming in C. Whether you're a beginner or looking to deepen your knowledge, these examples provide a practical approach to learning parallelism.
