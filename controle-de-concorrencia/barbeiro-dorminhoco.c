/**
 * Name:        barbeiro-dorminhoco.c
 * Description: Impletação do algoritmo para solução do problema do barbeiro dorminhoco
 * Authors:     Denis Moura e Valter Negreiros
 * Data:        19-11-2019
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

    //Cria um único barbeiro
    pthread_create(&tBarbeiro, NULL, (void*) barbeiro, NULL);

    //Cria clientes indefinidamente
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
        //verifica se há clientes
        sem_wait(&clientes);
        //tem acesso a lista de espera
        sem_wait(&mutex);

        // atende um cliente
        espera = espera--;

        //barbeiro disponível
        sem_post(&barbeiros);
        //libera a lista de espera
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

    //entra na região crítica
    sem_wait(&mutex);

    if(espera < numCadeiras)
    {   
        //entra na fila de espera
        espera = espera++;
        //sinaliza se há clientes para o barbeiro atender
        sem_post(&clientes);
        //libera lista de espera
        sem_post(&mutex);
        //Aloca o barbeiro
        sem_wait(&barbeiros);

        printf("Cliente cortou o cabelo!\n");
    }else{
        
        //acessa região crítica
        sem_post(&mutex);

        printf("Barbearia está cheia. Cliente foi embora\n");
    }

    pthread_exit(NULL);
}
