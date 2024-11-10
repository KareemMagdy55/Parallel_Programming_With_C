#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define square(x) ((x)* (x))


int getRandomSeed()
{
    srand(time(NULL));
    return rand();
}

int main()
{
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int *arr = malloc(size * sizeof(int));

    int sum = 0 ;
    double mean = 0 ;
    double variance = 0 ;



    // First parallel part : generate n random numbers
#pragma omp parallel for
    for (int i = 0 ; i < size ; i ++)
    {
        int seed = getRandomSeed() * (i + 1) + omp_get_thread_num();
        srand(seed);
        arr[i] = rand() ;
    }


    // Second parallel part : calculate mean
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
    }

    mean = sum / size;

    // Third parallel part : calculate variance
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
    {
        variance += square(arr[i] - mean) ;
    }

    variance /= size ;
    printf("{");
    for (int i = 0; i < size; ++i)
    {
        printf("%d, ", arr[i]);
    }
    printf("}\n");

    printf("Mean of elements above is %f\n", mean);
    printf("Variance of elements above is %f\n", variance);
    printf("Standard deviation of elemnts above is %f\n", sqrt(variance));
    return 0;
}