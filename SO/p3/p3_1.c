#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_MODELS 5

int camisetas[NUM_MODELS];  // Shared buffer representing the stock of camisetas
sem_t semaphores[NUM_MODELS];  // Semaphores for each model

// Function declarations
void *cliente(void *arg);
void *proveedor(void *arg);

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Usage: %s <num_clientes> <num_proveedores>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_clientes = atoi(argv[1]);
    int num_proveedores = atoi(argv[2]);

    // Initialize the buffer with random initial stock values
    srand(time(NULL));
    for (int i = 0; i < NUM_MODELS; i++) {
        camisetas[i] = rand() % 100 + 1;  // Random stock between 1 and 100
        sem_init(&semaphores[i], 0, 1);  // Initialize semaphores with initial value 1
    }

    // Print the initial stock
    printf("Initial Stock:\n");
    for (int i = 0; i < NUM_MODELS; i++) {
        printf("Model %d: %d\n", i, camisetas[i]);
    }

    // Create threads for clientes
    pthread_t clientes[num_clientes];
    for (int i = 0; i < num_clientes; i++) {
        pthread_create(&clientes[i], NULL, cliente, NULL);
    }

    // Create threads for proveedores
    pthread_t proveedores[num_proveedores];
    for (int i = 0; i < num_proveedores; i++) {
        pthread_create(&proveedores[i], NULL, proveedor, NULL);
    }

    // Wait for clientes to finish
    for (int i = 0; i < num_clientes; i++) {
        pthread_join(clientes[i], NULL);
    }

    // Wait for proveedores to finish
    for (int i = 0; i < num_proveedores; i++) {
        pthread_join(proveedores[i], NULL);
    }

    // Print the final stock
    printf("Final Stock:\n");
    for (int i = 0; i < NUM_MODELS; i++) {
        printf("Model %d: %d\n", i, camisetas[i]);
    }

    // Destroy semaphores
    for (int i = 0; i < NUM_MODELS; i++) {
        sem_destroy(&semaphores[i]);
    }

    return 0;
}

void *cliente(void *arg) {
    while (1) {
        // Simulate a purchase
        int model = rand() % NUM_MODELS;
        int quantity = rand() % 10 + 1;  // Random quantity between 1 and 10

        sem_wait(&semaphores[model]);  // Wait for access to the model
        if (quantity > camisetas[model]) {
            // If the client wants more than available, only provide what's left
            quantity = camisetas[model];
        }
        camisetas[model] -= quantity;
        sem_post(&semaphores[model]);  // Release access to the model

        // Print the purchase
        printf("Cliente: Compra de %d camisetas del modelo %d\n", quantity, model);

      // Sleep to simulate some time passing between purchases
    }

    return NULL;
}

void *proveedor(void *arg) {
    while (1) {
        // Simulate a supply
        int model = rand() % NUM_MODELS;
        int quantity = rand() % 10 + 1;  // Random quantity between 1 and 10

        sem_wait(&semaphores[model]);  // Wait for access to the model
        camisetas[model] += quantity;
        sem_post(&semaphores[model]);  // Release access to the model

        // Print the supply
        printf("Proveedor: Suministro de %d camisetas al modelo %d\n", quantity, model);

        sleep(2);  // Sleep to simulate some time passing between supplies
    }

    return NULL;
}
