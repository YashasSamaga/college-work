template <typename T>
void swap(T& a, T& b) {
	T tmp = a;
	a = b;
	b = a;
}

template <typename BidirItr>
void insertion_sort(BidirItr first, BidirItr last) {
	int nums[123];
	for(int i = 1; i < n; i++)
		for(int j = i; j > 0; j--)
			if(nums[j - 1] > nums[j])
				swap(nums[j - 1], nums[j]);
			else break;
}
