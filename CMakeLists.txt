cmake_minimum_required(VERSION 3.26)
project(Project1 C)

# Specify the path to GCC-13 (replace with your actual path)

set(CMAKE_C_STANDARD 11)
find_package(MPI REQUIRED)
include_directories(/Microsoft SDKs/MPI/Include)
add_executable(p0 MPI_0.c)
add_executable(p1 MPI_1.c)
add_executable(p2 MPI_2.c)
add_executable(p3 MPI_3.c)
add_executable(omp2 open_mpi_1.c)
target_link_libraries(p0 PUBLIC MPI::MPI_C)
target_link_libraries(p1 PUBLIC MPI::MPI_C)
target_link_libraries(p2 PUBLIC MPI::MPI_C)
target_link_libraries(p3 PUBLIC MPI::MPI_C)

# Find OpenMP package
find_package(OpenMP REQUIRED)

add_executable(Project1 open_mpi_0.c)

# Enable OpenMP support
if (OpenMP_C_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    target_link_libraries(Project1 PRIVATE ${OpenMP_C_LIBRARIES})
endif ()