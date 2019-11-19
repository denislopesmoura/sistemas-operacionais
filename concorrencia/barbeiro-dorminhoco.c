/**
 * Name:        barbeiro-dorminhoco.c
 * Description: Impletação do algoritmo para solução do problema do barbeiro dorminhoco
 * Authors:      Denis Moura e Valter Negreiros
 * Data:        18-11-2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define numCadeiras 5
#define TRUE 1

sem_t clientes;
sem_t barbeiros;
sem_t mutex;

int espera = 0;

void* barbeiro(void* args);
void* cliente(void* args);

int main()
{
    //inicialização das variáveis
    sem_init(&clientes, TRUE, 0);
    sem_init(&barbeiros, TRUE, 0);
    sem_init(&mutex, TRUE, 1);

    pthread_t tBarbeiro, tCliente;

    pthread_create(&tBarbeiro, NULL, (void*) barbeiro, NULL);

    while(TRUE)
    {
        pthread_create(&tCliente, NULL, (void*) cliente, NULL);
        sleep(1);
    }

    return 0;
}   

void* barbeiro(void* args)
{
    while(TRUE)
    {
        sem_wait(&clientes);
        sem_wait(&mutex);

        espera = espera--;

        sem_post(&barbeiros);
        sem_post(&mutex);
        
        printf("Cortando cabelo do cliente\n");
        sleep(3);
    }

    pthread_exit(NULL);

}

void* cliente(void* args)
{
    printf("Cliente chegou na barbearia\n");
    sleep(1);

    sem_wait(&mutex);

    if(espera < numCadeiras)
    {
        espera = espera++;
        sem_post(&clientes);
        sem_post(&mutex);
        sem_wait(&barbeiros);

        printf("Cliente cortou o cabelo!\n");
    }else{
        sem_post(&mutex);
        printf("Barbearia está cheia. Cliente foi embora\n");
    }

    pthread_exit(NULL);
}
