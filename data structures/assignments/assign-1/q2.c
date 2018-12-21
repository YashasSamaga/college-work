#include <stdio.h>
#include <stdint.h>

#define MAX 100000 + 5

typedef struct {
	long long position;
	long long speed;
} Car;

void copy(Car *first, Car *last, Car *dest) //[first, last)
{
	while(first != last)
		*dest++ = *first++;
}

long long msmerge(Car nums[], int32_t first, int32_t mid, int32_t last) //[first, mid), [mid, last)
{
	int32_t size_left = mid - first;
	Car left[size_left];
	copy(&nums[first], &nums[mid], left);

	int32_t left_itr = 0, right_itr = mid, dest_itr = first;
	long long count = 0;
	while(left_itr < size_left && right_itr < last)
	{
		if(left[left_itr].position < nums[right_itr].position)
			nums[dest_itr++] = left[left_itr++];
		else if(left[left_itr].position == nums[right_itr].position) {
			if(left[left_itr].speed <= nums[right_itr].speed)
				nums[dest_itr++] = left[left_itr++];
			else {
				nums[dest_itr++] = nums[right_itr++];
			}
		}
		else {
			nums[dest_itr++] = nums[right_itr++];
			count += size_left - left_itr;
		}
	}
	copy(&left[left_itr], &left[size_left], &nums[dest_itr]);
	copy(&nums[right_itr], &nums[last], &nums[dest_itr]);
	return count;
}

long long mssplit(Car nums[], int32_t first, int32_t last) //[first, last)
{
	if(first >= (last - 1))
		return 0;

	int32_t mid = (first + last)/2;
	long long count = 0;
	count += mssplit(nums, first, mid); //[first, mid)
	count += mssplit(nums, mid, last); //[mid, last)
	
	count += msmerge(nums, first, mid, last);
	return count;
}

long long mssort(Car nums[], int32_t size) 
{
	return mssplit(nums, 0, size);
}

int is_possible(Car cars[], long long n, long long k, int time)
{
	static Car cars_new[MAX];
	int i;
	for(i = 0; i < n; i++) {
		cars_new[i].position = cars[i].position + cars[i].speed * time;
		cars_new[i].speed = 0;
	}
	long long count = mssort(cars_new, n);
	return count >= k;
}

int main ()
{
	long long n, k;
	scanf("%lld%lld", &n, &k);

	int i;
	static Car cars[MAX];
	for(i = 0; i < n; i++)
		scanf("%lld", &cars[i].position);
	for(i = 0; i < n; i++)
		scanf("%lld", &cars[i].speed);

	mssort(cars, n);

	if(!is_possible(cars, n, k, 1e9))
		return printf("-1\n"), 0;

	int first = 0, last = 1e9;
	while(first < last) {
		int mid = (first + last)/2;
		if(is_possible(cars, n, k, mid))
			last = mid;
		else
			first = mid + 1;
	}
	printf("%d\n", first);
	return 0;
}
