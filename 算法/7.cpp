#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const double MAX = 1e50;
int n;
double ab(double x)
{
	return x > 0 ? x : -x;
}
struct node
{
	double x, y;
	bool bel;//用于分组
}a[200010], temp[200010];
bool cx(const node &a, const node &b)
{
	return a.x < b.x;
}//比较x
bool cy(const node &a, const node &b)
{
	return a.y < b.y;
}//比较y
double min(double x, double y)
{
	return x < y ? x : y;
}//比较值
double dis(node p, node q)
{
	if (p.bel == q.bel) return MAX;//如果两点属于同一组，则距离为MAX
	return sqrt((p.x - q.x)*(p.x - q.x) + (p.y - q.y)*(p.y - q.y));
}//计算距离
double make(int l, int r)
{
	if (l == r) return MAX;//二分，只有1个点时。返回MAX，两个点时返回距离
	int m = (l + r) / 2, i, j, k, ll, rr, p, q, x, y, z, cnt = 0;
	double ans = min(make(l, m), make(m + 1, r));
	for (i = l; i <= r; i++)
		if (ab(a[i].x - a[m].x) <= ans)
			temp[++cnt] = a[i];
	sort(temp + 1, temp + cnt + 1, cy);//将求出的x按y排序
	for (i = 1; i <= cnt; i++)
		for (j = i + 1; j <= cnt; j++)
		{
			if (temp[j].y - temp[i].y > ans) break;
			ans = min(ans, dis(temp[i], temp[j]));
		}
	return ans;
}
int main()
{
	int i, j, k, T;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		for (i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &a[i].x, &a[i].y);
			a[i].bel = 0;
		}
		for (i = 1; i <= n; i++)
		{
			scanf("%lf%lf", &a[i + n].x, &a[i + n].y);
			a[i + n].bel = 1;
		}
		sort(a + 1, a + 2 * n + 1, cx);
		printf("%.3f\n", make(1, 2 * n));
	}
}