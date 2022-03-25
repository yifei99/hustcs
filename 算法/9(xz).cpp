#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
string a[300];
string add(string a, string b)
{
	if (a.length() < b.length())
		swap(a, b);
	int i, j, up = 0, temp;
	for (i = a.length() - 1, j = b.length() - 1; i >= 0; i--, j--)
	{
		a[i] = a[i] + (j >= 0 ? b[j] - '0' : 0) + up;
		temp = (a[i] - '0') % 10;
		up = (a[i] - '0' - temp) / 10;
		a[i] = temp + '0';
		if (i == 0 && up != 0) a = "1" + a;//防止最高位进一无法储存；
	}
	return a;
}
int main()
{
	int n;
	a[0] = "1", a[1] = "1";
	for (int i = 2; i <= 250; ++i)
		a[i] = add(add(a[i - 2], a[i - 1]), a[i - 2]);//递推，f(n)=f(n-1)+2f(n-2)；
	while (cin >> n)
		cout << a[n] << endl;
	return 0;
}