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

class Solution {
public:
    long long countOperationsToEmptyArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> pos(n);
        vector<int> sortedNums = nums;
        sort(sortedNums.begin(), sortedNums.end());
        
        for (int i = 0; i < n; i++) {
            int val = nums[i];
            int idx = lower_bound(sortedNums.begin(), sortedNums.end(), val) - sortedNums.begin();
            pos[idx] = i;
        }
        
        long long operations = 0;
        int prevPos = -1;
        
        for (int i = 0; i < n; i++) {
            int currPos = pos[i];
            if (currPos > prevPos) {
                operations += (currPos - prevPos);
            } else {
                operations += (n - (prevPos - currPos));
            }
            prevPos = currPos;
        }
        
        return operations;          
    }
};
