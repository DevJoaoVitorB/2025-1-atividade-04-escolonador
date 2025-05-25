#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <math.h>

// Thread CPU-bound (cálculos intensivos)
void* cpu_thread(void* arg) {
    printf("Thread CPU-bound %ld iniciada (PID: %d)\n", (long)arg, getpid());

    // Cálculo de π (método de Leibniz)
    double pi = 0;
    int sign = 1;
    for(int i = 0; i < 100000000; i++) {
        pi += sign * (4.0 / (2*i + 1));
        sign *= -1;
    }
    printf("Thread CPU-bound %ld terminou (π aproximado: %f)\n", (long)arg, pi);
    return NULL;
}

// Thread I/O-bound (simula espera)
void* io_thread(void* arg) {
    printf("Thread I/O-bound %ld iniciada (PID: %d)\n", (long)arg, getpid());
    sleep(2);  // Simula operação I/O
    printf("Thread I/O-bound %ld terminou\n", (long)arg);
    return NULL;
}

int main() {
    pid_t pid;
    pthread_t thread_cpu1, thread_cpu2, thread_cpu3, thread_io1, thread_io2, thread_io3;

    // Cria processo filho
    pid = fork();

    if (pid == 0) { // Processo filho
        printf("\nProcesso filho (PID: %d)\n", getpid());
        
        // Cria threads CPU-bound
        pthread_create(&thread_cpu1, NULL, cpu_thread, (void*)1);
        pthread_create(&thread_cpu2, NULL, cpu_thread, (void*)2);
        pthread_create(&thread_cpu3, NULL, cpu_thread, (void*)3);
        
        // Cria threads I/O-bound
        pthread_create(&thread_io1, NULL, io_thread, (void*)1);
        pthread_create(&thread_io2, NULL, io_thread, (void*)2);
        pthread_create(&thread_io3, NULL, io_thread, (void*)3);
        
        // Espera todas as threads terminarem
        pthread_join(thread_cpu1, NULL);
        pthread_join(thread_cpu2, NULL);
        pthread_join(thread_cpu3, NULL);
        pthread_join(thread_io1, NULL);
        pthread_join(thread_io2, NULL);
        pthread_join(thread_io3, NULL);
        
    } else if (pid > 0) { // Processo pai
        printf("Processo pai (PID: %d)\n", getpid());
        wait(NULL); // Espera filho terminar
    }

    return 0;
}