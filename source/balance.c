#include "balance.h"
void initialize(int p){
	srand(time(NULL));
	if((p<1 || p>99) && ( p != -1)){
		printf("initialize(p) : p is %d! exit!\n", p);
		exit(1);
	}
	while(1){
		int bad_count = 0;
		FILE * fp = fopen("bad.txt", "r");
		if(p == -1 && fp){
			for(int i=0; i<100; i++)
				__coin[i] = CORRECT;
			char buffer[1024];
			fgets(buffer, sizeof(buffer), fp);
			fclose(fp);
			char *s = strtok(buffer, " ");
			while(s != NULL){
				__coin[atoi(s)] = BAD;
				bad_count++;
				s = strtok(NULL, " ");
			}
		}
		else{
			for(int i=0; i<100; i++){
				if(((double)rand()/RAND_MAX)*100 < p) {
					__coin[i] = BAD;
					bad_count++;
				}
				else __coin[i] = CORRECT;
			}
		}
		if(bad_count == 100 || bad_count == 0){
			printf("initialize errer!, reinitializing!");
		}
		else{
			printf("Number of bad coins : %d\n", bad_count);
			printf("Indexes of bad coins : ");
			for(int i=0; i<100; i++) if(__coin[i] == BAD) printf("%d, ", i);
			printf("\n");
			return;
		}
	}
}
int balance(int a[], int b[]){
	call_count++;
	printf("*%d 회차 호출\n", call_count);
	int ai, bi;

	{
		//duplication search
		int coinindex1[100] = {0, };
		ai = 0; bi = 0;
		while(a[ai] != -1){
			coinindex1[a[ai]]++;
			ai++;
		}
		while(b[bi] != -1){
			coinindex1[b[bi]]++;
			bi++;
		}
		for(int i=0; i<100; i++) if(coinindex1[i] > 1){ printf("duplication error!\n"); return ERROR;}
	}

	//try
	if(b[0] == -1){
		int coinindex2[100] = {0, };
		ai = 0;
		for(int i=0; i<100; i++) if(__coin[i] == BAD) coinindex2[i]++;
		while(a[ai] != -1){
			coinindex2[a[ai]]--;
			ai++;
		}
		for(int i=0; i<100; i++) if(coinindex2[i] != 0){printf("Ah... It's incorrect.\n"); return ERROR;}
		printf("SUCCESS!\n");
		return SUCCESS;
	}

	//balance
	ai = 0; bi = 0;
	int left_weight = 0;
	int right_weight = 0;
	while(a[ai] != -1) left_weight += __coin[a[ai++]];
	while(b[bi] != -1) right_weight += __coin[b[bi++]];
	if(left_weight < right_weight){ printf("SMALL\n"); return SMALL;}
	else if(left_weight > right_weight){ printf("LARGE\n"); return LARGE;}
	else if(left_weight == right_weight){ printf("EQUAL\n"); return EQUAL;}
	else return ERROR;
}
