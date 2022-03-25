#include<stdio.h>
#define N 65536
#define Ni 50000
#define res 42768
int map[N];
int a[Ni];
int b[Ni];
int i;
int j;
int k;

bool hash(int *a, int *b){
	int f;
	int temp1;
	int temp2;
	for (f = 0; f < i; f++) {
		temp1 = a[f]+32768;
		map[temp1] = 1;
	}//将a中出现的数在map中标记为1
	for (f = 0; f < j; f++) {
		temp1 = b[f];
		temp2 = res - temp1;
		if (map[temp2] == 1)
			return true;
	}
	return false;
};//查询res-b中的数在map中是否有标记
int main() {
	for (i = 0; i < N; i++) {
		map[i] = 0;
	};
	scanf_s("%d", &i);
	for (k = 0; k < i; k++) {
		scanf_s("%d", a+k);
	};
	scanf_s("%d", &j);
	for (k = 0; k < j; k++) {
		scanf_s("%d", b+k);
	};
	if (hash(a, b))
		printf("YES");
	else
		printf("NO");
	return 0;
}
