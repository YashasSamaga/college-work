#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int main ()
{
	long long n; 
	long long k;
	scanf("%lld%lld", &n, &k);

	long long i, nums[n];
	for(i = 0; i < n; i++)
		scanf("%lld", &nums[i]);

	long long remaining = n;
	while(k > remaining && remaining) {
		const long long q = k / remaining;
		k = k % remaining;

		for(i = 0; i < n; i++) {
			if(nums[i] == 0)
				continue;

			if(nums[i] > q)
				nums[i] -= q;
			else {
				k += q - nums[i];
				nums[i] = 0;
				remaining--;
			}	
		}	
	}

	long long cur_pos = 0;
	while(remaining && k)
	{
		for(cur_pos = 0; k && remaining && cur_pos < n; cur_pos++)
			if(nums[cur_pos] != 0)
			{
				k--;
				if(--nums[cur_pos] == 0)
					remaining--;			
			}	
	}

	if(k > 0)
		return printf("-1\n"), 0;

	if(remaining == 0)
		return printf("\n"), 0;

	for(i = cur_pos; i < n; i++)
		if(nums[i])
			printf("%lld ", i + 1);
	for(i = 0; i < cur_pos; i++)
		if(nums[i])
			printf("%lld ", i + 1);
	printf("\n");	
	return 0;
}