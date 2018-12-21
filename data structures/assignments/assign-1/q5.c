#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define debug(...) //printf(__VA_ARGS__)

const int64_t mod = 1e9 + 7;
int64_t fast_exp2(int64_t base, int64_t exponent)
{
	base = base % mod;
	exponent = exponent % mod;	

	int64_t result = 1;
	while(exponent) {
		if(exponent%2)
			result = (result * base)%mod;
		base = (base * base)%mod;
		exponent /= 2;		
	}
	return result;
}

int main () {
	int32_t n, k;
	scanf("%"PRId32"%"PRId32, &n, &k);

	int32_t nums[n], i;
	for(i = 0; i < n; i++)
		scanf("%"PRId32, &nums[i]);

	int32_t min_list[n], min_left_itr = 0, min_right_itr = 0,
		max_list[n], max_left_itr = 0, max_right_itr = 0;
	for(i = 0; i < k; i++) {
		while(min_left_itr != min_right_itr && nums[i] <= nums[min_list[min_right_itr - 1]])
			min_right_itr--;

		while(max_left_itr != max_right_itr && nums[i] >= nums[max_list[max_right_itr - 1]])
			max_right_itr--;		
	
		min_list[min_right_itr++] =
		max_list[max_right_itr++] = i;
	}

	int64_t min_product = 1, max_product = 1;
	for(i = k; i < n; i++) {
		debug("min: %"PRId32", max: %"PRId32"\n", nums[min_list[min_left_itr]], nums[max_list[max_left_itr]]);		
		
		min_product = (min_product * nums[min_list[min_left_itr]])%mod;
		max_product = (max_product * nums[max_list[max_left_itr]])%mod;		
		if(min_list[min_left_itr] == (i - k))
			min_left_itr++;

		if(max_list[max_left_itr] == (i - k))
			max_left_itr++;
		
		while(min_left_itr != min_right_itr && nums[i] <= nums[min_list[min_right_itr - 1]])
			min_right_itr--;

		while(max_left_itr != max_right_itr && nums[i] >= nums[max_list[max_right_itr - 1]])
			max_right_itr--;
	
		min_list[min_right_itr++] =
		max_list[max_right_itr++] = i;
	}
	min_product = (min_product * nums[min_list[min_left_itr]])%mod;
	max_product = (max_product * nums[max_list[max_left_itr]])%mod;	

	debug("min: %"PRId32", max: %"PRId32"\n", nums[min_list[min_left_itr]], nums[max_list[max_left_itr]]);
	printf("%"PRId64"\n", ((max_product % mod) * fast_exp2(min_product, mod - 2))%mod);
	return 0;
}
