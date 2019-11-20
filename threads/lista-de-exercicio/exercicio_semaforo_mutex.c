#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h> 
  
sem_t mutex; 

struct args {
    pid_t thread_id;
};
  
void* doSomething(void* arg) { 

    // wait 
    sem_wait(&mutex); 

    printf("\nEntered..\n"); 

    printf("\nThread ID: %d\n", ((struct args*)arg)->thread_id);
  
    // Sessão Crítica
    sleep(4); 
      
    // signal 
    printf("\nJust Exiting...\n"); 
    sem_post(&mutex); 
} 
  
  
int main()  { 

    // Inicialização da Estrutura do Semáforo não compartilhado entre processos e com valor inicial 1 : http://man7.org/linux/man-pages/man3/sem_init.3.html
    sem_init(&mutex, 0, 1); 


    // Inicialização das threads
    pthread_t t1,t2; 

    // Argumentos das Threads
    struct args *thread_1_args = (struct args *)malloc(sizeof(struct args));
    thread_1_args->thread_id = t1;

    struct args *thread_2_args = (struct args *)malloc(sizeof(struct args));
    thread_2_args->thread_id = t2;

    // Criação e Execução das threads
    pthread_create(&t1,NULL,doSomething, (void *)thread_1_args); 
    pthread_create(&t2,NULL,doSomething, (void *)thread_2_args); 
    pthread_join(t1,NULL); 
    pthread_join(t2,NULL); 

    // Destruindo estrutura do semáforo utilizado : https://pubs.opengroup.org/onlinepubs/007908799/xsh/sem_destroy.html
    sem_destroy(&mutex); 

    return 0; 
} 