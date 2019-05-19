#include <stdio.h>

#define MAX 1000000

#define debug(...) //printf(__VA_ARGS__)

#define IsBitSet(x,y) ((x & y) == y)
#define SetBit(x,y) ((x) | (y))
#define NumToBit(x) (1 << (x))

enum 
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};

int min(int x, int y)
{
	return ((x < y)?x:y);
}
int min3(int x, int y, int z)
{
	return min(min(x, y), z);
}	

int g_N;
char *g_str;
int *g_cost;

int table[MAX + 1][8][3];
int func(int idx, int state, int cur_char)
{
	debug("[DEBUG] func call >> idx=%d, state=%d, cur_char=%d\n", idx, state, cur_char);

	if(idx == g_N)
		return 0;

	if(table[idx][state][cur_char] != -1)
		return table[idx][state][cur_char];

	if(g_str[idx] == cur_char)
	{
		table[idx][state][cur_char] = func(idx + 1, state, cur_char);
		return table[idx][state][cur_char];
	}

	if(!IsBitSet(state, NumToBit(g_str[idx])))
	{
		int p1 = func(idx + 1, state, cur_char) + g_cost[idx],
		    p2 = func(idx + 1, SetBit(state, NumToBit(g_str[idx])), g_str[idx]);

		table[idx][state][cur_char] = min(p1, p2);
		return table[idx][state][cur_char];
	}
	table[idx][state][cur_char] = func(idx + 1, state, cur_char) + g_cost[idx];
	return table[idx][state][cur_char];
}
			
int main ()
{
	int N;
	scanf("%d", &N);

	char str[N + 1];
	scanf("%s", str);			

	int char_hash[127];
	char_hash['R'] = RED;
	char_hash['G'] = GREEN;
	char_hash['B'] = BLUE;

	int cost[N], i;
	for(i = 0; i < N; i++)
	{
		str[i] = char_hash[str[i]];
		scanf("%d", &cost[i]);
	}

	g_str = str;
	g_cost = cost;
	g_N = N;

	for(i = N - 1; i >= 0; i--)
	{
		int j;
		for(j = 7; j >= 0; j--)
		{
			int k;
			for(k = 0; k < 3; k++)
				table[i][j][k] = -1;
		}
	}
	/*int table[N + 1][8][3];
	for(i = 0; i < 8; i++)
	{
		int j;
		for(j = 0; j < 3; j++)
			table[N][i][j] = 0;
	}*/

	//Topological sorting
	/*
		Every iteration will use first index greater than 'i'
			=> (fill in decreasing order)
		Every iteration will use the third index as 'j' or with a new bit set in 'j'
			=> setting a new bit in 'j' will always increase 'j'
			=> iteration depends on higher values of 'j'
			=> (fill in decreasing order)
		Every iteration will use third index as SHIT
			=> SHHHIIIIIT
	*/
	/*for(i = N - 1; i >= 0; i--)
	{
		int j;
		for(j = 7; j >= 0; j--)
		{
			int k;
			for(k = 0; k < 3; k++)
			{
				if(str[i] == k)
				{
					table[i][j][k] = table[i+1][j][k];
					break;
				}
				if(!IsBitSet(j, NumToBit(str[i])))
				{
					int p1 = table[i+1][j][k] + cost[i],
					    p2 = table[i+1][SetBit(j, NumToBit(str[i]))][str[i]];
					table[i][j][k] = min(p1, p2);
					break;
				}
				table[i][j][k] = table[i+1][j][k] + cost[i];
			}
		}
	}

	/*
	int  min = func(1, NumToBit(RED), RED) + ((str[0] == RED)?0:cost[0]);
	debug("[DEBUG] For 'R', min=%d\n", min);

	int c = func(1, NumToBit(BLUE), BLUE) + ((str[0] == BLUE)?0:cost[0]);
	debug("[DEBUG] For 'B', min=%d\n", c);
	if(c < min)
		min = c;
	
	c = func(1, NumToBit(GREEN), GREEN) + ((str[0] == GREEN)?0:cost[0]);
	debug("[DEBUG] For 'G', min=%d\n", c);
	if(c < min)
		min = c;
	*/

	printf("%d", min3(func(1, NumToBit(RED), RED) + ((str[0] == RED)?0:cost[0]),
			  func(1, NumToBit(BLUE), BLUE) + ((str[0] == BLUE)?0:cost[0]),
			  func(1, NumToBit(GREEN), GREEN) + ((str[0] == GREEN)?0:cost[0])));	
	return 0;
}
