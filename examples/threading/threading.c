#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

 int status;


    struct thread_data* thread_func_args = (struct thread_data *) thread_param;


    sleep(thread_func_args->obtain_wait_time/1000);

    status = pthread_mutex_lock(thread_func_args->mutex);

    if (status != 0 ) {
        ERROR_LOG("Failed to obtain the mutex, error %d", status);
        thread_func_args->thread_complete_success = false;

    } else {


        sleep(thread_func_args->release_wait_time/1000);

        status = pthread_mutex_unlock(thread_func_args->mutex);

        if (status != 0) {

            ERROR_LOG("Cannot relase the mutex, error %d", status);

            thread_func_args->thread_complete_success = false;

        } else {

            DEBUG_LOG("Mutex was release.")

            thread_func_args->thread_complete_success = true;

        }
    }
    return thread_param;
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    int status = 0;
    struct thread_data* data = malloc(sizeof(struct thread_data));

    if (data != NULL) {

        data->obtain_wait_time = wait_to_obtain_ms;

        data->release_wait_time = wait_to_release_ms;

        data->mutex = mutex;

        status = pthread_create(thread, NULL, threadfunc, (void *)data);

        if(status != 0) {

            ERROR_LOG("Failed to create thread, error was %d", status);

            free(data); 

        } else {

            DEBUG_LOG("Thread created successfully!");

            return true;

        }
    } 
    else {

        ERROR_LOG("Not enough memory to create thread data.");
        // Do nothing
    }
    return false;
}

