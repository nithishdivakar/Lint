#include<pthread.h>
#include<iostream>
#include"shorts.h"
#include<mutex>

using namespace std;
mutex mtx;
typedef struct args_t{
	int id;
	int thing;
} Args;

void *dostuff( void * ptr){
	Args *A = (Args*) ptr;
	int j=5;
	while(j--){
		mtx.lock();
		cout<<j<<" Thread "<<A->id<<endl;
		mtx.unlock();
	}
	pthread_exit(NULL);
}



int main(){
	pthread_t T[5];
	Args A[5];

	FOR(i,0,5){
		A[i].id = i;
		A[i].thing = 245;
		int rc = pthread_create(&T[i], NULL, dostuff, (void *)&A[i]);
	}
	
	FOR(i,0,5){
		void * status;
		pthread_join(T[i],&status);
	}

	pthread_exit(NULL);
	return 0;
}
