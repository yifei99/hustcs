#include <stdio.h>
#include<string.h>
#define N 110
char b[N];
int a[N];
int top;
int p, q, r, s, t;
bool cal(){
	int len = strlen(b);
	top = 0;
	for (int i = len - 1; i >= 0; i--)
	{
		if (b[i] == 'p') a[top++] = p;
		else  if (b[i] == 'q') a[top++] = q;
		else  if (b[i] == 'r') a[top++] = r;
		else  if (b[i] == 's') a[top++] = s;
		else  if (b[i] == 't') a[top++] = t;
		else if (b[i] == 'K')
		{
			int w = a[--top];
			int e = a[--top];
			a[top++] = (w&&e);
		}
		else if (b[i] == 'A')
		{
			int w = a[--top];
			int e = a[--top];
			a[top++] = (w || e);
		}
		else if (b[i] == 'N')
		{
			int w = a[--top];
			a[top++] = (!w);
		}
		else if (b[i] == 'C')
		{
			int w = a[--top];
			int e = a[--top];
			a[top++] = (!w) || e;
		}
		else if (b[i] == 'E')
		{
			int w = a[--top];
			int e = a[--top];
			if (w == e) a[top++] = 1;
			else a[top++] = 0;
		}
	}
	if (!a[0]) return false;
	else return true;
}
bool judge(){
	for (p = 0; p <= 1; p++)
		for (q = 0; q <= 1; q++)
			for (r = 0; r <= 1; r++)
				for (s = 0; s <= 1; s++)
					for (t = 0; t <= 1; t++)
					{
						if (!cal()) return false;
					}

	return true;
}//总共32种情况枚举
int main(){
	while (~scanf_s("%s", b))
	{
		if (strcmp(b, "0") == 0)
			break;
		if (judge())
			printf("tautology\n");
		else printf("not\n");
	}
	return 0;
}