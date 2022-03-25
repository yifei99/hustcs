#include<iostream>
using namespace std;

bool map[16][16] = { false };
bool flag = false;
int step;
int a[6] = { -1,1,0,0,0 }, b[6] = { 0,0,-1,1,0 };   //左右上中下

bool judge()      //判断是否全部同色
{
	for (int i = 1; i <= 4; i++)     //五个位置，除开自身，只要判断四个
		for (int j = 1; j <= 4; j++)
		{
			if (map[i][j] != map[1][1])
				return false;
		}
	return true;
}
void flip(int row, int col)     //翻转棋子
{
	for (int i = 0; i <= 4; i++)
		map[row + a[i]][col + b[i]] = !map[row + a[i]][col + b[i]];
	return;
}
void dfs(int row, int col, int deep)
{
	if (deep == step)       //判断是否从map[1][1]翻转到当前位置
	{
		flag = judge();
		return;
	}
	if (flag || row == 5) return; // dfs的走向是从左到右，从上到下，故当row==5的时候已经实现
	flip(row, col);
	if (col < 4)                  //将翻转后的全部遍历一遍，看是否符合
		dfs(row, col + 1, deep + 1);
	else
		dfs(row + 1, 1, deep + 1);
	flip(row, col);              //若前面的循环内检验出不符合条件，则翻回来
	if (col < 4)
		dfs(row, col + 1, deep);
	else
		dfs(row + 1, 1, deep);
	return;
}
int main()
{
	char fir;
	for (int i = 1; i <= 4; i++)
		for (int j = 1; j <= 4; j++)
		{
			cin >> fir;
			if (fir == 'b') map[i][j] = true;    //黑棋标记为true，白旗为false
		}

	for (step = 0; step <= 16; step++)     //最多需要走4*4（16）步
	{
		dfs(1, 1, 0);
		if (flag) break;
	}
	if (flag)
		cout << step << endl;
	else
		cout << "Impossible" << endl;
	return 0;
}
