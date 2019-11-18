/**
 * Name:        barbeiro-dorminhoco.c
 * Description: Impletação do algoritmo para solução do problema do barbeiro dorminhoco
 * Authors:      Denis Moura e Valter Negreiros
 * Data:        18-11-2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define numCadeiras  5
#define numClientes 10

sem_t clientes;
sem_t barbeiros;
sem_t mutex;

int espera = 0;

void* barbeiro(void *args);
void* cliente(void *args);

int main()
{

    //inicializa variáveis
    sem_init(&clientes, 1, 0);
    sem_init(&barbeiros,1, 0);
    sem_init(&mutex,    1, 1);
    
    pthread_t tBarbeiro, tCliente;

    //cria um barbeiro
    pthread_create(&tBarbeiro, NULL, (void*) barbeiro, NULL);

    //cria vários clientes
    for(int count = 0; count <= numCadeiras; count++)
    {
        pthread_create(&tCliente, NULL, (void*) cliente, NULL);
        sleep(1);
    }

    //espera até que o barbeiro atenda todos os clientes
    //pthread_join(tBarbeiro, NULL);

    return 0;
}

void* barbeiro(void* args)
{
    while(1)
    {
        sem_wait(&clientes);
        sem_wait(&mutex);
    
        espera = espera - 1;
    
        sem_post(&barbeiros);
        sem_post(&clientes);
    
        //região crítica
        printf("barbeiro está cortando cabelo do cliente\n");
    }

    pthread_exit(NULL);
}

void* cliente(void* args)
{
    sem_wait(&mutex);
    
    if(espera < numCadeiras)
    {
        printf("Cliente chegou na barbearia\n");
        espera = espera + 1;
        sem_post(&clientes);
        sem_post(&mutex);
        sem_wait(&barbeiros);
        printf("Cliente deseja cortar o cabelo\n");
    }
    else
    {
        sem_post(&mutex);
        printf("Barbearia está cheia. Cliente foi embora.\n");
    }
    
    pthread_exit(NULL);
}
