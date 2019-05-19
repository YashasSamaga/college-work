#include <stdio.h>

#define MAX 5000

int main ()
{
	char str[MAX + 1];
	scanf("%s", str);

	int K;
	scanf("%d", &K);
	
	char char_stack[MAX]; 
	int count_stack[MAX], top = -1, i = 0;
	do
	{
		if(top == -1 && str[i] != '\0')
		{
			char_stack[++top] = str[i];
			count_stack[top] = 1;
		}
		else if(str[i] == char_stack[top])	
			count_stack[top]++;
		else
		{
			count_stack[top] %= K;
			if(count_stack[top] == 0)
			{
				i--;
				top--;	
			}
			else
			{
				char_stack[++top] = str[i];
				count_stack[top] = 1;	
			}		
		}
	}while(str[i++] != '\0');

	if(top == -1)
		return (printf("-1"), 0);
	
	for(i = 0; i <= top; i++)
		while(count_stack[i]--)
			printf("%c", char_stack[i]);
	return 0;
}
