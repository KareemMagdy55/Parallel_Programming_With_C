#include <io.h>
#include <stdio.h>
#include <mpi.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MASTER_RANK 0
#define MAX_FILES 100
#define MAX_FILENAME_LENGTH 1000


void free2DArray(int **array, int rows) {
    // Free memory for each row
    for (int i = 0; i < rows; i++) {
        free(array[i]);
    }
    // Free memory for the array itself
    free(array);
}
void fillwRandomNumber(FILE* file){

    for (int i = 0; i < 100; ++i){

        const int randomNumber = rand() % 100 + 1;
        const int numberLength = 40 ;

        char randNumber[numberLength] ;
        sprintf(randNumber, "%d\n", randomNumber);
        fprintf(file, randNumber);

    }
}
void mkfile(const char* dirname, const char *filename) {
    char filepath[500];
    snprintf(filepath, sizeof(filepath), "%s/%s", dirname, filename);

    FILE *file = fopen(filepath, "w");
    fillwRandomNumber(file);

    fclose(file);
}
int search(const char* dirname, const char* filename, const int x){
    char filepath[500];
    snprintf(filepath, sizeof(filepath), "%s/%s", dirname, filename);

    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    int counter = 0 ;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (atoi(buffer) == x)
        {
            counter ++  ;
        }
    }

    fclose(file);
    return counter ;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int rank, size, x;
    char dirname[MAX_FILENAME_LENGTH];
    char sendfilenames[MAX_FILES][MAX_FILENAME_LENGTH];
    char recvfilenames[MAX_FILES][MAX_FILENAME_LENGTH];


    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    if (size < 2) {
        printf("This program requires at least 2 processes\n");
        MPI_Finalize();
        return 1;
    }

    if (rank == MASTER_RANK) {

        printf("Please input directory name : ");
        fflush(stdout);
        scanf("%s", dirname);

        printf("Please input a number to find its occurrences: ");
        fflush(stdout);
        scanf("%d", &x);

        int range = MAX_FILES / size;

        mkdir(dirname);

        for (int i = 0; i < MAX_FILES; ++i){
            char filename[MAX_FILENAME_LENGTH] = "file";
            sprintf(filename, "%s%d.txt",filename,  i);

            strcpy(sendfilenames[i], filename);
            mkfile(dirname, filename);
        }
    }

    MPI_Bcast(dirname, MAX_FILENAME_LENGTH, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int counts[size];
    int displacements[size];

    int range = MAX_FILES / size ;
    int rem = MAX_FILES % size;

    for (int i = 0; i < size; i++) {

        counts[i] = (i == 0) ? (range + rem) : range;
        displacements[i] = (i == 0) ? 0 : (displacements[i - 1] + counts[i - 1]);

        counts[i] *= MAX_FILENAME_LENGTH;
    }

     MPI_Scatterv(sendfilenames, counts, displacements, MPI_CHAR,
                 recvfilenames, MAX_FILENAME_LENGTH * MAX_FILES, MPI_CHAR,
                 0, MPI_COMM_WORLD);

    int local_cnt = 0 ;
    int total_cnt = 0 ;

    for(int i = 0  ;i < counts[rank] / MAX_FILENAME_LENGTH; i++ ){
        local_cnt += search(dirname, recvfilenames[i], x);
    }

    printf("P%d : Total number of occurrences = %d\n", rank, local_cnt);
    MPI_Reduce(&local_cnt, &total_cnt, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == MASTER_RANK){
        printf("Total number of occurrences in all %d files = %d\n", MAX_FILES, total_cnt);
    }

    MPI_Finalize();
    return 0;
}
