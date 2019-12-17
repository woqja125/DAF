#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n = atoi(argv[3]);
	int a[400];
	iota(a, a + 400, 0);
	for(int i = 0; i < n; i++){
		random_shuffle(a, a + 400);
		for(int j = 0; j < 400; j++){
			printf("%d%c", a[j], " \n"[j == 399]);
		}
	}
	return 0;
}
