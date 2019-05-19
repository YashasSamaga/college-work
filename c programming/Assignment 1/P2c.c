#include <stdio.h>

#define debug(...) printf(__VA_ARGS__)

int main ()
{
	int N, M;
	scanf("%d%d", &N, &M);

	int ranges[N + 2], //[0 first_zero_pos second_zero_pos .... last_zero_pos end_pos]
	    range_count = 1;
	ranges[0] = 0; //start position = 0

	int i;
	for(i = 0; i < N; i++)
	{
		int temp;
		scanf("%d", &temp);

		if(!temp)
			ranges[range_count++] = i + 1; //push positions (not indexes)
	}
	ranges[range_count++] = N + 1; //end position

	if(range_count <= (M + 2))
		return printf("%d", N), 0;

	int max = 0;
	for(i = 0, last = i + M + 1; last < range_count; i++, last++)
	{	
		int diff = ranges[last] - ranges[i] - 1; //(ranges[i], ranges[last])
		if(diff > max)
			max = diff;

		debug("[DEBUG] diff:%d max:%d i:%d last:%d\n", diff, max, i, last); 
	}
	printf("%d", max);
	return 0;
}
