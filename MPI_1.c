#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define MASTER_RANK 0

int main(int argc, char** argv)
{
    int rank, size;
    int nVoters, nCandidates;
    int* pref_list;
    int* banned ;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == MASTER_RANK)
    {
        FILE* fptr = fopen("in.txt", "r");
        fscanf(fptr, "%d %d", &nCandidates, &nVoters);

        banned = (int*)malloc((nCandidates + 1) * sizeof(int*));
        pref_list = (int*)malloc((nVoters * nCandidates) * sizeof(int*));
        for (int i = 0; i < nVoters * nCandidates; i++)
            fscanf(fptr, "%d", &pref_list[i]);
        for (int i = 0; i <= nCandidates; ++i)
             banned[i] = 0 ;

        fclose(fptr);
    }


    MPI_Bcast(&nVoters, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);
    MPI_Bcast(&nCandidates, 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);

    const int range = nVoters / size;
    const int rem = nVoters % size;

    int counts[size];
    int displacements[size];

    for (int i = 0; i < size; i++)
    {
        counts[i] = (i == 0 ? rem + range : range);
        displacements[i] = (i == 0 ? 0 : displacements[i - 1] + counts[i - 1]);

        counts[i] *= nCandidates;
    }

    int local_pref_list[counts[rank]];

    // MPI_Bcast(banned, nCandidates + 1, MPI_INT, MASTER_RANK, MPI_COMM_WORLD);
    MPI_Scatterv(pref_list, counts, displacements, MPI_INT,
                 local_pref_list, counts[rank], MPI_INT,
                 MASTER_RANK, MPI_COMM_WORLD);

    printf("Process NO.%d \n", rank);
    printf("DISP : %d\n  ", displacements[rank]);
    printf("COUNT : %d\n ", counts[rank]);
    int tmp[counts[rank] / nCandidates][nCandidates];
    int l = 0 ;
    int r = 0;
    for (int i = 0 ; i < counts[rank] ; i ++)
    {
        if (r == nCandidates) l ++ ;
        r %= nCandidates;

        tmp[l][r] = local_pref_list[i];
        r ++ ;

    }
    // MPI_Allgather(MPI_IN_PLACE, 0, MPI_DATATYPE_NULL, banned, 1, MPI_INT, MPI_COMM_WORLD);






    for (int i = 0; i < counts[rank] / nCandidates; i++)
    {
        for (int j = 0; j < nCandidates; ++j)
        {
            printf("%d, ", tmp[i][j]);
        }
        printf("\n");
    }
    // for (int i = 0 ; i < nCandidates + 1;  i ++)
    //     printf("banned %d, ", banned[i]);
    // printf("\n");

    printf("\n------------------------------------------------\n");

    MPI_Finalize();
    return 0;
}
