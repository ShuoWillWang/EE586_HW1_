#include<stdio.h>

void rev(short *a, short an)
{
	short start = 0;
	short end = an - 1;
	while (start < end)
	{
		short temp = a[start];
		a[start] = a[end];
		a[end] = temp;
		start++;
		end--;
	}
}

short* conv(short *a, short *b, short an, short bn)
{
	short* res;
	res = (short *)malloc(sizeof(short) * (an + bn - 1));
	short ind = 0;
	while (ind < an + bn - 1)
	{
		res[ind] = 0;
		ind++;
	}
	rev(a, an);
	short* bnew;
	bnew = (short *)malloc(sizeof(short) * (an + an - 1 + bn - 1));
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
		short sum = 0;
		short j = 0;
		while (j < an)
		{
			if(j + 3 < an)
			{
				sum += a[j] * bnew[j + i];
				sum += a[j + 1] * bnew[j + i + 1];
				sum += a[j + 2] * bnew[j + i + 2];
				sum += a[j + 3] * bnew[j + i + 3];
				j += 4;
			}
			else
			{
				sum += a[j] * bnew[j + i];
				j++;
			}
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
	short* inputs;
	inputs = (short *)malloc(sizeof(short) * (sizeof(input) / sizeof(float)));
	while(i < sizeof(input) / sizeof(float))
	{
		inputs[i] = (short)(100 * input[i]);
		i++;
	}
	
	short* filters;
	filters = (short *)malloc(sizeof(short) * (sizeof(filter) / sizeof(float)));
	i = 0;
	while(i < sizeof(filter) / sizeof(float))
	{
		filters[i] = (short)(100 * filter[i]);
		i++;
	}
	i = 0;
	int t = 0;
	while(t < 10000)
	{
		short* temp = conv(inputs, filters, 12, 7);
		if(t % 100 == 0)
		{
			for (i = 0; i < 18; i++)
			{
				printf("%d\t", temp[i]);
			}
			printf("\n");
		}
		t++;
	}
}
