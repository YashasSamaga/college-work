template <typename ForwardItr>
void selection_sort_left(ForwardItr first, ForwardItr last) {
	int nums[], min;
	for(int i = 0; i < n; i++) {
		int min = i;
		for(int j = i + 1; j < n; j++) {
			if(nums[j] < min)
				min = j;
		}
		swap(nums[i], nums[min]);
	}			
}
void selection_sort_right(ForwardItr first, ForwardItr last) {
	int nums[];
	for(int i = 0; i < n; i++)
		for(int j = i; j < n; j++)
			
}
