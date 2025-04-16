/**
 * Author: Dr. Ing. P. Yuhala
 * Postdoc
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * Integer array sizes as num. of elements in xMB
 */
#define NUM_INTS_ONE_MB (1 << 18)
#define NUM_INTS_FOUR_MB (1 << 20)

#define MAX_NUM UINT32_MAX
#define MIN_NUM 100
#define CPU_FREQ_GHZ 3.00

/**
 * Forward declarations
 */
uint64_t read_tsc();
void vector_add(uint32_t *A, uint32_t *B, uint32_t len);
double get_time_millis(uint64_t cycles);

typedef struct
{
    uint64_t start;
    uint64_t stop;
    uint64_t cycles_elapsed;

} Timer;

// Timer functions
void start_clock(Timer *timer);
void stop_clock(Timer *timer);

void vector_add(uint32_t *A, uint32_t *B, uint32_t len)
{
    for (int i = 0; i < len; i++)
    {
        A[i] = (A[i] + B[i]) % MAX_NUM;
    }
}

void start_clock(Timer *timer)
{
    timer->start = read_tsc();
}

void stop_clock(Timer *timer)
{
    timer->stop = read_tsc();
    timer->cycles_elapsed = timer->stop - timer->start;
}

double get_time_millis(uint64_t cycles)
{
    return cycles / (CPU_FREQ_GHZ * 1e6);
}

uint64_t read_tsc()
{
    unsigned int hi, lo;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

int main()
{
    Timer add_timer;
    uint32_t *A = (uint32_t *)malloc(NUM_INTS_FOUR_MB * sizeof(uint32_t));
    uint32_t *B = (uint32_t *)malloc(NUM_INTS_FOUR_MB * sizeof(uint32_t));

    for (int i = 0; i < NUM_INTS_FOUR_MB; i++)
    {
        A[i] = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
        B[i] = (rand() % (MAX_NUM - MIN_NUM + 1)) + MIN_NUM;
    }

    start_clock(&add_timer);
    vector_add(A, B, NUM_INTS_FOUR_MB);
    stop_clock(&add_timer);

    double time_elapsed = get_time_millis(add_timer.cycles_elapsed);

    printf("Cycles elapsed: %llu\n", (unsigned long long)add_timer.cycles_elapsed);
    printf("Time elapsed milliseconds: %.3f\n", time_elapsed);

    free(A);
    free(B);

    return 0;
}
