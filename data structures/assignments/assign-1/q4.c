#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define debug(...) printf(__VA_ARGS__)

void copy(int32_t *first, int32_t *last, int32_t *dest) //[first, last)
{
	while(first != last)
		*dest++ = *first++;
}

int32_t upper_bound(int32_t nums[], int32_t first, int32_t last, int32_t value) //[first, last)
{
	last--;
	while(first < last) {
		int mid = (first + last)/2;
		if(nums[mid] <= value)
			first = mid + 1;		
		else
			last = mid;
	}
	return first;
}

int32_t lis_length(int32_t nums[], int32_t first, int32_t last) //[first, last)
{
	int32_t ends[last - first], length = 1;
	ends[0] = nums[first];

	int32_t itr = first + 1;
	while(itr < last) 
	{
		const int32_t current_value = nums[itr];
		if(current_value >= ends[length - 1])
			ends[length++] = current_value;
		else
		{
			int lub = upper_bound(ends, 0, length, current_value);			
			ends[lub] = current_value;
			if(lub == length)
				length++;
		}
		itr++;
	}
	return length;
}

int32_t msmerge(int32_t nums[], int32_t first, int32_t mid, int32_t last) //[first, mid), [mid, last)
{
	int32_t length = (last - first) - lis_length(nums, first, last);

	int32_t size_left = mid - first;
	int32_t left[size_left];
	copy(&nums[first], &nums[mid], left);

	int32_t left_itr = 0, right_itr = mid, dest_itr = first;
	while(left_itr < size_left && right_itr < last)
	{
		if(left[left_itr] < nums[right_itr])
			nums[dest_itr++] = left[left_itr++];
		else
			nums[dest_itr++] = nums[right_itr++];
	}
	copy(&left[left_itr], &left[size_left], &nums[dest_itr]);
	copy(&nums[right_itr], &nums[last], &nums[dest_itr]);
	return length;
}

int32_t mssplit(int32_t nums[], int32_t first, int32_t last) //[first, last)
{
	if(first >= (last - 1))
		return 0;

	int32_t mid = (first + last)/2, count = 0;
	count += mssplit(nums, first, mid); //[first, mid)
	count += mssplit(nums, mid, last); //[mid, last)
	
	count += msmerge(nums, first, mid, last);
	return count;
}

int32_t mssort(int32_t nums[], int32_t size) 
{
	return mssplit(nums, 0, size);
}

int main () {
	int32_t n;
	scanf("%"PRId32, &n);

	int32_t nums[n], i;
	for(i = 0; i < n; i++)
		scanf("%"PRId32, &nums[i]);

	printf("%d", mssort(nums, n));
	return 0;
}
