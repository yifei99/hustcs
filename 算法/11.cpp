#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int arr[maxn], n;
ll m;
bool check(int mid) {
	ll cnt = 0, i = 0;
	for (int i = 0; i < n; i++) {
		cnt += arr + n - lower_bound(arr + i + 1, arr + n, arr[i] + mid);//大于mid的个数
	}
	return cnt >= m / 2 + 1;
}
int main() {
	while (~scanf_s("%d", &n)) {
		for (int i = 0; i < n; i++) scanf_s("%d", &arr[i]);
		m = n * (n - 1) / 2;
		sort(arr, arr + n);
		int left = 0, right = arr[n - 1] - arr[0];
		while (left <= right) {
			int mid = (left + right) / 2;
			if (check(mid)) left = mid + 1;
			else right = mid - 1;
		}
		printf("%d\n", right);
	}
}