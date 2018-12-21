#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define debug(...) printf(__VA_ARGS__)

/* helpers */
void copy(int_fast32_t *first, int_fast32_t *last, int_fast32_t *dest) //[first, last)
{
	while(first != last)
		*dest++ = *first++;
}

/* sorting */
void msmerge(int_fast32_t nums[], int_fast32_t first, int_fast32_t mid, int_fast32_t last) //[first, mid), [mid, last)
{
	int_fast32_t size_left = mid - first, left[size_left];
	copy(&nums[first], &nums[mid], left);

	int_fast32_t left_itr = 0, right_itr = mid, dest_itr = first;
	while(left_itr < size_left && right_itr < last)
	{
		if(left[left_itr] < nums[right_itr])
			nums[dest_itr++] = left[left_itr++];
		else
			nums[dest_itr++] = nums[right_itr++];
	}
	copy(&left[left_itr], &left[size_left], &nums[dest_itr]);
	copy(&nums[right_itr], &nums[last], &nums[dest_itr]);
}

void mssplit(int_fast32_t nums[], int_fast32_t first, int_fast32_t last) //[first, last)
{
	if(first >= (last - 1))
		return;

	int_fast32_t mid = (first + last)/2;
	mssplit(nums, first, mid); //[first, mid)
	mssplit(nums, mid, last); //[mid, last)
	
	msmerge(nums, first, mid, last);
}

void mssort(int_fast32_t nums[], int_fast32_t size) 
{
	mssplit(nums, 0, size);
}

/* question specific functions */
int64_t time_function(int_fast32_t min, int_fast32_t max) 
{
	const int64_t min_c = min, max_c = max;
	return max_c * (max_c - min_c + 1);
}
int_fast32_t is_possible(int_fast32_t nums[], int_fast32_t size, int_fast32_t processors, int64_t time)
{
	int_fast32_t left_itr = 0, right_itr = 0;
	while(right_itr < size && processors)
	{
		if(time_function(nums[left_itr], nums[right_itr]) <= time)
			right_itr++;
		else
		{
			left_itr = right_itr;
			processors--;		
		}
	}
	return right_itr == size;
}

int main () 
{
	int_fast32_t n, k;
	scanf("%"PRIdFAST32"%"PRIdFAST32, &n, &k);

	int_fast32_t nums[n], i;
	for(i = 0; i < n; i++)
		scanf("%"PRIdFAST32, &nums[i]);

	mssort(nums, n);

	int64_t first = nums[0], last = nums[n - 1]*nums[n - 1];
	while(first < last)
	{
		int64_t mid = (first + last)/2;
		if(is_possible(nums, n, k, mid))
			last = mid;
		else
			first = mid + 1;
	}
	printf("%"PRId64, first);	
	return 0;
}
