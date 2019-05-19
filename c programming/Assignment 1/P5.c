#include <stdio.h>
#include <string.h>

#define debug(...) //printf(__VA_ARGS__)

int lower_bound(int nums[], int index_array[], int first, int last, int val)
{
	while(first < last)
	{
		int mid = (first + last)/2;
		if(nums[index_array[mid]] < val)
			first = mid + 1;
		else if(val <= nums[index_array[mid]])
			last = mid;
	}
	return first;
}

int main ()
{
	int N;
	scanf("%d", &N);

	int nums[N], i;
	for(i = 0; i < N; i++)
		scanf("%d", &nums[i]);

	int tailIndex[N], prevIndex[N], len = 1;	
	prevIndex[0] = -1;
	tailIndex[0] = 0;
	for(i = 1; i < N; i++)
	{
		if(nums[tailIndex[0]] >= nums[i])
		{
			debug("[DEBUG] New smallest element: %d, Previous smallest element: %d\n", nums[i], nums[tailIndex[0]]);
			prevIndex[i] = -1;		
			tailIndex[0] = i;
		}
		else if(nums[tailIndex[len - 1]] < nums[i])
		{	
			debug("[DEBUG] New largest element: %d, Previous largest element: %d\n", nums[i], nums[tailIndex[len - 1]]);
			prevIndex[i] = tailIndex[len - 1];			
			tailIndex[len++] = i;
		}		
		else
		{
			debug("[DEBUG] New intermediate element: %d, smallest element: %d, largest element:%d\n", nums[i], nums[tailIndex[0]], nums[tailIndex[len - 1]]);

			int lb = lower_bound(nums, tailIndex, 0, len, nums[i]);
			debug("[DEBUG] lower bound:%d , value@ = %d\n", lb, nums[tailIndex[lb]]);
			prevIndex[i] = tailIndex[lb - 1];
			tailIndex[lb] = i;
		}
		debug("\n");
	}

	//reusing nums to store indexes in reverse order
	int j;
	for(i = 0, j = tailIndex[len - 1]; j != - 1; i++, j = prevIndex[j])
		nums[i] = j;

	printf("%d\n", len);
	for(i = len - 1; i >= 0; i--)
		printf("%d ", nums[i]);

	return 0;
}
