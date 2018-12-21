template <typename BidirItr>
void bubble_sort(BidirItr first, BidirItr last) {
	int nums[], first = 0, last = n, did_sawp = true;
	while(did_swap) {
		swap = false;
		for(int j = 1; j < last; j++)
			if(nums[j - 1] > nums[j]) {
			 	swap(nums[j], nums[j + 1]);
				did_sawp = true;	
				last = j;			
			}	
	}
}
