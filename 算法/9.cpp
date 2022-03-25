#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 10010;

int n, mid, ans = 0;
int x[maxn], y[maxn];
//对于y轴，总步数为Σ|y[i]-mid|，对于x轴，总步数为Σ|x[i]-(mid+i)|=Σ|(x[i]-i)-mid|

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d", &x[i], &y[i]);
	sort(x + 1, x + n + 1);
	for (int i = 1; i <= n; i++) x[i] -= i;//预处理x[i]-i
	sort(x + 1, x + n + 1);
	mid = x[(1 + n) / 2];
	for (int i = 1; i <= n; i++) ans += abs(mid - x[i]);

	sort(y + 1, y + n + 1);
	mid = y[(1 + n) / 2];
	for (int i = 1; i <= n; i++) ans += abs(mid - y[i]);

	printf("%d\n", ans);
	return 0;
}