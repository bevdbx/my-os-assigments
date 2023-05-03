#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include "a2_helper.h"

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

int main(){

    init();

    info(BEGIN, 1, 0);
    
    pid_t p2 = fork();
    //pid_t p4 = 0;

    if(p2 == 0)
    {
        info(BEGIN, 2, 0);
        
        

        pid_t p4 = fork();

        if(p4 == 0)
        {
            info(BEGIN, 4, 0);
            
            pthread_t t4 = -1;
            if(pthread_create(&t4, NULL, thread_function, NULL) != 0)
            {
                return -1;
            }
            pthread_join(t4,NULL);
            info(END, 4, 0);
            exit(4);
        }
        else waitpid(p4,NULL,0);

        pid_t p5 = fork();

        if(p5 == 0)
        {
            info(BEGIN, 5, 0);
            
            info(END, 5, 0);
            exit(4);
        }
        else waitpid(p5,NULL,0);

        pthread_t t2 = -1;
        if(pthread_create(&t2, NULL, thread_f, NULL) != 0)
        {
            return -1;
        }
        pthread_join(t2,NULL);

        info(END, 2, 0);
        exit(4);
    }
    else waitpid(p2,NULL,0);

    pid_t p3 = fork();

    if(p3 == 0)
    {
        info(BEGIN, 3, 0);
        
        pthread_t t3 = -1;
        if(pthread_create(&t3, NULL, thread_func, NULL) != 0)
        {
            return -1;
        }
        pthread_join(t3,NULL);

        info(END, 3, 0);
        exit(4);
    }
    else waitpid(p3,NULL,0);

    pid_t p6 = fork();

    if(p6 == 0)
    {
        info(BEGIN, 6, 0);
        
        info(END, 6, 0);
        exit(4);
    }
    else waitpid(p6,NULL,0);

    pid_t p7 = fork();
        
    if(p7 == 0)
    {
        info(BEGIN, 7, 0);
              
        info(END, 7, 0);
        exit(4);
    } 
    else waitpid(p7,NULL,0);

    info(END, 1, 0);
    exit(4);
    return 0;
}