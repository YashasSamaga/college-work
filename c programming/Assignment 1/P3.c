#include <stdio.h>

#define debug(...) //printf(__VA_ARGS__)

#define max(x,y) (((x)>(y))?(x):(y))

/*int func(int days, int state)
{
	if(days == 0)
		return 0;

	if(state == K)
		return func(days - 1, 0);

	int p1 = func(days - 1, state + 1) + time[N-days],
	    p2 = func(days - 1, 0);
			
	return max(p1, p2);
}*/

int main ()
{
	int N, K;
	scanf("%d%d", &N, &K);

	int time[N], i;
	for(i = 0; i < N; i++)
		scanf("%d", &time[i]);

	K--;
	int table[N + 1][K + 1]; //table[i][j] = max play time in 'i' days with (K-j) continues play days remaining
	for(i = 0; i <= K; i++)
		table[0][i] = 0;

	int j;
	for(i = 1; i <= N; i++)
	{
		for(j = 0; j < K; j++)
		{
			table[i][j] = max(table[i-1][j+1] + time[N-i], table[i-1][0]);
			
			debug("[DEBUG] table[%d][%d] = %d, table[%d][%d]=%d, time[%d]=%d, table[%d][%d]=%d\n", 
				i, j, table[i][j], i-1, j+1, table[i-1][j+1], N-i, time[N-i], i-1, 0, table[i-1][0]);
		}
		table[i][K] = table[i-1][0];

		debug("[DEBUG] table[%d][%d] = %d, table[%d][%d]=%d\n", 
				i, j, table[i][j], i-1, 0, table[i-1][0]);
	}
	printf("%d", table[N][0]);
	return 0;
}
