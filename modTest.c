#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

// max number of values for each thread to sort
#define MAX_VALS_PER_THREAD 1000
// max threads allowed
#define MAX_N_SIZE 100

int custom_mod(int dividend, int divisor) {
    // Ensure divisor is positive
    if (divisor < 0)
        divisor = -divisor;

    // Initialize remainder to the dividend
    int remainder = dividend;

    // Subtract divisor from remainder until it becomes smaller than divisor
    while (remainder >= divisor)
        remainder -= divisor;

    // Return the remainder
    return remainder;
}

void* thread_dispatch1(int* rere){
	clock_t start, end;
	long long total = 0;
	int op = 100000;
	
	start = clock();
	for(int i = 0; i < op; i++){
		//total += i % 17;
		total += custom_mod(i, 16);
	}
	end = clock();
	printf("Reg total: %lld\n", total);
	double time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Regular modulo took: %f seconds for %d operations\n", time, op);
	return (void*) 0;
}

void* thread_dispatch2(int* rere){
	clock_t start, end;
	long long total = 0;
	int op = 100000;
	
	start = clock();
	for(int i = 0; i < op; i++){
		total += (i) & 15;
	}
	end = clock();
	
	printf("& total: %lld\n", total);
	double time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("& modulo took: %f seconds for %d operations\n", time, op);
	return (void*) 0;
}

int isPowerOfTwo(int val){
	int temp = 1;
	while(temp <= val){
		if(temp == val){
			return 1;
		}
		temp = temp * 2;
	}
	return 0;
}

int multiply_mod(int dividend, int divisor) {
    // Ensure divisor is positive
    if (divisor < 0)
        divisor = -divisor;

    // Bitwise division
    int quotient = dividend / divisor;

    // Bitwise multiplication
    int product = quotient * divisor;

    // Bitwise subtraction
    int remainder = dividend - product;

    // Return the remainder
    return remainder;
}

void* thread_dispatch3(int* rerere){
	clock_t start, end;
	long long total = 0;
	int op = 100000;
	
	start = clock();
	for(int i = 0; i < op; i++){
		total += multiply_mod(i, 16);
	}
	end = clock();
	
	printf("multiply total: %lld\n", total);
	double time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("multiply modulo took: %f seconds for %d operations\n", time, op);
	return (void*) 0;
}

void* evenTestDefault(int* uh){
  clock_t start, end;
	long long total = 0;
	int op = 100000;
	
	start = clock();
	for(int i = 10000; i < 10000 + op; i++){
		total += multiply_mod(i, 2);
	}
	end = clock();
	
	printf("multiply total: %lld\n", total);
	double time = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("Default isEven took: %f seconds for %d operations\n", time, op);
	return (void*) 0;
}

void* evenTestAND(int* ehrjehrje){
  clock_t start, end;
	long long total = 0;
	int op = 100000;
	
	start = clock();
	for(int i = 10000; i < 10000 + op; i++){
		total += (i) & 1;
	}
	end = clock();
	
	printf("& total: %lld\n", total);
	double time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("& isEven took: %f seconds for %d operations\n", time, op);
	return (void*) 0;
}

int main(int argc, char** argv) { 
  pthread_t tid[5];
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  int o1 = 0;
  int o2 = 1;
  int o3 = 2;
  int o4 = 3;
  int o5 = 4;
  
  pthread_create(&tid[0], &attr, thread_dispatch1, &o1);
  pthread_create(&tid[1], &attr, thread_dispatch2, &o2);
  pthread_create(&tid[2], &attr, thread_dispatch3, &o3);

  sleep(1);

  pthread_create(&tid[3], &attr, evenTestDefault, &o4);
  pthread_create(&tid[4], &attr, evenTestAND, &o5);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_join(tid[2], NULL);
  pthread_join(tid[3], NULL);
  pthread_join(tid[4], NULL);

  exit(0);

}
