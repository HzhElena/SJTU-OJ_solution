//oj_4001.cpp

#include<cstdio>

const int upperbound = 100000000;
long long a,b;

int main()
{
	char input;
	bool flag = true;
	while((input = getchar()) != EOF)
	{
		if(input == ' ')
			continue;
		if(input == '+')
			flag = false;
		else if(input >= '0' && input <= '9')
		{
			if(flag)
				a = a * 10 + input - '0';
			else
				b = b * 10 + input - '0';
		}
	}
	a + b > upperbound ? printf("Large\n") : printf("%d\n",a + b);
	return 0;
}
