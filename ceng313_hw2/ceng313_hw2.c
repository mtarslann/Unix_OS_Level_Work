//Mustafa Talha Arslan 250201067 - OS HW2 - Fall 2017

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

pthread_t tid[6];
char *filenames[3];

pthread_mutex_t r1Lock1;
pthread_mutex_t r1Lock2;
pthread_mutex_t r2Lock;

typedef int bool;
#define true 1
#define false 0

bool isR1_1Empty = false, isR1_2Empty = false;

//Cut and Paste
void *threadWorkA(void *arg) {

    int threadID = (int*) arg;
    srand(time(NULL));
    int num = 1 + rand() % 10;
    int myR1;
    while(1){
//      Thread tries to lock resources
        for (; ;) {
            if (isR1_1Empty == true && isR1_2Empty == true) break;
            pthread_mutex_lock(&r2Lock);

            if(pthread_mutex_trylock(&r1Lock1)==0 && isR1_1Empty == false) {
                myR1 = 0;
                break;
            }
            else if(pthread_mutex_trylock(&r1Lock2)==0 && isR1_2Empty == false) {
                myR1 = 1;
                break;
            }

            pthread_mutex_unlock(&r2Lock);

        }
//      Finish the execution if both numbers1.txt and numbers2.txt is empty
        if (isR1_1Empty == true && isR1_2Empty == true) break;

        FILE *file1, *temp, *file2;
        file1 = fopen ( filenames[myR1], "r+" );
        temp = fopen("replicaA.txt","w+");
        file2 = fopen(filenames[2],"a");
        // Cutting and Pasting work
        if ( file1 != NULL  )
        {
            int i = 0;
            char line [10];
            while ( fgets ( line, sizeof line, file1 ) != NULL) {

                if(i<num) {
                    fputs(line, file2);
                }
                else{
                    fputs(line, temp);
                }

                i++;
            }
            // Check if the file is empty or not
            rewind(temp);
            if( fgets(line, sizeof line, temp) == NULL) {
                switch(myR1) {
                    case 0:
                        isR1_1Empty = true;
                        break;
                    case 1:
                        isR1_2Empty = true;
                        break;
                }
            }

            fclose(file1);
            fclose(temp);
            fclose(file2);

            remove(filenames[myR1]);
            rename("replicaA.txt",filenames[myR1]);
        }
        else
        {
            perror ( filenames[myR1] );
        }

//      Thread releases resources
        switch(myR1) {
            case 0:
                pthread_mutex_unlock(&r1Lock1);
                break;
            case 1:
                pthread_mutex_unlock(&r1Lock2);
                break;
        }
        pthread_mutex_unlock(&r2Lock);

    }

}

int primeNumberCheck(int n){
    int  i;

    for(i=2; i<=n/2; ++i)
    {
        if(n%i==0)
        {
            // return 0 if the number is not prime
            return 0;
        }
    }
    // return 1 if the number is prime
    return 1;
}

//Remove Prime Numbers
void *threadWorkB(void *arg){
    int myR;
    while(1) {
//      Thread-B tries to lock resource
        for (; ;) {
            if (isR1_1Empty == true && isR1_2Empty == true) break;

            if(pthread_mutex_trylock(&r1Lock1)==0 && isR1_1Empty == false) {
                myR = 0;
                break;
            }
            else if(pthread_mutex_trylock(&r1Lock2)==0 && isR1_2Empty == false) {
                myR = 1;
                break;
            }
            else if(pthread_mutex_trylock(&r2Lock)==0) {
                myR = 2;
                break;
            }

        }
//      Finish the execution if both numbers1.txt and numbers2.txt is empty
        if (isR1_1Empty == true && isR1_2Empty == true) break;

        FILE *file1, *temp;
        file1 = fopen ( filenames[myR], "r+" );
        temp = fopen("replicaB.txt","w+");

        // Removing prime numbers
        if ( file1 != NULL )
        {
            int i = 0;
            char line [10];
            while ( fgets ( line, sizeof line, file1 ) != NULL)
            {

                if(atoi(line) <= 0) {
                    fputs(line, temp);
                }
                else if (primeNumberCheck(atoi(line)) == 0){
                    fputs(line, temp);
                }
                i++;
            }
            // Check if the file is empty or not
            rewind(temp);
            if( fgets(line, sizeof line, temp) == NULL) {
                switch(myR) {
                    case 0:
                        isR1_1Empty = true;
                        break;
                    case 1:
                        isR1_2Empty = true;
                        break;
                    default:
                        break;
                }
            }

            fclose(file1);
            fclose(temp);

            remove(filenames[myR]);
            rename("replicaB.txt",filenames[myR]);
        }
        else
        {
            perror ( filenames[myR] );
        }
//      Thread-B releases resource
        switch(myR) {
            case 0:
                pthread_mutex_unlock(&r1Lock1);
                break;
            case 1:
                pthread_mutex_unlock(&r1Lock2);
                break;
            case 2:
                pthread_mutex_unlock(&r2Lock);
                break;
        }

    }

}

//Remove Negative Numbers
void *threadWorkC(void *arg){
    int myR;
    while(1) {
//      Thread-C tries to lock resource
        for (; ;) {
            if (isR1_1Empty == true && isR1_2Empty == true) break;

            if(pthread_mutex_trylock(&r1Lock1)==0 && isR1_1Empty == false) {
                myR = 0;
                break;
            }
            else if(pthread_mutex_trylock(&r1Lock2)==0 && isR1_2Empty == false) {
                myR = 1;
                break;
            }
            else if(pthread_mutex_trylock(&r2Lock)==0) {
                myR = 2;
                break;
            }

        }
//      Finish the execution if both numbers1.txt and numbers2.txt is empty
        if (isR1_1Empty == true && isR1_2Empty == true) break;

        FILE *file1, *temp;
        file1 = fopen ( filenames[myR], "r+" );
        temp = fopen("replicaC.txt","w+");
        // Removing negative numbers
        if ( file1 != NULL  )
        {
            int i = 0;
            char line [10];
            while ( fgets ( line, sizeof line, file1 ) != NULL)
            {

                if(atoi(line) >= 0) {
                    fputs(line, temp);
                }
                i++;
            }
            // Check if the file is empty or not
            rewind(temp);
            if( fgets(line, sizeof line, temp) == NULL) {
                switch(myR) {
                    case 0:
                        isR1_1Empty = true;
                        break;
                    case 1:
                        isR1_2Empty = true;
                        break;
                    default:
                        break;
                }
            }

            fclose(file1);
            fclose(temp);

            remove(filenames[myR]);
            rename("replicaC.txt",filenames[myR]);
        }
        else
        {
            perror ( filenames[myR] );
        }
//      Thread-C releases resource
        switch(myR) {
            case 0:
                pthread_mutex_unlock(&r1Lock1);
                break;
            case 1:
                pthread_mutex_unlock(&r1Lock2);
                break;
            case 2:
                pthread_mutex_unlock(&r2Lock);
                break;
        }

    }
}



int main ( void )
{
    filenames[0] = "numbers1.txt";
    filenames[1] = "numbers2.txt";
    filenames[2] = "resource_type_2.txt";

//  creating mutexes
    if ((pthread_mutex_init(&r1Lock1, NULL) != 0) || (pthread_mutex_init(&r1Lock2, NULL) != 0)
        || (pthread_mutex_init(&r2Lock, NULL) != 0))
    {
        printf("\n mutex init has failed\n");
        return 1;
    }

    int i=0;
    int threadCount = 5;

//  creating threads
    while(i<4){
        pthread_create(&(tid[i]), NULL, &threadWorkA, i);
        printf("Thread A%d created\n",i);
        i++;
    }
    pthread_create(&(tid[4]), NULL, &threadWorkB, 4);
    printf("Thread B created\n");
    pthread_create(&(tid[5]), NULL, &threadWorkC, 5);
    printf("Thread C created\n");

    for(i=0; i<threadCount; i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&r1Lock1);
    pthread_mutex_destroy(&r1Lock2);
    pthread_mutex_destroy(&r2Lock);
    printf("I'm done with these files, send new ones ;D \n");
    return 0;
}