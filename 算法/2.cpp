#include<stdio.h>
int main()
{
	int n,i,j,b[20];
	double a[20][2],r2,pi=3.1415;
	scanf_s("%d",&n);
	for(i=0;i<n;i++)
		scanf_s("%lf%lf",&a[i][0],&a[i][1]);
	
	
	for(i=0;i<n;i++)
	{
		r2=a[i][0]*a[i][0]+a[i][1]*a[i][1];
		for(j=0;;j++)
			if(j*50*2>pi*r2)
			{
				b[i]=j;break;
			}
		printf("Property %d: This property will begin eroding in year %d.\n",i+1,j);	
	}
	printf("END OF OUTPUT.");
	return 0;
}