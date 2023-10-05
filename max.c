/*
    Universidad del Valle de Guatemala
    Computación Paralela y distribuida
    Corto#2

    Christopher García 20541
*/

// Se incluyen librerías
#include <mpi.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Se define el tamaño del array
#define SIZE 5000

int main(int argc, char** argv) {
    int rank, size;
    int* array;
    int max_value;

    // Se inicializa entorno MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Se crea array
    array = malloc(SIZE * sizeof(int));
    srand(time(NULL) + rank);

    // Se llena de valores aleatorios
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 100;
    }

    // Se realiza la búsqueda local del valor máximo en todo el array
    int local_max = array[0];
    for (int i = 1; i < SIZE; i++) {
        if (array[i] > local_max) {
            local_max = array[i];
        }
    }

    // Se utiliza MPI_Reduce para reducir todos los procesos a un único proceso para el total final 
    MPI_Reduce(&local_max, &max_value, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    // Se imprime el resultado
    if (rank == 0) {
        printf("Maximum value: %d\n", max_value);
    }

    // Se libera el array y se finaliza el entorno
    free(array);
    MPI_Finalize();

    return 0;
}
