#include <stdio.h>
#include <string.h>

#define debug(...) //printf(__VA_ARGS__)

#define MAX 200000

int isSubsequence(const char *seq, const char *sub)
{
	debug("[DEBUG] isSubsequence>> seq:%s sub:%s\n", seq, sub);
	if(*sub == '\0')
		return 1;	
	if(*seq == '\0')
		return 0;
	do
	{
		debug("[DEBUG] isSubsequence::iteration >> %s %s\n", seq, sub);		
		if(*seq++ == *sub) 
			sub++;
		if(*sub == '\0') 
			return 1;
	}while(*seq != '\0');
	return 0;	
}
int main ()
{
	char S[MAX + 1], P[MAX + 1];
	scanf("%s%s", S, P);
 
	int S_len = strlen(S), order[MAX], i;
	for(i = 0; i < S_len; i++)
		scanf("%d", &order[i]);

	int first = 0, last = S_len;
	while(first < last)
	{
		int mid = (first + last)/2;
		debug("[DEBUG] upper_bound>> first=%d, mid=%d, last=%d\n", first, mid, last);

		char tmp[MAX + 1];
		memcpy(tmp, S, S_len + 1);

		for(i = 0; i < mid; i++)
			tmp[order[i] - 1] = '.';

		if(isSubsequence(tmp, P))
			first = mid + 1;
		else
			last = mid;		
	}
	printf("%d", first - 1);
	return 0;
}

