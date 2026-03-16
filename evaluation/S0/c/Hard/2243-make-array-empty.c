// Source: https://leetcode.com/problems/make-array-empty/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums containing distinct numbers, and you can perform the following operations until the array is empty:
//
//
// 	If the first element has the smallest value, remove it
// 	Otherwise, put the first element at the end of the array.
//
//
// Return an integer denoting the number of operations it takes to make nums empty.
//
// Example:
// Input: nums = [3,4,-1]
// Output: 5
//
//
//
// 	
// 		
// 			Operation
// 			Array
// 		
// 	
// 	
// 		
// 			1
// 			[4, -1, 3]
// 		
// 		
// 			2
// 			[-1, 3, 4]
// 		
// 		
// 			3
// 			[3, 4]
// 		
// 		
// 			4
// 			[4]
// 		
// 		
// 			5
// 			[]
//
// Constraints:
// 1 <= nums.length <= 105
// 	-109 <= nums[i] <= 109
// 	All values in nums are distinct.
//

long long countOperationsToEmptyArray(int* nums, int numsSize) {
    int *pos = (int*)malloc(numsSize * sizeof(int));
    if (!pos) return -1; /* allocation failure */

    for (int i = 0; i < numsSize; ++i) {
        pos[nums[i] < 0 ? -nums[i] : nums[i]] = i;
    }

    long long operations = 0;
    int currentIndex = -1;
    for (int val = -109; val <= 109; ++val) {
        int p = pos[val];
        if (p == 0 && nums[0] != 0) { /* not in array */
            continue;
        }
        if (p > currentIndex) {
            operations += (p - currentIndex);
        } else {
            operations += (numsSize - currentIndex + p);
        }
        currentIndex = p;
    }

    free(pos);
    return operations;      
}
