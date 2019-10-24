/**
 * Name:        threads.c
 * Description: código base para criação de threads na linguagem c
 * Author:      Denis Moura
 * Data:        13-10-2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/** Define o numero de threads do sistema*/
#define NUM_THREADS 4

/** Função que executa as Threads*/
void *excuteThread(void * args);

int main(void){

    pthread_t threads [NUM_THREADS];
    int i, args [NUM_THREADS];

    for(i = 0; i < NUM_THREADS ;i++){

        args[i] = i++;

        /** Cria uma nova thread e define a função que irá executá-la*/
        pthread_create(&threads [i], NULL, excuteThread, (void *)&args[i]);

    }
    
    for(i = 0; i < NUM_THREADS ;i++){

        /** Aguarda até que a Thread seja encerrada*/
        pthread_join(threads [i],NULL);
    
    }

    return 0;
    
}

void *excuteThread(void * args){

    int *pvalor;
    pvalor = args;

    printf("Executando a Thread %i...\n", *pvalor);
    printf("Finalizando a Thread %i...\n", *pvalor);
}