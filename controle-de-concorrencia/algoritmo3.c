/**
 * Name:        algoritmo3.c
 * Description: Implementação do algoritmo 3 para exclusão multua apresentado no capítulo 7 
 *              do livro "Arquitetura de Sistemas Operacionais" - Luis Paulo Maia              
 * Author:      Denis Moura
 * Data:        13-10-2019
 **/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int lockA = 0;
int lockB = 0;

int main(void){

void *executaA(void *);
void *executaB(void *);

    
    pthread_t tA, tB;
    
    pthread_create(&tA,NULL,executaA,NULL);
    
    pthread_create(&tB,NULL,executaB,NULL);
    
    pthread_join(tA, NULL);
    pthread_join(tB, NULL);

    return EXIT_SUCCESS;
    

}

void *executaA(void *args){
    
    while(1){
        
        printf("Iniciando execução do PA\n");
        
        lockA = 1;
        
        while(lockB == 1){
            
            printf("Preso em B\n");
            //sleep(1);
            //return()
        }
        
        printf("Processando região critica de PA\n");
        
        sleep(1);
        
        lockA = 0;
        
        printf("Processando A\n");
        
    }
    
}

void *executaB (void *args){
    
    while(1){
        
        printf("Iniciando execução da Thread B\n");
        
        lockB = 1;
        
        while(lockA == 1){
            
            printf("Esperando a execução da Thread A\n");
            //sleep(1);
            //return(0);
            
        }
        
        printf("Entrando na região critica de PB\n");
        sleep(1);
        
        lockB = 0;
        
        printf("Processando B...\n");
        
    }
    
}