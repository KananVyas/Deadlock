 #include <stdio.h>
 #include <pthread.h>
 #include <time.h>
 #include <semaphore.h>

 #define MAX_SLEEP 10
 #define MAX_THREADS 2

 pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
sem_t flag,flag1;

 void *callback1 (void *arg) {
     int random_time;

int value=0,value1=0;
     while (1) { 
         srand(time(NULL));
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleeping for %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);


  sem_post(&flag);
sem_getvalue(&flag,&value);

             //flag = 1;
          printf("\nflag: %d",value);
         printf("[%s]Trying to acquire mutex1 (holding none)\n", __FUNCTION__);
         pthread_mutex_lock(&mutex1);
         printf("[%s]Acquired mutex1\n", __FUNCTION__);
         
 sem_wait(&flag);

         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleeping for %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);



 sem_post(&flag1);
sem_getvalue(&flag1,&value1);
             //flag1 = 1;
         printf("\nflag1: %d",value1);
         printf("[%s]Trying to acquire mutex2 (holding mutex1) \n", __FUNCTION__);
         pthread_mutex_lock(&mutex2);
         printf("[%s]Acquired mutex2\n\n", __FUNCTION__);

sem_wait(&flag1); 
         pthread_mutex_unlock(&mutex2);
        //sem_wait(&flag1); 

        // printf("\nflag1: %d",flag1);

         pthread_mutex_unlock(&mutex1);
        //flag = 0;
//sem_wait(&flag1); 

         //printf("\nflag: %d",flag);
     }
     return NULL;
 }

 void *callback2 (void *arg) {
     int random_time;

     while (1) { 
         srand(time(NULL));
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleeping for %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);



sem_post(&flag1);
sem_getvalue(&flag1,&value1);
            // flag1 = 1;
   printf("\nflag1: %d",value1);
         printf("[%s]Trying to acquire mutex2 (holding none)\n", __FUNCTION__);
         pthread_mutex_lock(&mutex2);
         printf("[%s]Acquired mutex2\n", __FUNCTION__);

sem_wait(&flag1); 
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleeping for %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);
sem_post(&flag);
             //flag =1;
  // printf("\nflag: %d",flag);
         printf("[%s]Trying to acquire mutex1 (holding mutex2) \n", __FUNCTION__);
         pthread_mutex_lock(&mutex1);
         printf("[%s]Acquired mutex1\n\n", __FUNCTION__);
sem_wait(&flag); 
     random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleeping for %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);
         pthread_mutex_unlock(&mutex1);
          //flag = 0;
//sem_wait(&flag); 

   //printf("\nflag: %d",flag);
       pthread_mutex_unlock(&mutex2);
          //flag1 = 0;
//sem_wait(&flag1); 

  // printf("\nflag1: %d",flag1);
     }
     return NULL;
 }

 int main () {
     pthread_t thread[MAX_THREADS];
     int status, i;

   int res = sem_init(&flag,  /* pointer to semaphore */
                       0 ,                  /* 0 if shared between threads, 1 if shared between processes */
                      0);                  /* initial value for semaphore (0 is locked) */
    if (res < 0)
    {
        perror("Semaphore initialization failed");
        exit(0);
    }
    if (sem_init(&flag1, 0, 0)) /* initially unlocked */
    {
        perror("Semaphore initialization failed");
        exit(0);
    }

     status = pthread_create(&thread[0], NULL, callback1, NULL);
     if (status != 0) {
         fprintf(stderr, "pthread_create failed [status: %d]\n", status);
         return -1;
     }

     status = pthread_create(&thread[1], NULL, callback2, NULL);
     if (status != 0) {
         fprintf(stderr, "pthread_create failed [status: %d]\n", status);
         return -1;
     }

     for (i=0; i < MAX_THREADS; i++) { 
         status = pthread_join(thread[i], NULL);
         if (status != 0) {
             fprintf(stderr, "pthread_join failed for thread1 [%d]\n", status);
             return -1;
         }
     } 
     return 0;
 }


