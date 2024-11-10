#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv) {
    int size, rank;
    int d, b;
    int a = 1, c = 2;
    int result;
    const int root = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    //Prepare local data
    // localdata = rank;
    // printf("[Process %d]: has local data %d\n", rank, localdata);

    //MPI_Reduce(sendbuf, recvbuf, count, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
    if (rank == 0)
    {
        MPI_Reduce(&c, &d, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
        MPI_Reduce(&a, &b, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    }else if (rank == 1)
    {
        MPI_Reduce(&c, &d, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
        MPI_Reduce(&a, &b, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
    }else if (rank == 2)
    {
        MPI_Reduce(&a, &b, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
        MPI_Reduce(&c, &d, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

    }

    if (rank == 0) {
        printf("b : %d, d : %d\n", b, d);
        printf("\n");
    }

    MPI_Finalize();
    return 0;
}