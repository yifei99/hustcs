
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "stdio.h"
#include <string.h>

extern "C" long _cdecl FUNC1();
extern "C" long _cdecl FUNC2();
extern "C" long _cdecl FUNC3();
extern "C" long _cdecl FUNC4();
extern "C" long _cdecl FUNC5();
int op=1;
int main(int argc, char *argv[]) {
	char password[10];
	char username[11];
	int vb;
	printf("Are you Boos or Vistor?(1/0)\n");
	scanf("%d", &vb);
	if (vb == 0) {
		for(;;){
			system("cls");     printf("\n\n");
			printf(" Hello Vistor,  Welcome to FEISHOP! \n");
			printf("-------------------------------------------------\n");
			printf("    	  1.Query product information\n");
			printf("    	  6. Exit\n");
			printf("-------------------------------------------------\n");
			printf("    Tell me what you choose[0~6]:");
			scanf("%d", &op);
			if (op == 1) {
				FUNC1();
				getchar(); getchar();
			}
			if(op==6)
					break;
			}
		return 0;
	}
	else if (vb == 1) {
	L1:
		printf("Print username:");
		scanf("%s", username);
		if (strcmp("LIANGYIFEI", username) == 0) {
		L2:
			printf("Print password:");
			scanf("%s", password);
			if (strcmp("991026", password) == 0) {
				for (;;) {
					system("cls");     printf("\n\n");
					printf(" Hello Boss,  Welcome to FEISHOP! \n");
					printf("-------------------------------------------------\n");
					printf("    	  1.Query product information\n");
					printf("    	  2.Modify product information\n");
					printf("    	  3.Calculate the recommendation \n");
					printf("    	  4.Recommendation ranking\n");
					printf("    	  5.All product information\n");
					printf("    	  6.Exit\n");
					printf("-------------------------------------------------\n");
					printf("    Tell me what you choose[0~6]:");
					scanf("%d", &op);

					if (op == 1) {
						FUNC1();
						getchar(); getchar();
					}
					if (op == 2) {
						FUNC2();
						getchar(); getchar();
					}
					if (op == 3) {
						FUNC3();
						getchar(); getchar();
					}
					if (op == 4) {
						FUNC4();
						getchar(); getchar();
					}
					if (op == 5) {
						FUNC5();
						getchar(); getchar();
					}
					if (op == 6)
						break;
				}
			}
			else {
				printf("Mismatch,Try again\n");
				goto L2;
			} 
		}
		else {
			printf("Mismatch,Try again\n");
			goto L1;
		}
		}
	return 0;
	}