#include <stdio.h>

int main ()
{
	int N, M;
	scanf("%d%d", &N, &M);

	int ranges[N + 2], //[0 first_zero_pos second_zero_pos .... last_zero_pos end_pos]
	    range_count = 1;
	ranges[0] = 0; //start position = 0

	int i, first, max = 0;
	for(i = 0, first = 0; i < N; i++)
	{
		int temp;
		scanf("%d", &temp);

		if(!temp)
		{			
			if(range_count > M)
			{
				int diff = i - ranges[first];
				if(diff > max)
					max = diff;
				first++;
			}
			ranges[range_count++] = i + 1; //push positions (not indexes)
		}	
	}
	int diff = N - ranges[first];
	if(diff > max)
		max = diff;

	printf("%d", max);	
	return 0;
}
