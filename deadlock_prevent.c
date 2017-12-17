 #include <stdio.h>
 #include <pthread.h>
 #include <time.h>
 #include <semaphore.h>

 #define MAX_SLEEP 10
 #define MAX_THREADS 2

 pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
 pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
  sem_t flag,flag1;   //Intialization for semaphore variable
  int value=1,value1=1;
  
//Function for thread1
 void *thread1 (void *arg) {
     int random_time;



     while (1) {
       
	//Random sleeping time
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleep time: %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);

//storing semaphore value in integer
sem_getvalue(&flag,&value);
printf("\n before loop flag: %d\n",value);
if(value==1)
{
             
              sem_wait(&flag);//Implementation of P function
          printf("\nflag: %d\n",value);
         printf("[%s]Trying to acquire r1 (holding none)\n", __FUNCTION__);
         pthread_mutex_lock(&mutex1);
         printf("[%s]:Acquired r1\n", __FUNCTION__);

}

         //Random sleeping time
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleep time: %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);

//storing semaphore value in integer
sem_getvalue(&flag1,&value1);
if(value1==1)
{
            sem_wait(&flag1);
         printf("\nflag1: %d\n",value1);
         printf("[%s]Trying to acquire r2 (holding r1) \n", __FUNCTION__);
         pthread_mutex_lock(&mutex2);
         printf("[%s]:Acquired r2\n\n", __FUNCTION__);
}
sem_getvalue(&flag1,&value1);
if(value1==0)
{
         pthread_mutex_unlock(&mutex2);
          sem_post(&flag1); //Implementation of V function of semaphore
}
         printf("\nflag1: %d\n",value1);
sem_getvalue(&flag,&value);
if(value==0)
{
         pthread_mutex_unlock(&mutex1);
         sem_post(&flag); //Implementation of V function of semaphore
}
         printf("\nflag: %d\n",value);
     }
     return NULL;
 }

//Function for thread2
 void *thread2 (void *arg) {
     int random_time;

     while (1) {
        
         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleep time: %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);
  sem_getvalue(&flag1,&value1);
 printf("\nflag1 before loop: %d\n",value1);
if(value1==1)
{
              sem_wait(&flag1);
   printf("\nflag1: %d\n",value1);
         printf("[%s]Trying to acquire r2 (holding none)\n", __FUNCTION__);
         pthread_mutex_lock(&mutex2);
         printf("[%s] :Acquired r2\n", __FUNCTION__);
}

         random_time = rand() % MAX_SLEEP;
         printf("[%s]Sleep time: %d seconds\n", __FUNCTION__, random_time);
         sleep(random_time);
sem_getvalue(&flag,&value);
if(value==1)
{
            sem_wait(&flag);
   printf("\nflag: %d\n",value);
         printf("[%s]Trying to acquire r1 (holding r2) \n", __FUNCTION__);
         pthread_mutex_lock(&mutex1);
         printf("[%s]Acquired r1\n\n", __FUNCTION__);
}
sem_getvalue(&flag,&value);
if(value==0)
{
         pthread_mutex_unlock(&mutex1);
         sem_post(&flag);
}
   printf("\nflag: %d\n",value);
sem_getvalue(&flag1,&value1);
if(value1==0)
{
         pthread_mutex_unlock(&mutex2);
          sem_post(&flag1);
}
   printf("\nflag1: %d\n",value1);
     }
     return NULL;
 }

 int main () {
     pthread_t thread[MAX_THREADS];
     int status, i;

 int res = sem_init(&flag,1,1);
    if (res < 0)
    {
        perror("Semaphore initialization failed");
        exit(0);
    }
    if (sem_init(&flag1, 1, 1) < 0) 
    {
        perror("Semaphore initialization failed");
        exit(0);
    }




     status = pthread_create(&thread[0], NULL, thread1, NULL);
     if (status != 0) {
         fprintf(stderr, "pthread_create failed [status: %d]\n", status);
         return -1;
     }

     status = pthread_create(&thread[1], NULL, thread2, NULL);
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
         sem_destroy(&flag);
         sem_destroy(&flag1);
     }
     return 0;
 }
