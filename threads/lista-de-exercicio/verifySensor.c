/**
 * Name:        verifySensor
 * Description: Monitora 4 sensores utilizando multthreads
 * Author:      Denis Moura
 * Data:        13-10-2019
 **/ 

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/** Define o numero de threads disponíveis pra uso*/
#define NUM_THREADS 4

/** Função que executa as Threads*/
void *monitorSensor(void *args);

int main(void){

    pthread_t threads [NUM_THREADS];
    int i, args [NUM_THREADS];

    for(i = 0; i < NUM_THREADS; i++){

        args[i] = i++;
        pthread_create(&threads[i], NULL, monitorSensor, (void *)&args[i]);

    }
    
    for(i = 0; i < NUM_THREADS ;i++){

        pthread_join(threads[i],NULL);
        
    }

    exit(NULL);
}

void *monitorSensor(void * args){
    
    int pvalor = (int)(*args);

    printf("Iniciando a thread %i - Monitorando sensor %i...\n", *pvalor,*pvalor+1 );

    switch (pvalor){
        case 0:
            printf("Verificando sensor 1");
            break;
        case 1:
            printf("Verificando sensor 2");
            break;
        case 2:
            printf("Verificando sensor 3");
            break;
        case 3:
            printf("Verificando sensor 4");
            break;
        default:
            break;
    }

}