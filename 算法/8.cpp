
#include<cstdio>
#include<cstring>
#define N 50

int n, k, M;
struct Matrix
{
	int f[N][N];
};
Matrix Add(Matrix U, Matrix V) //加
{
	Matrix S;
	memset(S.f, 0, sizeof(S.f));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			S.f[i][j] = (U.f[i][j] + V.f[i][j]) % M;
	return S;
}
Matrix Mul(Matrix U, Matrix V) //乘
{
	Matrix S;
	memset(S.f, 0, sizeof(S.f));
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				S.f[k][i] = (U.f[k][j] * V.f[j][i] + S.f[k][i]) % M;
	return S;
}
Matrix Pow(Matrix S, int k) //矩阵快速幂
{
	if (k == 0)
	{
		memset(S.f, 0, sizeof(S.f));
		for (int i = 0; i < n; i++)
			S.f[i][i] = 1;
		return S;
	}
	if (k == 1)
		return S;
	Matrix X = Pow(S, k / 2);
	if (k % 2)
		return Mul(Mul(X, X), S);
	else
		return Mul(X, X);
}
Matrix Cal(Matrix A, int k) //求解S(K)
{
	if (k == 1)
		return A;
	else
	{
		if (k % 2)
		{
			Matrix B = Add(A, Pow(A, (k + 1) / 2)); //S[7]=A+(A+A^4)*S(3);
			return Add(A, Mul(B, Cal(A, k / 2)));
		}
		else
		{
			Matrix B = Add(Pow(A, 0), Pow(A, k / 2)); //S[6]=(1+A^3)*S(3);
			return Mul(B, Cal(A, k / 2));
		}
	}
}
int main()
{
	while (scanf("%d%d%d", &n, &k, &M) == 3)
	{
		Matrix A;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &A.f[i][j]);
		Matrix S = Cal(A, k);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n - 1; j++)
				printf("%d ", S.f[i][j]);
			printf("%d\n", S.f[i][n - 1]);
		}
	}
	return 0;
}
