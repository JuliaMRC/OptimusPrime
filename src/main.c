#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>

#include "../libs/queue/include/queue.h"

// Semente para random
#define RAND_SEED 0.0000005

// Controle de matriz
#define MATRIX_M 6
#define MATRIX_N 6
#define MATRIX_LENGTH MATRIX_M * MATRIX_N
#define QTD_ELEM 4
#define QTD_MB MATRIX_LENGTH / QTD_ELEM
int *matrix = NULL;

// Controle de threads
#define QTD_THREADS 4

// Pthreads
pthread_t tid[QTD_THREADS];
pthread_mutex_t mutex;
pthread_cond_t cond;
int status;

// Controle de contagem e acesso (Seção Crítica)
int primos = 0;
int ultimaPosicaoLinha = 0;
int ultimaPosicaoColuna = 0;
int mb_d = 0;
Queue *queue = NULL;

// Tempo de execucao
clock_t ticks[2];

// Definicoes de funcoes
void *percorreMacro(void *arg);
int verificaPrimo(int num);

void *percorreMacro(void *arg) {
    ticks[0] = clock();
    int localP = 0;
    int inc = sqrt(QTD_ELEM);

    pthread_mutex_lock(&mutex);

    int ll = ultimaPosicaoLinha;
    int lc = ultimaPosicaoColuna;

    if(ultimaPosicaoColuna == (MATRIX_M - QTD_ELEM)) {
        ultimaPosicaoLinha += inc;
        ultimaPosicaoColuna = 0;
    } else {
        ultimaPosicaoColuna += inc;
    }
    int *mp = matrix+(MATRIX_M * ll + lc);
    //int *mp = queue_pop(queue);
    pthread_mutex_unlock(&mutex);

    while(mb_d <= QTD_MB) { // Enquanto houver macroblocos
        // Percorre o macrobloco a partir do ponteiro recebido
        for(int i = 0; i < sqrt(QTD_ELEM); i++){ // Assume que o macrobloco sempre vai ser quadrado
            for(int j = 0; j < sqrt(QTD_ELEM); j++){
                int num = *(mp+(MATRIX_M * i + j));
                if(verificaPrimo(num) == 0){ // Verifica se o numero correspondente é primo
                    localP++;
                }
            }
        }

        pthread_mutex_lock(&mutex);
        mb_d++;
        ll = ultimaPosicaoLinha;
        lc = ultimaPosicaoColuna;

        if(ultimaPosicaoColuna == (MATRIX_M - QTD_ELEM)) {
            ultimaPosicaoLinha += inc;
            ultimaPosicaoColuna = 0;
        } else {
            ultimaPosicaoColuna += inc;
        }
        mp = matrix+(MATRIX_M * ll + lc);
        //int *mp = queue_pop(queue);
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_lock(&mutex);
    primos += localP;
    pthread_mutex_unlock(&mutex);

    ticks[1] = clock();
    printf("Tempo gasto para percorrer macrobloco: %g ms.\n", (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC);

    pthread_exit((void *)NULL);
}

int verificaPrimo(int num) {
    int resultado = 0;
    for(int i = 2; i <= num / 2; i++) {
        if (num % i == 0) {
            resultado++;
            break;
        }
    }
    return resultado;
}

int main() {

    // Inicia o srand com uma semente (cada semente diferente, gera numeros aleatorios diferentes)
    srand(RAND_SEED);

    // Inicia mutex e condicional
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    // Inicia fila
    queue = queue_new();

    // Inicia array de threads id
    //tid = (pthread_t) malloc(sizeof(pthread_t) * QTD_THREADS);

    ticks[0] = clock();
    // malloca linhas da coluna
    matrix = (int *)malloc(sizeof(int) * MATRIX_LENGTH); // malloca a matriz (sendo tratada com um vetor)
    ticks[1] = clock();
    printf("Tempo gasto para alocar: %g ms.\n", (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC);


    ticks[0] = clock();
    // Inicia valores aleatorios da matriz
    for(int i = 0; i < MATRIX_LENGTH; i++) {
        *(matrix+i) = i;//rand() % 29999;
    }
    ticks[1] = clock();
    printf("Tempo gasto para preencher: %g ms.\n", (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC);


    ticks[0] = clock();
    // Passa para a funcao o ponteiro de inicio de cada macrobloco e adiciona a queue (Fila)
    for(int i = 0; i < MATRIX_M; i += sqrt(QTD_ELEM)) {
        for(int j = 0; j < MATRIX_N; j += sqrt(QTD_ELEM)) {
            queue_push(queue, matrix+(MATRIX_M * i + j));
            //percorreMacro((void *)matrix+(MATRIX_M * i + j));
        }
    }
    ticks[1] = clock();
    printf("Tempo gasto para colocar na fila: %g ms.\n", (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC);


    //queue_print(queue);

    // Inicia threads
    for(int i = 0; i < QTD_THREADS; i++) {
        pthread_create(&(tid[i]), NULL, percorreMacro, (void *)NULL);
    }

    // Aguarda as threads
    for(int i = 0; i < QTD_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    printf("numeros primos: %d", primos);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    queue_destroy(queue);
    free(matrix);

    return 0;
}