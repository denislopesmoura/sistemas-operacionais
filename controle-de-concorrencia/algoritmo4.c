/******************************************************************************

Authors : Valter Negreiros / Sergio Melo

*******************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

bool ca = false;
bool cb = false;

int main() { 
  

    int processoA = fork();
    int processoB = fork();

    ca = true;
    
    while(ca){
        int randomTime = rand() %5 + 1;
        printf("Execução da Sessão Crítica do Processo A : %d \n" , processoA);
        sleep(randomTime);
        ca = false;
    }
    
    
   cb = true;
    
    while(cb){
        int randomTime = rand() %5 + 1;
        printf("Execução da Sessão Crítica do Processo B : %d \n" , processoB);
        sleep(randomTime);
        cb = false;
    }
    
    return 0;

}