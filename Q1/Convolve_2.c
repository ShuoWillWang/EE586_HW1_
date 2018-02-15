#include<stdio.h>

void rev(float *a, short an)
{
	short start = 0;
	short end = an - 1;
	while (start < end)
	{
		float temp = a[start];
		a[start] = a[end];
		a[end] = temp;
		start++;
		end--;
	}
}

float* conv(float *a, float *b, short an, short bn)
{
	float* res;
	res = (float *)malloc(sizeof(float) * (an + bn - 1));
	short ind = 0;
	while (ind < an + bn - 1)
	{
		res[ind] = 0;
		ind++;
	}
	rev(a, an);
	float* bnew;
	bnew = (float *)malloc(sizeof(float) * (an + an - 1 + bn - 1));
	short i = 0;
	while (i < an + an - 1 + bn - 1)
	{
		if (i >= an - 1 && i < an + bn - 1)
		{
			bnew[i] = b[i - an + 1];
		}
		else
		{
			bnew[i] = 0;
		}
		i++;
	}
	i = 0;
	while (i < an + bn - 1)
	{
		short j = 0;
		float sum = 0;
		while (j < an)
		{
			sum += a[j] * bnew[j + i];
			j++;
		}
		res[i] = sum;
		i++;
	}
	free(bnew);
	return res;
}

void main()
{
	short i = 0;
	float input[] = {0.1,0.3,0.2,0.4,0.3,0.5,0.6,0.4,0.4,0.3,0.7,0.1};
	float filter[] = { -0.1,0.0,0.1,0.2,0.1,0.0,-0.1 };
	int t = 0;
	while(t < 10000)
	{
		float* temp = conv(input, filter, 12, 7);
		//if(t % 100 == 0)
		//{
		//	for (i = 0; i < 14; i++)
		//	{
		//		printf("%d\t", (int)temp[i]);
		//	}
		//	printf("\n");
		//}
		t++;
	}
}
