#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <map>
#include <ctype.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
int main()
{
	map<string, string> g;
	char str[30], s1[15], s2[15];
	while (gets_s(str) && strcmp(str, "") != 0)
	{
		sscanf(str, "%s %s", s1, s2);
		g[s2] = s1;
	}//键值对对应
	while (gets_s(s2))
	{
		if (g.count(s2) == 0)
			printf("eh\n");
		else
			cout << g[s2] << endl;
	}
	return 0;
}