/**
 * Name:        problema-dos-filosofos.c
 * Description: Impletação do algoritmo para solução do problema dos filósofos
 * Equipe:      Denis Moura e Valter Negreiros
 * Data:        18-11-2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define numGarfos 4
#define numFilosofos 4

sem_t garfos[numGarfos];
sem_t lugares;
pthread_t filosofos[numFilosofos];
int index;

void* filosofo(int* args);

int main()
{

    //Inicializa estado dos 5 garfos 
    for(index = 0; index <= 4; index++)
        sem_init(&garfos[index], TRUE, 1);
    
    //seta a quantidade de lugares
    sem_init(&lugares, TRUE, 4);

    //cria 5 filósofos
    for(index = 0; index <= 4; index++)
    {
        pthread_create(&filosofos[index], NULL, (void*) filosofo, &index);
        pthread_join(filosofos[index],NULL);
    }
    
}

void* filosofo(int *args)
{
    int indexValue = *args;
    
    printf("Filósofo %d está pensando\n",indexValue);
    sleep(1);

    //senta na cadeira pra comer
    sem_wait(&lugares);
    
    //pega dois garfos para comer
    sem_wait(&garfos[indexValue]);
    sem_wait(&garfos[(indexValue + 1) % 5]);

    printf("Filósofo está comendo\n");
    sleep(3);

    //libera os dois garfos
    sem_post(&garfos[indexValue]);
    sem_post(&garfos[(indexValue + 1) % 5]);

    //levanta da caderia
    sem_post(&lugares);

    printf("Filosofo terminou de comer\n\n");
    sleep(1);

    pthread_exit(NULL);

}
