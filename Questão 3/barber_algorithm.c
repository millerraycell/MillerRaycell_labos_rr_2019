#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define CADEIRAS 8

int clientes_esperando = 0;

sem_t barber;
sem_t customer;
sem_t mutex;

void cut_hair()
{
    printf("Barbeiro esta cortando o cabelo\n");
    for(int i=0; i< 0xFFFFFFFF; i++);;
}

void customer_arrived()
{
    printf("Cliente chegou para cortar cabelo\n");
}
void get_haircut()
{
    printf("Cliente esta tendo o cabelo cortado\n");
}

void giveup_haircut()
{
    printf("Cliente desistiu, salao cheio\n");
}

void *cliente()
{
    sem_wait(&mutex);
    if(clientes_esperando < CADEIRAS)
    {
        customer_arrived();
        clientes_esperando++;
        sem_post(&customer);
        sem_post(&mutex);
        sem_wait(&barber);
        get_haircut();
    }
    else
    {
        sem_post(&mutex);
        customer_arrived();
        giveup_haircut();
    }
    pthread_exit(NULL);
}

void *barbeiro()
{
    while(1)
    {
        sem_wait(&customer);
        sem_wait(&mutex);
        clientes_esperando--;
        sem_post(&barber);
        sem_post(&mutex);
        cut_hair();
    }
    pthread_exit(NULL);
}

int main()
{
    sem_init(&customer,1,0);
    sem_init(&barber,1,0);
    sem_init(&mutex,1,1);


    pthread_t barb,clien;

    pthread_create(&barb,NULL,barbeiro,NULL);

    while(1)
    {
        pthread_create(&clien,NULL,cliente,NULL);
        printf("Numero de pessoas na fila de espera: %d\n",clientes_esperando);
        for(int i=0; i< 0xFFFFFF; i++);
    }

    return 0;
}

