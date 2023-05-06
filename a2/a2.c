#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "a2_helper.h"
/*
void *thread_f(void* arg)
{
    info(BEGIN, 2, 1);

    info(END, 2, 1);

    info(BEGIN, 2, 2);

    info(BEGIN, 2, 3);

    info(END, 2, 3);

    info(END, 2, 2);

    info(BEGIN, 2, 4);

    info(END, 2, 4);

    info(BEGIN, 2, 5);

    info(END, 2, 5);

    info(BEGIN, 2, 6);

    info(END, 2, 6);

    return NULL;
}

void *thread_func(void* arg)
{
    for(int i = 5; i <= 37; i++)
    {
        if(i != 14)
        {
            info(BEGIN, 3, i);

            info(END, 3, i);
        }
    }

    info(BEGIN, 3, 1);

    info(BEGIN, 3, 2);

    info(BEGIN, 3, 3);

    info(BEGIN, 3, 4);

    info(BEGIN, 3, 14);

    info(END, 3, 14);

    info(END, 3, 4);

    info(END, 3, 3);

    info(END, 3, 2);

    info(END, 3, 1);

    return NULL;
}

void *thread_function(void* arg)
{
    info(BEGIN, 4, 1);

    info(END, 4, 1);

    info(BEGIN, 4, 4);

    info(BEGIN, 4, 2);

    info(END, 4, 2);

    info(END, 4, 4);

    info(BEGIN, 4, 3);

    info(END, 4, 3);

    info(BEGIN, 4, 5);

    info(END, 4, 5);

    return NULL;
}
*/

sem_t semafor1, semafor2;
sem_t *sem1, *sem2;

void* thread_2(void* arg)
{
    int id2 = *(int *)arg;

    if(id2 == 2)
    {
        info(BEGIN, 2, id2);
    
        info(END, 2, id2);
        sem_post(sem1);
    }
    else if(id2 == 1)
    {
        sem_wait(sem2);
        info(BEGIN, 2, id2);
        
        info(END, 2, id2);
    }
    else
    {
        info(BEGIN, 2, id2);
        
        info(END, 2, id2);
    }
    return NULL;
}

void* thread_3(void* arg)
{
    int id3 = *(int *)arg;

    info(BEGIN, 3, id3);
    
    info(END, 3, id3);

    return NULL;
}

void* thread_4(void* arg)
{
    int id4 = *(int *)arg;
    
    if(id4 == 3)
    {
        sem_wait(sem1);
        info(BEGIN, 4, id4);
        
        info(END, 4, id4);
        sem_post(sem2);
    }
    else if(id4 == 4)
    {
        info(BEGIN, 4, id4);
        sem_post(&semafor1);
        
        sem_wait(&semafor2);
        info(END, 4, id4);
    }
    else if(id4 == 2)
    {
        sem_wait(&semafor1);
        info(BEGIN, 4, id4);
        
        info(END, 4, id4);
        sem_post(&semafor2);
    }
    else
    {
        info(BEGIN, 4, id4);

        info(END, 4, id4);
    }
    return NULL;
}

int main(){
    init();
    
    info(BEGIN, 1, 0);
    
    pid_t p3 = fork();
    
    if(p3 == 0)
    {
        info(BEGIN, 3, 0);
        
        pthread_t t3[37];
        int res3[37];
        for(int i = 0; i < 37; i++)
        {
            res3[i] = i + 1;
            if(pthread_create(&t3[i], NULL, thread_3, &res3[i]) != 0)
            {
                return -1;
            }
        }
        
        for(int i = 0; i < 37; i++)
        {
            pthread_join(t3[i], NULL);
        }
        
        info(END, 3, 0);
        exit(4);
    }
    else waitpid(p3, NULL, 0);
    
    pid_t p6 = fork();
    
    if(p6 == 0)
    {
        info(BEGIN, 6, 0);
        
        info(END, 6, 0);
        exit(4);
    }
    else waitpid(p6, NULL, 0);
    
    pid_t p7 = fork();
    
    if(p7 == 0)
    {
        info(BEGIN, 7, 0);
        
        info(END, 7, 0);
        exit(4);
    }
    else waitpid(p7, NULL, 0);
    
        sem1 = sem_open("sem1", O_CREAT, 0644, 0); 

        sem2 = sem_open("sem2", O_CREAT, 0644, 0); 
    
    pid_t p2 = -1, p4 = -1, p5 = -1;
    p2 = fork();
    if(p2 == 0)
    {
        info(BEGIN, 2, 0);
        
        p5 = fork();
        
        if(p5 == 0)
        {
            info(BEGIN, 5, 0);
        
            info(END, 5, 0);
            exit(4);
        }
        else 
        {
            waitpid(p5, NULL, 0);
        
            p4 = fork();
            
            if(p4 == 0)
            {
                info(BEGIN, 4, 0);
            
                pthread_t t2[6], t4[5];
                int res2[6], res4[5];
        
                sem1 = sem_open("sem1", 0); 
                    sem2 = sem_open("sem2", 0); 
        
                for(int i = 0; i < 6; i++)
                {
                    res2[i] = i + 1;
                    if(pthread_create(&t2[i], NULL, thread_2, &res2[i]) != 0)
                    {
                        return -1;
                    }
                }
        
                for(int i = 0; i < 5; i++)
                {
                    res4[i] = i + 1;
                    if(pthread_create(&t4[i], NULL, thread_4, &res4[i]) != 0)
                    {
                        return -1;
                    }
                }
        
                for(int i = 0; i < 5; i++)
                {
                    pthread_join(t4[i], NULL);
                }
            
            
                for(int i = 0; i < 6; i++)
                {
                    pthread_join(t2[i], NULL);
                }
                    
                    info(END, 4, 0);
                    exit(4);
                }
                else
                {
                waitpid(p4, NULL, 0);
        
                info(END, 2, 0);
                exit(4);
            }
        }
    }
    else waitpid(p2, NULL, 0);
    
    sem_close(sem1);
        sem_close(sem2);
    
    info(END, 1, 0);
    exit(4);

    return 0;
}
        

    
