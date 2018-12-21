#include <iostream>
#include <iterator>

template <typename T, std::size_t N>
T* end(T (&arr)[N])
{
	return arr + N;
}

template <typename ForwardItr, typename T>
bool binary_search(ForwardItr first, ForwardItr last, T val)
{
	--last;
	ForwardItr mid;
	while(first <= last)
	{
		mid = first + (last - first)/2;
		if(*mid > val)
			last = mid;
		else if(*mid < val)
			first = mid + 1;
		else
			last = mid;
	}
	return false;
}

bool binary_search(int nums[], int size, int value)
{
	int first = 0, last = size - 1;
	while(first <= last)
	{
		int mid = (first + last)/2;
		if(nums[mid] == value)
			return true;
		else if(nums[mid] < value)
			first = mid + 1;
		else
			last = mid;
	}
	return false;
}

template <typename ForwardItr, typename T>
int binary_search_rank(ForwardItr first, ForwardItr last, const T& val)
{
	ForwardItr mid, start = first;
	while(first < last)
	{
		mid = first + (last - first)/2;
		if(*mid > val)
			last = mid;
		else if(*mid == val)
			last = mid;
		else
			first = mid + 1;			
	}
	return first - start;
}

template <typename ForwardItr, typename T>
ForwardItr lower_bound(ForwardItr first, ForwardItr last, T val)
{
	ForwardItr mid;
	while(first < last)
	{
		mid = first + (last - first)/2;
		if(val <= *mid)
			last = mid;
		else
			first = mid + 1;
	}
	return first;
}

template <typename ForwardItr, typename T>
ForwardItr upper_bound(ForwardItr first, ForwardItr last, T val)
{
	ForwardItr mid;
	while(first < last)
	{
		mid = first + (last - first)/2;
		if(val < *mid)
			last = mid;
		else if(val >= *mid)
			first = mid + 1;
	}
	return first;
}

int main ()
{
	int arr[] = { 1, 1, 3, 4, 4, 4, 4, 4, 6, 8, 10, 10 , 10, 12 };
	int a;
	std::cin >> a;
	std::cout << lower_bound(arr, end(arr), a) - arr;
}
